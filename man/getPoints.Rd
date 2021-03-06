% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/getPoints.R
\name{getPoints}
\alias{getPoints}
\alias{getPoints,ANY-method}
\alias{getPoints,geom-method}
\alias{getPoints,Spatial-method}
\alias{getPoints,sf-method}
\alias{getPoints,ppp-method}
\alias{getPoints,Raster-method}
\alias{getPoints,matrix-method}
\title{Get the table of point attributes}
\usage{
\S4method{getPoints}{ANY}(x, ...)

\S4method{getPoints}{geom}(x, ...)

\S4method{getPoints}{Spatial}(x)

\S4method{getPoints}{sf}(x)

\S4method{getPoints}{ppp}(x)

\S4method{getPoints}{Raster}(x)

\S4method{getPoints}{matrix}(x)
}
\arguments{
\item{x}{the object from which to derive the attribute table.}

\item{...}{subset based on logical predicates defined in terms of the
columns in \code{x} or a vector of booleans. Multiple conditions are
combined with \code{&}. Only rows where the condition evaluates to TRUE are kept.}
}
\value{
A table of the point attributes of \code{x} or an object where the
  point table has been subsetted.
}
\description{
Get tabular information of the attributes of points (incl. coordinates).
}
\examples{
getPoints(x = gtGeoms$polygon)

getPoints(x = gtGeoms$point)

# for a raster object, the @point slot is extracted from its' compact storage
gtGeoms$grid$continuous@point
getPoints(x = gtGeoms$grid$continuous)
}
\seealso{
Other getters: 
\code{\link{getCRS}()},
\code{\link{getExtent}()},
\code{\link{getFeatures}()},
\code{\link{getGroups}()},
\code{\link{getHistory}()},
\code{\link{getLayer}()},
\code{\link{getName}()},
\code{\link{getRes}()},
\code{\link{getType}()},
\code{\link{getWindow}()}
}
\concept{getters}
