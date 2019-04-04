cmake_minimum_required(VERSION 2.6)
project(driver)

enable_testing()

set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard
add_executable (driver driver.cpp geometryUtils.cpp obstacles.cpp plannerLow.cpp)

add_executable(geometryUtilsTest geometryUtilsTest.cpp geometryUtils.cpp) 
add_test(NAME getSlopeTest COMMAND geometryUtilsTest)