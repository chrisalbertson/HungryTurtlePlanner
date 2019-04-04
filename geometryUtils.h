/*! \file       geometryUtils.h
    \brief      Defines various utilty funtions and types from Boost Geometry.
    \author     Chris Albertson
    
    Details are TBD.
*/


#ifndef GEOMETRYUTILS_H
#define GEOMETRYUTILS_H


#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/linestring.hpp>

#include <boost/geometry/index/rtree.hpp>

#include <cmath>
#include <vector>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 2, bg::cs::cartesian> point_t;
typedef bg::model::box<point_t> box_t;
typedef bg::model::polygon<point_t, false, false> polygon_t; // ccw, open polygon
typedef bg::model::linestring<point_t> linestring_t;
typedef boost::shared_ptr<linestring_t> shp_t;
typedef std::pair<box_t, shp_t> value_t;


void slopeDist2Cartsian(float slope, float length, float* x, float* y);
/*! 
    Converts a slope and distance to (x,y).

    Note that "slope and distance" is different from the more common kind of
    polar coordinate which is angle and distance.
*/

void makeSegmentFromMidPt(float slope, float length, point_t midPt, 
                          point_t *pt1, point_t *pt2);

void makeLineEndPt(float slope, float length, point_t startPt, point_t *endPt);

float getSlope(point_t pt1, point_t pt2);

void makeRectAroundSegment(point_t pt1, point_t pt2, float width, polygon_t *rect);

#endif /* GEOMETRYUTILS_H */