/*! \file       driver.cpp
    \brief      Provides a "main()" to facilitate testing the plannerLow class.
    \author     Chris Albertson
    
    Details are TBD.
*/


#include "plannerLow.h"

int main() {
    
    plannerLow pl;
    ObstacleList obsList;

    unsigned depth = 0;
    point_t  pathStart;
    point_t  pathTarget;
    float    score = 100.0;


    obsList.add(point_t(-5,2), point_t(4,2));
    obsList.add(point_t(-5,5), point_t(0,5));
    obsList.add(point_t(-1,8), point_t(-1,11));
    obsList.add(point_t(-3,16), point_t(3,16));

    bg::assign_point(pathStart,  point_t(0.0,  0.0));
    bg::assign_point(pathTarget, point_t(0.0, 20.0)); 
    std::cout << bg::wkt(pathStart) << bg::wkt(pathTarget) << std::endl;

    for(int i=0; i<10; i++) {

        pl.bestPath(depth, pathStart, &pathTarget, &score);
        std::cout << bg::wkt(pathStart) << bg::wkt(pathTarget) << std::endl;
        bg::assign_point(pathStart,  pathTarget);
        bg::assign_point(pathTarget, point_t(0.0, 20.0));

    }
}