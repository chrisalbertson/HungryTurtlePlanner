cmake_minimum_required(VERSION 2.6)
project(driver)
enable_testing()
set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable (driver driver.cpp geometryUtils.cpp obstacles.cpp plannerLow.cpp)

add_executable(geometryUtilsTest geometryUtilsTest.cpp                              geometryUtils.cpp)
add_executable(    obstaclesTest     obstaclesTest.cpp                obstacles.cpp geometryUtils.cpp) 
add_executable(   plannerLowTest    plannerLowTest.cpp plannerLow.cpp obstacles.cpp geometryUtils.cpp) 

add_test(NAME geometryUtilsTest  COMMAND geometryUtilsTest)
add_test(NAME obstaclesTest      COMMAND obstaclesTest)
add_test(NAME plannerLowTest     COMMAND plannerLowTest)