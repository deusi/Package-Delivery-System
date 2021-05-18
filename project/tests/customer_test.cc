#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include "../include/customer.h"
#include <EntityProject/entity.h>
#include "json_helper.h"


#include <iostream>

//Using code from factory_test.cc to initialize the customer object.

namespace csci3081 {

using entity_project::IEntity;

class CustomerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    //Creating a customer object using delivery system's create entity, which will also test 
    //the CustomerFactory class.
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
    obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    JsonHelper::AddStringToJsonObject(obj, "name", "customer");
    JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    customer = dynamic_cast<Customer*> (system->CreateEntity(obj));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
  Customer* customer;
  std::vector<float> position_to_add;
  std::vector<float> direction_to_add;
  picojson::object obj;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

//Code from factory_test.cc, first asserts that drone was created properly
TEST_F(CustomerTest, CustomerCreated) { 
  // Checks that the returned entity is not NULL
  ASSERT_NE(customer, nullptr) << "The entity created";
  system->AddEntity(customer);
  ASSERT_EQ(1, system->GetEntities().size());
  // Checks that when GetDetails() is called, the entity returns 
  // the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

//Checks that customer is initialized properly and that getter functions work for Position, Direction, ID, and Name.
TEST_F(CustomerTest, InitializationTests) {
  ASSERT_FLOAT_EQ(customer->GetPosition()[0], position_to_add[0]) << "Position initialized incorrectly";
  ASSERT_FLOAT_EQ(customer->GetPosition()[1], position_to_add[1]) << "Position initialized incorrectly";
  ASSERT_FLOAT_EQ(customer->GetPosition()[2], position_to_add[2]) << "Position initialized incorrectly";
  ASSERT_FLOAT_EQ(customer->GetDirection()[0], direction_to_add[0]) << "Direction initialized incorrectly";
  ASSERT_FLOAT_EQ(customer->GetDirection()[1], direction_to_add[1]) << "Direction initialized incorrectly";
  ASSERT_FLOAT_EQ(customer->GetDirection()[2], direction_to_add[2]) << "Direction initialized incorrectly";
  EXPECT_EQ(customer->GetId(), 3000) << "ID initialized incorrectly";
  EXPECT_EQ(customer->GetName(), "customer") << "Name initialized incorrectly";
}

//Checks GetRadius, GetVersion, and IsDynamic, which shouldn't change during iteration 2. 
TEST_F(CustomerTest, OtherGetterTests) {
  EXPECT_EQ(customer->GetRadius(), 1) << "Radius initialized incorrectly";
  EXPECT_EQ(customer->GetVersion(), 0) << "Version initialized incorrectly";
  EXPECT_EQ(customer->IsDynamic(), false) << "dynamic_ initialized incorrectly";
}

//Checks the setters
TEST_F(CustomerTest, SetterTests) {
  customer->SetId(1095);
  EXPECT_EQ(customer->GetId(), 1095) << "SetID incorrect";
 
  customer->SetStatus("Hungry");
  EXPECT_EQ(customer->GetStatus(), "Hungry");

  customer->SetName("Customer_1095");
  EXPECT_EQ(customer->GetName(), "Customer_1095") << "SetName incorrect";

  std::vector<float> new_position;
  new_position.push_back(237.723);
  new_position.push_back(876.920);
  new_position.push_back(-793.124);
  customer->SetPosition(new_position);
  EXPECT_FLOAT_EQ(customer->GetPosition()[0], new_position[0]) << "SetPosition incorrect";
  EXPECT_FLOAT_EQ(customer->GetPosition()[1], new_position[1]) << "SetPosition incorrect";
  EXPECT_FLOAT_EQ(customer->GetPosition()[2], new_position[2]) << "SetPosition incorrect";

  customer->SetDynamic(true);
  EXPECT_EQ(customer->IsDynamic(), true) << "SetDynamic incorrect";
}


}  // namespace csci3081
