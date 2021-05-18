#include "gtest/gtest.h"
#include "../include/vector3D.h"

#include <iostream>

namespace csci3081 {

class Vector3DTest : public ::testing::Test {
    public:
        void SetUp() {}
        void TearDown() {}
    protected:
        Vector3D zero_3D_vec = Vector3D(0.0, 0.0, 0.0);
        Vector3D unit_x_vec = Vector3D(1.0, 0.0, 0.0);
        Vector3D unit_y_vec = Vector3D(0.0, 1.0, 0.0);
        Vector3D unit_z_vec = Vector3D(0.0, 0.0, 1.0);
        Vector3D rand_vec_1 = Vector3D(21.1781, 6.29359, 11.28419);
        Vector3D test_vec_1 = Vector3D(9.0, 12.0, 20.0);
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

//Testing GetX,Y,Z
TEST_F(Vector3DTest, CoordinateGetterTests) {
    EXPECT_FLOAT_EQ(rand_vec_1.GetX(), 21.1781) << "GetX failed";
    EXPECT_FLOAT_EQ(rand_vec_1.GetY(), 6.29359) << "GetY failed";
    EXPECT_FLOAT_EQ(rand_vec_1.GetZ(), 11.28419) << "GetZ failed";
}

//Testing SetMagnitude function, called while initializing the vector.
TEST_F(Vector3DTest, MagnitudeTest) {
    EXPECT_FLOAT_EQ(zero_3D_vec.GetMagnitude(), 0.0) << "Zero Vec magnitude failed";
    EXPECT_FLOAT_EQ(unit_x_vec.GetMagnitude(), 1.0) << "Unit X Vec magnitude failed";
    EXPECT_FLOAT_EQ(unit_y_vec.GetMagnitude(), 1.0) << "Unit Y Vec magnitude failed";
    EXPECT_FLOAT_EQ(unit_z_vec.GetMagnitude(), 1.0) << "Unit Z Vec magnitude failed";
    EXPECT_FLOAT_EQ(test_vec_1.GetMagnitude(), 25.0) << "9-12-20 Vec magnitude failed";
}

//Testing Direction function, called while initializing the vector.
TEST_F(Vector3DTest, DirectionTest) {
    ASSERT_EQ(zero_3D_vec.GetDirection().size(), 3) << "Direction vector has incorrect length";
    ASSERT_EQ(test_vec_1.GetDirection().size(), 3) << "Direction vector has incorrect length";
    std::vector<float> dir_1{0.0, 0.0, 0.0};
    std::vector<float> dir_2{0.36, 0.48, 0.80};
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(zero_3D_vec.GetDirection()[i], dir_1[i]) << "Direction vector is wrong at index " << i;
    }
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(test_vec_1.GetDirection()[i], dir_2[i]) << "Direction vector is wrong at index " << i;
    }
}

//Testing UpdateVector
TEST_F(Vector3DTest, UpdateVectorTest) {
    rand_vec_1.UpdateVector(-9.0, 12.0, -20.0);
    EXPECT_FLOAT_EQ(rand_vec_1.GetX(), -9.0) << "UpdateVector failed to update X";
    EXPECT_FLOAT_EQ(rand_vec_1.GetY(), 12.0) << "UpdateVector failed";
    EXPECT_FLOAT_EQ(rand_vec_1.GetZ(), -20.0) << "UpdateVector failed to update Z";
    EXPECT_FLOAT_EQ(rand_vec_1.GetMagnitude(), 25) << "Failed to update magnitude";
    
    std::vector<float> dir{-0.36, 0.48, -0.80};
    ASSERT_EQ(rand_vec_1.GetDirection().size(), 3) << "Direction vector has incorrect length";
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(rand_vec_1.GetDirection()[i], dir[i]) << "Direction vector is wrong at index " << i;
    }
}

}