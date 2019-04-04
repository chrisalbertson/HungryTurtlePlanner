#include "geometryUtils.cpp"
#include <gtest/gtest.h>

TEST(getSlopeTest, normalSlopes) {
    EXPECT_EQ( 1.0, getSlope(point_t(1.0, 1.0),point_t( 2.0, 2.0)));
    EXPECT_EQ(-1.0, getSlope(point_t(0.0, 0.0),point_t(-1.0, 1.0)));
    EXPECT_EQ( 2.0, getSlope(point_t(0.0, 0.0),point_t( 1.0, 2.0)));
    EXPECT_EQ( 0.5, getSlope(point_t(0.0, 0.0),point_t( 2.0, 1.0)));
}

TEST(getSlopeTest, horzVertSlopes) {
    EXPECT_EQ(       0.0, getSlope(point_t(1.0, 1.0),point_t( 1.0, 0.0)));
    EXPECT_EQ(10000000.0, getSlope(point_t(0.0, 0.0),point_t( 0.0, 1.0)));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}