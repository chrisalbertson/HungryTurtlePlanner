# Low Level Path Planner
Plan a 2D path for a mobile robot given poor quality and uncertin data in a dynamically changing environment.

Many planners are designed to operate in an environment that is well mapped.   This planner attemps to operate as if if are an anamal with poor vision that is beig chases by a preditir through an area it has never been in before.  All thepoor animal can do is run in a general direct and and try not to colide with trees of run off a cliff.

It is assumed there is a high level path planner the gives this planner a "goal point" that is relitively close.  This planner will apply real-time sensor data to avoid colisions with obstacles.   We assume the sensor data is impresice and not well locaized.   The algorithm is like A* but with a recursion depth limit that may stop the serch before it finds a complete path.    But thinking again about or animal, It does not know its exact location. It can only run it the general directin of "safety" while trying to aviod only what it can see.  