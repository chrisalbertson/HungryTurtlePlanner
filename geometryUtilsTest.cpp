// geometryUtilsTest.cpp  - Unit test using Boost Test
#include "geometryUtils.h"

#define BOOST_TEST_MODULE test module name
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( getSlopeTest )
{
    BOOST_CHECK_EQUAL(  0.5, getSlope(point_t( 1.0,  1.0),point_t(  3.0,  2.0)) );
    BOOST_CHECK_EQUAL( -0.5, getSlope(point_t(-1.0,  1.0),point_t( -3.0,  2.0)) );
    BOOST_CHECK_EQUAL(  2.0, getSlope(point_t(-1.0, -1.0),point_t( -2.0, -3.0)) );
    BOOST_CHECK_EQUAL( -2.0, getSlope(point_t( 1.0, -1.0),point_t(  2.0, -3.0)) );

    BOOST_CHECK_EQUAL(  0.5, getSlope(point_t( 3.0,  2.0),point_t(  1.0,  1.0)) );
    BOOST_CHECK_EQUAL( -0.5, getSlope(point_t(-3.0,  2.0),point_t( -1.0,  1.0)) );

    BOOST_CHECK      ( 10000.0 <  getSlope(point_t( 2.0, 1.0),point_t(  2.0, 8.0)) );
    BOOST_CHECK_EQUAL(     0.0,   getSlope(point_t( 1.0, 1.0),point_t(  8.0, 1.0)) );
}
