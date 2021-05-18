#include "gtest/gtest.h"
#include "../include/battery.h"

#include <iostream>

namespace csci3081 {

class BatteryTest : public ::testing::Test {
    public:
        void SetUp() {}
        void TearDown() {}
    protected:
        Battery battery_1;
        Battery battery_2 = Battery(500);
        Battery battery_3 = Battery(-10);
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

//Checks that batteries are initialized properly and that GetMaxCharge/CheckEmpty works
TEST_F(BatteryTest, InitializationTests) {
    EXPECT_FLOAT_EQ(battery_1.GetMaxCharge(), 10000) << "Max Charge initialization failed";
    EXPECT_FLOAT_EQ(battery_2.GetMaxCharge(), 500) << "Max Charge initialization failed";
    EXPECT_FLOAT_EQ(battery_3.GetMaxCharge(), 1) << "Max Charge initialization failed";
    EXPECT_EQ(battery_1.CheckEmpty(), false) << "Initialization of empty failed";
    EXPECT_EQ(battery_2.CheckEmpty(), false) << "Initialization of empty failed";
    EXPECT_EQ(battery_3.CheckEmpty(), false) << "Initialization of empty failed";
    EXPECT_FLOAT_EQ(battery_1.GetCharge(), 10000) << "Curr Charge initialization failed";
    EXPECT_FLOAT_EQ(battery_2.GetCharge(), 500) << "Curr Charge initialization failed";
    EXPECT_FLOAT_EQ(battery_3.GetCharge(), 1) << "Curr Charge initialization failed";
}

//Checks if the UpdateCharge function has the correct behavior.
TEST_F(BatteryTest, UpdateTests) {
    battery_2.UpdateBattery(300);
    EXPECT_FLOAT_EQ(battery_2.GetCharge(), 200) << "Update Charge failed";
    EXPECT_EQ(battery_2.CheckEmpty(), false) << "Update Charge failed";
    battery_2.UpdateBattery(200);
    EXPECT_FLOAT_EQ(battery_2.GetCharge(), 0) << "Update Charge failed";
    EXPECT_EQ(battery_2.CheckEmpty(), true) << "Update Charge failed";
    battery_2.UpdateBattery(2);
    EXPECT_FLOAT_EQ(battery_2.GetCharge(), 0) << "Update Charge failed";
    EXPECT_EQ(battery_2.CheckEmpty(), true) << "Update Charge failed";
}

//Checks SetMaxCharge.
TEST_F(BatteryTest, SetterTests) {
    battery_3.SetMaxCharge(1000);
    EXPECT_FLOAT_EQ(battery_3.GetMaxCharge(), 1000) << "Max Charge setter failed";
}

} //namespace csci3081