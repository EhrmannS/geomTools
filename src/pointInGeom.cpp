#include <Rcpp.h>
using namespace Rcpp;

// This is an extension by Steffen Ehrmann (2019), of the below described
// algorithm. It extends the "point in polygon" algorithm, which gives values 0
// and 1 for points that are outside or inside of a polygon, respectively, by
// the values 2 and 3, for points that are on one or two lines (a vertex) of the
// polygon, respectively.
//
// http://geomalgorithms.com/a03-_inclusion.html Copyright 2000 softSurfer, 2012
// Dan Sunday This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it. SoftSurfer makes no
// warranty for this code, and cannot be held liable for any real or imagined
// damage resulting from its use. Users of this code must verify correctness for
// their application.


// [[Rcpp::export]]
IntegerVector pointInGeomC(NumericMatrix &vert, NumericMatrix &geom, bool invert){
  int vRows = vert.nrow();
  int gRows = geom.nrow();
  double isLeft;
  int inside, outside;
  IntegerVector out(vRows);
  if(invert){
    inside = 0;
    outside = 1;
  } else{
    inside = 1;
    outside = 0;
  }

  // get bounding box of geom
  double xMin = min(geom(_, 0)), xMax = max(geom(_, 0));
  double yMin = min(geom(_, 1)), yMax = max(geom(_, 1));

  // warning if first and last coordinate are not the same
  // if(any(geom(0, _) != geom(gRows-1, _)).is_true()){
  //   stop("first and last vertex must be the same.");
  // }
  // Rcout << "\n[x- " << xMin << "," << xMax << " | y- " << yMin << "," << yMax << "]" << std::endl;

  for(int j = 0; j < vRows; j++){
    int on = 1; // as we start with a new vertex, reset indicator for "on the line" to 1

    double x = vert(j, 0);
    double y = vert(j, 1);
    // Rcout << "\n(" << x << "," << y << ")" << std::endl;

    // if the coordinate is within the bounding box, proceed, otherwise value is definitely 0
    if((x <= xMax) & (x >= xMin) & (y <= yMax) & (y >= yMin)){
      int wn = 0;                            // the  winding number counter

      // Rcout << "inside extent\n" << std::endl;
      // loop through all edges of the geometry and find wn
      for (int i = 0; i < gRows-1; i++){

        // Rcout << "\n" << i+1 << ". ----" << std::endl;

        if (y >= geom(i, 1)){
          // Rcout << "y >= vertex " << i+1 << " (" << y << " >= " << geom(i, 1) << ")" << std::endl;

          if (y < geom(i+1, 1)){             // an upward crossing
            // Rcout << "    y < vertex " << i+2 << " (" << y << " < " << geom(i+1, 1) << ")" << std::endl;

            isLeft = (geom(i+1, 0) - geom(i, 0)) * (y - geom(i, 1)) - (x -  geom(i, 0)) * (geom(i+1, 1) - geom(i, 1));
            if(isLeft == 0){                  // point is on the line
              ++on;
              // Rcout << "    y is on the line (" << isLeft << ")" << std::endl;
              // Rcout << "                    -- set 'on' (" << on << ")" << std::endl;
            } else if(isLeft > 0){                  // P left of or on edge "isLeft > 0"
              ++wn;                          // have  a valid up intersect
              // Rcout << "    y is left of line (" << isLeft << ")" << std::endl;
              // Rcout << "                    -- wn+1 (" << wn << ")" << std::endl;
            } else {
              // Rcout << "    y is right of line (" << isLeft << ")" << std::endl;
              // Rcout << "                    -- NULL" << std::endl;
            }
          } else {
            // Rcout << "    y >= vertex " << i+2 << " (" << y << " >= " << geom(i+1, 1) << ")" << std::endl;
            // Rcout << "                    -- NULL" << std::endl;
            isLeft = (geom(i+1, 0) - geom(i, 0)) * (y - geom(i, 1)) - (x -  geom(i, 0)) * (geom(i+1, 1) - geom(i, 1));
            if(isLeft == 0){
              ++on;
              // Rcout << "    y is on the line (" << isLeft << ")" << std::endl;
              // Rcout << "                    -- on+1 (" << on << ")" << std::endl;
            }
          }

        } else {
          // Rcout << "y < vertex " << i+1 << " (" << y << " < " << geom(i, 1) << ")" << std::endl;

          if (y >= geom(i+1, 1)){            // a downward crossing
            // Rcout << "    y >= vertex " << i+2 << " (" << y << " >= " << geom(i+1, 1) << ")" << std::endl;

            isLeft = (geom(i+1, 0) - geom(i, 0)) * (y - geom(i, 1)) - (x -  geom(i, 0)) * (geom(i+1, 1) - geom(i, 1));
            if(isLeft == 0){
              ++on;
              // Rcout << "    y is on the line (" << isLeft << ")" << std::endl;
              // Rcout << "                    -- on+1 (" << on << ")" << std::endl;
            } else if(isLeft < 0){                  // P right of edge
              --wn;                          // have  a valid down intersect
              // Rcout << "    y is right of line (" << isLeft << ")" << std::endl;
              // Rcout << "                    -- wn-1 (" << wn << ")" << std::endl;
            } else {
              // Rcout << "    y is left of line (" << isLeft << ")" << std::endl;
              // Rcout << "                    -- NULL" << std::endl;
            }
          } else {
            // Rcout << "    y < vertex " << i+2 << " (" << y << " < " << geom(i+1, 1) << ")" << std::endl;
            // Rcout << "                    -- NULL" << std::endl;

          }

        }

      }

      if(on != 1){
        out[j] = on;
      } else {
        if(wn == 0){
          out[j] = outside;
        } else{
          out[j] = inside;
        }
      }

    } else {
      // Rcout << "outside of extent\n" << std::endl;
      out[j] = outside;
    }
  }

  return(out);
}