/*! \file       driver.cpp
    \brief      Provides a "main()" to facilitate testing the plannerLow class.
    \author     Chris Albertson
    
    Details are TBD.
*/


#include "plannerLow.h"

int main() {
    
    plannerLow planner;
    unsigned depth = 2;
    point_t  pathStart;
    point_t  pathTarget;
    float    score;



    point_t endPt;
    point_t p1{0.0, 0.0};


    makeLineEndPt(1.0, 10.0, p1, &endPt);
    float d = bg::distance(p1, endPt);
    std::cout << endPt.get<0>() << "  " << endPt.get<1>() << "  " << d;

    planner.bestPath(depth, pathStart, &pathTarget, &score);
}