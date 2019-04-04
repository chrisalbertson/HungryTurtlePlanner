
#include "geometryUtils.h"

void slopeDist2Cartsian(float slope, float length, float* x, float* y){

    
    float h = 0.0;
    float v = 0.0;
    float angle;

    // Look for the special cases of a vertical or horizontal line
    if ( slope > 100000.0){
        // the slope is vertical
        v = length;
    }
    else if (slope < 0.000001){
        // the slope is horizontal
        h = length;
    }
    else {
        angle = atan(slope);
        h = cos(angle) * (length);
        v = sin(angle) * (length);
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
    
    slopeDist2Cartsian(slope, length/2.0, &x, &y);

    // set return values
    endPt->set<0>(startX + x);
    endPt->set<1>(startY + y);
}


float getSlope(point_t pt1, point_t pt2){
    float rise;
    float run;

    rise = pt2.get<0>() - pt1.get<0>();
    run  = pt2.get<1>() - pt1.get<1>();
    return (rise/run);
}


void makeRectAroundSegment(point_t pt1, point_t pt2, float width, polygon_t *rect){

    float slope = getSlope(pt1, pt2);
    point_t v1;
    point_t v2;
    point_t v3;
    point_t v4;

    makeSegmentFromMidPt(slope, width, pt1, &v1, &v2);
    makeSegmentFromMidPt(slope, width, pt2, &v4, &v3);

    // clear of the ploygon (just in case) then att the four corners.
    // TODO: figure out of the starting point needs to be repeated at the end.
    //       Do we need to append v1 again?
    rect->clear();
    bg::append(rect->outer(), v1);
    bg::append(rect->outer(), v2);
    bg::append(rect->outer(), v3);
    bg::append(rect->outer(), v4);
}   
