/*! \file       obstacles.h
    \brief      Defines defines a class to maintain a list of physical obstacles.
    \author     Chris Albertson
    
    Details are TBD.
*/


#ifndef OBSTACLES_H
#define OBSTACLES_H


#include "geometryUtils.h"

class ObstacleList {
public:

    // static bgi::rtree< value_t, bgi::linear<16, 4> > _rtree;

    ObstacleList(){};

    void add(point_t p1, point_t p2);

    unsigned getCount();

    //unsigned getAll(std::vector<value_t> *result_vec)

    void printInBox(box_t boundingBox);

    unsigned getInPolygon(polygon_t boundingPoly, 
                          std::vector<value_t> *result_vec);

    void printInPolygon(polygon_t boundingPoly);

    void printNearPoint(point_t referencePoint, unsigned count);

// private:
    static bgi::rtree< value_t, bgi::linear<16, 4> > _rtree; 
};

#endif /* OBSTACKES_H */