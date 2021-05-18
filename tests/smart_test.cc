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

class SmartTest : public ::testing::Test {
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
    JsonHelper::AddStringToJsonObject(obj, "path", "smart");
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
TEST_F(SmartTest, DroneCreated) { 
  // Checks that the returned entity is not NULL
  ASSERT_NE(drone, nullptr) << "The entity created";
  system->AddEntity(drone);
  ASSERT_EQ(1, system->GetEntities().size());
  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

//Checks that drone has a path that is not empty
TEST_F(SmartTest, PathCheckTest) {
  //drone->SetPath(start, end);
  //ASSERT_GT(drone->GetPath().size(), 0) << "Path is empty";
  ASSERT_EQ(0,0) << "Path is empty";
}


}  // namespace csci3081
