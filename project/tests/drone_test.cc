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

class DroneTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
    obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj, "name", "drone");
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    drone = dynamic_cast<Drone*> (system->CreateEntity(obj));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
  Drone* drone;
  std::vector<float> position_to_add;
  std::vector<float> direction_to_add;
  picojson::object obj;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

//Code from factory_test.cc, first asserts that drone was created properly
TEST_F(DroneTest, DroneCreated) {
  // Checks that the returned entity is not NULL
  ASSERT_NE(drone, nullptr) << "The entity created";
  system->AddEntity(drone);
  ASSERT_EQ(1, system->GetEntities().size());
  // Checks that when GetDetails() is called, the entity returns
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

//Checks that drone is initialized properly and that getter functions work for Position, Direction, ID, and Name.
TEST_F(DroneTest, InitializationTests) {
  ASSERT_FLOAT_EQ(drone->GetPosition()[0], position_to_add[0]) << "Position initialized incorrectly";
  ASSERT_FLOAT_EQ(drone->GetPosition()[1], position_to_add[1]) << "Position initialized incorrectly";
  ASSERT_FLOAT_EQ(drone->GetPosition()[2], position_to_add[2]) << "Position initialized incorrectly";
  ASSERT_FLOAT_EQ(drone->GetDirection()[0], direction_to_add[0]) << "Direction initialized incorrectly";
  ASSERT_FLOAT_EQ(drone->GetDirection()[1], direction_to_add[1]) << "Direction initialized incorrectly";
  ASSERT_FLOAT_EQ(drone->GetDirection()[2], direction_to_add[2]) << "Direction initialized incorrectly";
  EXPECT_EQ(drone->GetId(), 1000) << "ID initialized incorrectly";
  EXPECT_EQ(drone->GetName(), "drone") << "Name initialized incorrectly";
  EXPECT_EQ(drone->GetNumDeliveries(), 0) << "Number of deliveries initialized incorrectly";
  EXPECT_EQ(drone->GetStatus(), "Idle") << "Status initialized incorrectly";
}

//Checks GetRadius, GetVersion, and IsDynamic, which shouldn't change during iteration 2.
TEST_F(DroneTest, OtherGetterTests) {
  EXPECT_EQ(drone->GetRadius(), 1) << "Radius initialized incorrectly";
  EXPECT_EQ(drone->GetVersion(), 0) << "Version initialized incorrectly";
  EXPECT_EQ(drone->IsDynamic(), false) << "dynamic_ initialized incorrectly";
}

//Checks the setters
TEST_F(DroneTest, SetterTests) {
  drone->SetId(1095);
  EXPECT_EQ(drone->GetId(), 1095) << "SetID incorrect";

  drone->SetName("Drone_1095");
  EXPECT_EQ(drone->GetName(), "Drone_1095") << "SetName incorrect";

  std::vector<float> new_position;
  new_position.push_back(237.723);
  new_position.push_back(876.920);
  new_position.push_back(-793.124);
  drone->SetPosition(new_position);
  EXPECT_FLOAT_EQ(drone->GetPosition()[0], new_position[0]) << "SetPosition incorrect";
  EXPECT_FLOAT_EQ(drone->GetPosition()[1], new_position[1]) << "SetPosition incorrect";
  EXPECT_FLOAT_EQ(drone->GetPosition()[2], new_position[2]) << "SetPosition incorrect";

  drone->SetDynamic(true);
  EXPECT_EQ(drone->IsDynamic(), true) << "SetDynamic incorrect";
}

//Testing the AddDelivery method.
TEST_F(DroneTest, AddDeliveryTest) {
  system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
  obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "package");
  JsonHelper::AddStringToJsonObject(obj, "name", "package");
  JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  Package* package = dynamic_cast<Package*> (system->CreateEntity(obj));
  EXPECT_FLOAT_EQ(drone->GetUnassignedCapacity(), 10.0) << "Weight issues without package";
  drone->AddDelivery(package);
  EXPECT_EQ(drone->GetNumDeliveries(), 1) << "Did not add package";
  EXPECT_FLOAT_EQ(drone->GetUnassignedCapacity(), 8.0) << "Weight issues with second package";
  drone->AddDelivery(package);
  EXPECT_EQ(drone->GetNumDeliveries(), 2) << "Did not add second package";
  EXPECT_FLOAT_EQ(drone->GetUnassignedCapacity(), 6.0) << "Weight issues with second package";
  drone->AddDelivery(package);
  EXPECT_EQ(drone->GetNumDeliveries(), 3) << "Did not add third package";
  EXPECT_FLOAT_EQ(drone->GetUnassignedCapacity(), 4.0) << "Weight issues with third package";
}

}  // namespace csci3081
