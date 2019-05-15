[![Travis-CI Build Status](https://travis-ci.org/EhrmannS/geometr.svg?branch=master)](https://travis-ci.org/EhrmannS/geometr)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/geometr)](https://cran.r-project.org/package=geometr)
[![Coverage Status](https://img.shields.io/codecov/c/github/EhrmannS/geometr/master.svg)](https://codecov.io/github/EhrmannS/geometr?branch=master)
<!-- [![](http://cranlogs.r-pkg.org/badges/grand-total/geometr)](https://cran.rstudio.com/web/packages/geometr/index.html)-->

# geometr

***Generate and Process Geometric Shapes***

The geometr package provides a standardised and reproducible approach to generating and manipulating geometries at vertex level.


## Getting started

1) Install the development version from github via:

        devtools::install_github("EhrmannS/geometr")

2) Read a **brief introduction** to understand the philosophy of `geometr`:

        ?`geometr-package`

3) Read an in detail [Introduction](articles/introduction.html).

## Example workflow


## Planned for future versions

- `gt_curvify()` will add control points that round off corners so that the resulting geometry is a curve rather than a polygon/straight line,

- `gt_buffer()`, ...

- set operations for `geom`s
