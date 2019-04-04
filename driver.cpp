#include "plannerLow.h"

int main() {
    
    plannerLow planner;
    unsigned depth = 2;
    point_t  pathStart;
    point_t  pathTarget;
    unsigned score;

    planner.bestPath(depth, pathStart, &pathTarget, &score);
}