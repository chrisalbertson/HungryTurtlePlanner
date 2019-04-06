/*! \file       driver.cpp
    \brief      Provides a "main()" to facilitate testing the plannerLow class.
    \author     Chris Albertson
    
    Details are TBD.
*/


#include "plannerLow.h"

int main() {
    
    plannerLow pl;
    unsigned depth = 2;
    point_t  pathStart;
    point_t  pathTarget;
    float    score;

    polygon_t rect;
    makeRectAroundSegment(point_t(0.0, 0.0), point_t(1.0, 100.0), 1.0, &rect);
    std::cout << bg::wkt(rect) << std::endl;

    makeRectAroundSegment(point_t(0.0, 0.0), point_t(4.0, 2.0), 1.0, &rect);
    std::cout << bg::wkt(rect) << std::endl;


    makeRectAroundSegment(point_t(0.0, 0.0), point_t(-2.0, 4.0), 1.0, &rect);
    std::cout << bg::wkt(rect) << std::endl;



    pl.bestPath(depth, pathStart, &pathTarget, &score);
}