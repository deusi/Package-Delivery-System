#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include "../include/drone.h"
#include <EntityProject/entity.h>
#include "json_helper.h"


#include <iostream>

//Using code from factory_test.cc to initialize the drone object.

namespace csci3081 {

using entity_project::IEntity;

class ParabolicTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
    obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj, "name", "drone");
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
    start.push_back(498.292);
    start.push_back(253.883);
    start.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", start);
    end.push_back(1);
    end.push_back(0);
    end.push_back(0);
    midpoint.push_back(start[0] + (end[0]-start[0])/2);
    midpoint.push_back(start[1] + (end[0]-start[0])/2 + 50.0);
    midpoint.push_back(start[2] + (end[2]-start[2])/2);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", end);
    JsonHelper::AddStringToJsonObject(obj, "path", "parabolic");
    drone = dynamic_cast<Drone*> (system->CreateEntity(obj));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
  Drone* drone;
  std::vector<float> start;
  std::vector<float> end;
  std::vector<float> midpoint;
  picojson::object obj;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

//Code from factory_test.cc, first asserts that drone was created properly
TEST_F(ParabolicTest, DroneCreated) { 
  // Checks that the returned entity is not NULL
  ASSERT_NE(drone, nullptr) << "The entity created";
  system->AddEntity(drone);
  ASSERT_EQ(1, system->GetEntities().size());
  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

//Checks that drone has a path that is the correct size, then check beginning and end, and make sure some properties hold
TEST_F(ParabolicTest, PathCheckest) {
  drone->SetPath(start, end);
  ASSERT_EQ(drone->GetPath().size() % 2, 0) << "Path is not even";
  EXPECT_EQ(drone->GetPath()[0], start) << "Start point broken"; 
  EXPECT_EQ(drone->GetPath().back(), end) << "End point broken";
  //check to see that height is increasing from index 0 to midpoint
  for (int i=1; i<(drone->GetPath().size()/2); i++){
      EXPECT_GE(drone->GetPath()[i][1], drone->GetPath()[i-1][1]) << "Going up broken";
  }
  //check midpoint coordinates 
  EXPECT_NEAR(drone->GetPath()[drone->GetPath().size()/2 - 1][0], midpoint[0], 0.05) << "Midpoint x coordinate correct";
  EXPECT_NEAR(drone->GetPath()[drone->GetPath().size()/2 - 1][2], midpoint[2], 0.05) << "Midpoint y coordinate correct";

  //check to see that height is decreasing from midpoint to end
  for (int i=501; i<(drone->GetPath().size()-1); i++){
      EXPECT_LE(drone->GetPath()[i][1], drone->GetPath()[i-1][1]) << "Going down broken";
  }
}



}  // namespace csci3081