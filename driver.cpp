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

    planner.bestPath(depth, pathStart, &pathTarget, &score);
}