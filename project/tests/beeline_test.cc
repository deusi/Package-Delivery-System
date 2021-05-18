#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include "../include/drone.h"
#include "../include/IStrategy.h"
#include <EntityProject/entity.h>
#include "json_helper.h"

#include <iostream>

//Using code from factory_test.cc to initialize the drone object.

namespace csci3081 {

using entity_project::IEntity;

class BeelineTest : public ::testing::Test {
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
    high_start.push_back(498.292);
    high_start.push_back(400);
    high_start.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", start);
    end.push_back(1);
    end.push_back(0);
    end.push_back(0);
    high_end.push_back(1);
    high_end.push_back(400);
    high_end.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", end);
    JsonHelper::AddStringToJsonObject(obj, "path", "beeline");
    drone = dynamic_cast<Drone*> (system->CreateEntity(obj));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
  Drone* drone;
  std::vector<float> start;
  std::vector<float> end;
  std::vector<float> high_start;
  std::vector<float> high_end;
  picojson::object obj;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

//Code from factory_test.cc, first asserts that drone was created properly
TEST_F(BeelineTest, DroneCreated) { 
  // Checks that the returned entity is not NULL
  ASSERT_NE(drone, nullptr) << "The entity created";
  system->AddEntity(drone);
  ASSERT_EQ(1, system->GetEntities().size());
  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

//Checks that drone has a path that is the correct size, then check each point along path
TEST_F(BeelineTest, PathInitializationTests) {
  drone->SetPath(start, end);
  ASSERT_EQ(drone->GetPath().size(), 5) << "Path of incorrect size";
  EXPECT_EQ(drone->GetPath()[0], start) << "Start point broken"; 
  EXPECT_EQ(drone->GetPath()[1], start) << "Second point broken";
  EXPECT_EQ(drone->GetPath()[2], high_start) << "Moving up broken";
  EXPECT_EQ(drone->GetPath()[3], high_end) << "Not above destination";
  EXPECT_EQ(drone->GetPath()[4], end) << "Didn't reach destination";
}



}  // namespace csci3081