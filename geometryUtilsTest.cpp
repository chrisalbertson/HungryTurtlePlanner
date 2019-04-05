/*! \file       geometryUtilsTest.cpp
    \brief      Defines unit tests for geometryUtils using Boost Test.
    \author     Chris Albertson
    
    Details are TBD.
*/

#include "geometryUtils.h"

#define BOOST_TEST_MODULE  geometryUtils test module
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(geometryUtilsSuite)

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

// void makeLineEndPt(float slope, float length, point_t startPt, point_t *endPt)
BOOST_AUTO_TEST_CASE( makeLineEndPtTest ) 
{
    point_t endPt;
    point_t p1{0.0, 0.0};
    makeLineEndPt(1.0, 10.0, p1, &endPt);
    float d = bg::distance(p1, endPt);
    BOOST_CHECK_EQUAL( 10.0, d);
}

// void slopeDist2Cartsian(float slope, float length, float* x, float* y)
BOOST_AUTO_TEST_CASE( slopeDist2CartsianTest ) 
{
    float x;
    float y;
    slopeDist2Cartsian(1.0f, 1.0f, &x, &y);
    BOOST_CHECK_CLOSE_FRACTION(0.707106f, x, 0.001);
    BOOST_CHECK_CLOSE_FRACTION(0.707106f, y, 0.001);
}

//void makeSegmentFromMidPt(float slope, float length, point_t midPt, point_t *pt1, point_t *pt2)
BOOST_AUTO_TEST_CASE( makeSegmentFromMidPtTest ) 
{
    point_t midPt{0.0f, 0.0f};
    point_t p1;
    point_t p2;
    makeSegmentFromMidPt(1.0f, 2.0f, midPt, &p1, &p2);
    float d1 = bg::distance(point_t(-0.707106, -0.707106), p1);
    float d2 = bg::distance(point_t( 0.707106,  0.707106), p2);
    BOOST_CHECK( d1 < 0.001);
    BOOST_CHECK( d2 < 0.001);
}

BOOST_AUTO_TEST_SUITE_END()