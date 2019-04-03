cmake_minimum_required(VERSION 2.6)
project(driver)
set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard
add_executable (driver driver.cpp  geometryUtils.cpp  geometryUtilsTest.cpp  obstacles.cpp  plannerLow.cpp)