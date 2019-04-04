#include "plannerLow.h"
#include "obstacles.h"
#include "geometryUtils.h"


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

// ObstacleList obstacles;

void plannerLow::bestPath(unsigned depth, point_t pathStart, point_t *pathTarget, float *score){

    // To prevent infinate recurion a depth limit is enforced.
    // At the depth limit we return with the target point set to
    // the start point, which means "do not move" and we return a very
    // poor score.
    if (depth == depthLimit) {
        *score = 100.0;
        *pathTarget = pathStart;
        return;
    }

    // Find the direct path to the target, built a rectanga aroud this
    // path and look for obstatcles that fall into this rectagagle.
    // If the path is clear, we return this path and a high score.
    polygon_t pathPoly;
    makeRectAroundSegment(pathStart, *pathTarget, vehicleWidth, &pathPoly);
    
    std::vector<value_t> obsVec;
    unsigned obsCount = obstacles->getInPolygon(pathPoly, &obsVec);

    if (obsCount == 0) {

        // Looks like we can reach the goal on one shot. A "straight shot"
        // score is zero
        *score += 0.0;
        // *pathTarget to remain unchanged, We can reach it directly

    }
    else {

        // One or more obstacles is in the way between the robot and the goal.  
        // In this case we compute the score based on the fraction of the 
        // distance to the goal we can drive.   We need the total distance
        // so that we can compute the fractions later.
        float distStartToGoal = bg::distance(pathStart, *pathTarget);
        std::vector<point_t> osbEndPtVec;

        // For each obstacle between curent location and the goal we
        // check each obstacle-endpoint to see if we can drive directly to it.
        // We only concider obstacles that are not blocked by other obstacles.
        // we collect a vector of end points
        BOOST_FOREACH(value_t obs, obsVec) {

            linestring_t ls = *(obs.second);
            point_t p1 = ls.front();
            point_t p2 = ls.back();
            float obsSlope;
            point_t extendedPt;
            float pathOffset = 0.55 * vehicleWidth; // just over 1/2. 

            // extend the obstacle (at p1 end) by 1/2 the vehicle width
            obsSlope = getSlope(p2, p1);
            makeLineEndPt(obsSlope, pathOffset, p1, &extendedPt);
            osbEndPtVec.push_back(extendedPt);

            // extend the obstacle (at p1 end) by 1/2 the vehicle width
            obsSlope = getSlope(p2, p1);
            makeLineEndPt(obsSlope, pathOffset, p1, &extendedPt);
            osbEndPtVec.push_back(extendedPt);
        }

        // osbEndPtVec now holds the vector of points we can directly
        // drive to.   Next we choose the point that puts us in the
        // best place relative to the goal.
        float s;
        float sMin = 9E20f;  // initialize to impossibly large value
        point_t ptMin;
        BOOST_FOREACH(point_t pt, osbEndPtVec){
            float distToGo = bg::distance(pt, pathTarget);
            //TODO: Need to "look" if path is blocked and compute a more
            // meaningful score.  But for now this much just might work
            // let's try and see...
            s = distToGo / distStartToGoal;  // this is the "score"
            if (s < sMin){
                sMin = s;
                bg::assign_point(ptMin, pt);
            }
        }
        *score = sMin; 
        bg::assign_point(*pathTarget, ptMin);
    }
return;
}
