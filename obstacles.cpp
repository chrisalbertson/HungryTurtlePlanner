/*! \file       obstacles.cpp
    \brief      Implements funtions defined in obstacles.h.
    \author     Chris Albertson
    
    Details are TBD.
*/


#include "obstacles.h"


// This class uses a large STATIC data structure to hold a reperesentation
// of obstacles in the real world.   All uses of this class will be seeing
// the same set of obstacles.

// There are a few basic kinds of users of this class
// 1) Sensors -- a sensors observes an obstacle the adds it to the set or
//               the sesor sees the space is claer and removes obstacles
//               that were in the now clear space.
// 2) Panners -- A planner looks at the current set of abstacles and attemps
//               to plan a path to some goal.
// 3) Mantainance  -- a mantainance process is one that removes older
//               observations, mearges reduncent obstacles and or otherwise
//               keeps the structure effiscent.
//
// Again, all instances of this call use the same STATIC data as there is
// only one "real world" that needs to be represneted


void ObstacleList::add(point_t p1, point_t p2){

    // create a shared pointer to a new linestring and add the points
    shp_t ls(new linestring_t());
    bg::append(*ls, p1); 
    bg::append(*ls, p2);

    // Add the linestring and a box used as its index
    box_t boundingBox = bg::return_envelope<box_t>(*ls);
    _rtree.insert(std::make_pair(boundingBox, ls));
}

unsigned ObstacleList::getCount(){
    return _rtree.size();
}

void ObstacleList::printInBox(box_t boundingBox){

    // find values intersecting the area defined by boundingBox
    std::vector<value_t> result_n;
    _rtree.query(bgi::intersects(boundingBox), std::back_inserter(result_n));

    std::cout << "Lines intersecting box are:" << std::endl;
    BOOST_FOREACH(value_t const& v, result_n)
        std::cout << bg::wkt<linestring_t>(*v.second) << std::endl;
}

/*
void printInPolygon(polygon_t boundingPoly){

    // find values intersecting the area defined by bounding polygon
    std::vector<value_t> result_n;
    _rtree.query(bgi::intersects(boundingPoly), std::back_inserter(result_n));

    std::cout << "Lines intersecting polygon are:" << std::endl;
    BOOST_FOREACH(value_t const& v, result_n)
        std::cout << bg::wkt<linestring_t>(*v.second) << std::endl;
}
*/

unsigned ObstacleList::getInPolygon(polygon_t boundingPoly, 
                        std::vector<value_t> *result_vec){

    // find values intersecting the area defined by bounding polygon
    _rtree.query(bgi::intersects(boundingPoly), 
                    std::back_inserter(*result_vec));

    return result_vec->size();
}

void ObstacleList::printInPolygon(polygon_t boundingPoly){

    // find values intersecting the area defined by bounding polygon
    std::vector<value_t> result_n;
    getInPolygon(boundingPoly, &result_n);

    std::cout << "Lines intersecting polygon are:" << std::endl;
    BOOST_FOREACH(value_t const& v, result_n)
        std::cout << bg::wkt<linestring_t>(*v.second) << std::endl;
}

void ObstacleList::printNearPoint(point_t referencePoint, unsigned count){

    std::vector<value_t> result_n;
    _rtree.query(bgi::nearest(referencePoint, count), std::back_inserter(result_n));

    std::cout << "nearest lines are:" << std::endl;
    BOOST_FOREACH(value_t const& v, result_n)
        std::cout << bg::wkt<linestring_t>(*v.second) << std::endl;
}
