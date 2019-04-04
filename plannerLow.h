#ifndef PLANNERLOW_H
#define PLANNERLOW_H

#include "geometryUtils.h"
#include "obstacles.h"


class plannerLow {
public:
    plannerLow(){
        depthLimit   = 3;
        vehicleWidth = 1.0;  // meters.  TODO: use the real value

        obstacles = new(ObstacleList);
    }

    // This planner works at the lowest level.  It is assumed there is a
    // higher level planner.  Perhaps a human or software but in either case
    // it gives this planner a goal point that is only some meters away and
    // within perhaps under half a minute of driving time.
    //
    // This planner is designed to work with poor quality and low resulution
    // information that might even be wrong.  The planner maintains a list of "obstacles"
    // that are observed in real-time with various sensors.  It uses a simple
    // Hueristic algorithm to attempt to drive around these observed obstacles.
    // The algorithum was designed assuming the list of observed obstacles
    // will be in constant flux both because some of them might be movoing
    // objects and because the sensor will "see" differenty as the robot move
    // to different locations



    // Find the best path from current location to target loaction
    // while avoiding contact with known obstacles.
    //
    // This function is recursive.  It will call itself up to a depth limit to
    // find a "promisoing" route to a target then it returns the first point on
    // that route.   This funtion may (and should be) called very frquenty.  In
    // most cases weel before reachig the taget.  It will replan each time it
    // is called so as sensors gather more and better data the route will be 
    // revised.
    //

    // A scoring system is used to select a better route.   The score can
    // be throught of as a cost.  "Zero" is the best possible score it means
    // the target canbe reached directly by a straight open path.  A less-good 
    // route is one that requires traveling to some out of the way waypoints
    // and some turns at each waypoint.   The score roughy equals the number of
    // turns required.   

    // Summary of the algorithm:
    // We first check if a direct path is possible.  If it is we retun
    // that and a scoere of zero.
    // if there are obstacles in the path we consider driving to the end points
    // of each obstivcle and then we recursivly look to see if the goal
    // can be reached.   Than we take the sortest most direct path.
    // We do NOT recursivly search to a complete solution. We stop looking
    // after a recursive depth limit is reason.   the reasoning for this is that
    // the list  of obstacles is not complet or of good enough quality to
    // allow a comlete solution.  and in the process of moving more data will be
    // collected and we based future planning on this new data.

    void bestPath(unsigned depth, point_t pathStart,point_t *pathTarget, unsigned *score);

private:
    unsigned depthLimit;
    point_t curentLocation;
    point_t targetLocation;

    ObstacleList *obstacles;

    unsigned vehicleWidth;
};

#endif /* PLANNERLOW_H */