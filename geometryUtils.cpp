/*! \file       geometryUtils.cpp
    \brief      Implements funtions defined in geometryUtils.h.
    \author     Chris Albertson
    
    Details are TBD.
*/

#include <math.h>
#include "geometryUtils.h"

void slopeDist2Cartsian(float slope, float distance, float* x, float* y){

    
    float h = 0.0;
    float v = 0.0;
    float angle;

    // Look for the special cases of a vertical or horizontal line
    if ( slope > 100000.0){
        // the slope is vertical
        v = distance;
    }
    else if (fabs(slope) < 0.000001){
        // the slope is horizontal
        h = distance;
    }
    else {
        angle = atan(slope);
        h = cos(angle) * (distance);
        v = sin(angle) * (distance);
    }
    *x = h;
    *y = v;
}

void makeSegmentFromMidPt(float slope, float length, point_t midPt, point_t *pt1, point_t *pt2){
    
    float midX = midPt.get<0>();
    float midY = midPt.get<1>();
    float x;
    float y;
    
    slopeDist2Cartsian(slope, length/2.0, &x, &y);

    // set return values
    pt1->set<0>(midX - x);
    pt1->set<1>(midY - y);
    pt2->set<0>(midX + x);
    pt2->set<1>(midY + y);
}


void makeLineEndPt(float slope, float length, point_t startPt, point_t *endPt){
    
    float startX = startPt.get<0>();
    float startY = startPt.get<1>();
    float x;
    float y;
    
    slopeDist2Cartsian(slope, length, &x, &y);

    // set return values
    endPt->set<0>(startX + x);
    endPt->set<1>(startY + y);
}


float getSlope(point_t pt1, point_t pt2){
    float rise;
    float run;

    run  = pt2.get<0>() - pt1.get<0>();
    rise = pt2.get<1>() - pt1.get<1>();

    if (0.0 == run) {
        return 1E20f;  // Any big number will do
    }
    else {
        return (rise/run);
    }
}


void makeRectAroundSegment(point_t pt1, point_t pt2, float width, polygon_t *rect){

    float slope = -1.0 / getSlope(pt1, pt2); // slope of end segments
    point_t v1;
    point_t v2;
    point_t v3;
    point_t v4;

    makeSegmentFromMidPt(slope, width, pt1, &v1, &v2);
    makeSegmentFromMidPt(slope, width, pt2, &v4, &v3);

    // clear of the ploygon (just in case) then add the four corners.
    // TODO: figure out if the starting point needs to be repeated at the end.
    //       Do we need to append v1 again?
    rect->clear();
    bg::append(rect->outer(), v1);
    bg::append(rect->outer(), v2);
    bg::append(rect->outer(), v3);
    bg::append(rect->outer(), v4);
}   

// assuma a line AB.  If you stand on A and loob at B is point C to the left?
// returns 1 if C is left, -1 if C is to the right
//
// The expression is zero if the point is colinear and is treated as being
// "not to the left" and -1 is returned
bool isLeft(point_t a, point_t b, point_t c) {

    float Ax = a.get<0>();
    float Ay = a.get<1>();
    float Bx = b.get<0>();
    float By = b.get<1>();
    float Cx = c.get<0>();
    float Cy = c.get<1>();

    float location = (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax);

    if (location > 0.0) {
        return 1;
    }
    else {
        return 0;
    }
}