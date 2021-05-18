#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include "../include/package.h"
#include <EntityProject/entity.h>
#include "json_helper.h"


#include <iostream>

//Using code from factory_test.cc to initialize the package object.

namespace csci3081 {

using entity_project::IEntity;

class PackageTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
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
    package = dynamic_cast<Package*> (system->CreateEntity(obj));


    cust_system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
    cust_obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(cust_obj, "type", "customer");
    JsonHelper::AddStringToJsonObject(cust_obj, "name", "customer");
    JsonHelper::AddFloatToJsonObject(cust_obj, "radius", 1.0);
    position_to_add.push_back(498.292);
    position_to_add.push_back(253.883);
    position_to_add.push_back(-228.623);
    JsonHelper::AddStdFloatVectorToJsonObject(cust_obj, "position", position_to_add);
    direction_to_add.push_back(1);
    direction_to_add.push_back(0);
    direction_to_add.push_back(0);
    JsonHelper::AddStdFloatVectorToJsonObject(cust_obj, "direction", direction_to_add);
    customer = dynamic_cast<Customer*> (system->CreateEntity(cust_obj));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
  IDeliverySystem* cust_system;
  Package* package;
  std::vector<float> position_to_add;
  std::vector<float> direction_to_add;
  picojson::object obj;
  Customer* customer;
  picojson::object cust_obj;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

//Code from factory_test.cc, first asserts that package was created properly
TEST_F(PackageTest, PackageCreated) {
  // Checks that the returned entity is not NULL
  ASSERT_NE(package, nullptr) << "The entity created";
  system->AddEntity(package);
  ASSERT_EQ(1, system->GetEntities().size());
  // Checks that when GetDetails() is called, the entity returns
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

}

//Checks that package is initialized properly and that getter functions work for Position, Direction, ID, and Name.
TEST_F(PackageTest, InitializationTests) {
  ASSERT_FLOAT_EQ(package->GetPosition()[0], position_to_add[0]) << "Position initialized incorrectly";
  ASSERT_FLOAT_EQ(package->GetPosition()[1], position_to_add[1]) << "Position initialized incorrectly";
  ASSERT_FLOAT_EQ(package->GetPosition()[2], position_to_add[2]) << "Position initialized incorrectly";

  ASSERT_FLOAT_EQ(package->GetInitialPosition()[0], position_to_add[0]) << "Initial Position initialized incorrectly";
  ASSERT_FLOAT_EQ(package->GetInitialPosition()[1], position_to_add[1]) << "Initial Position initialized incorrectly";
  ASSERT_FLOAT_EQ(package->GetInitialPosition()[2], position_to_add[2]) << "Initial Position initialized incorrectly";

  ASSERT_FLOAT_EQ(package->GetDirection()[0], direction_to_add[0]) << "Direction initialized incorrectly";
  ASSERT_FLOAT_EQ(package->GetDirection()[1], direction_to_add[1]) << "Direction initialized incorrectly";
  ASSERT_FLOAT_EQ(package->GetDirection()[2], direction_to_add[2]) << "Direction initialized incorrectly";

  EXPECT_EQ(package->GetId(), 2000) << "ID initialized incorrectly";

  EXPECT_EQ(package->GetName(), "package") << "Name initialized incorrectly";

  EXPECT_FLOAT_EQ(package->GetWeight(), 2.0) << "Weight initialized incorrectly";

  std::vector<float> dest{0.0, 0.0, 0.0};
  EXPECT_FLOAT_EQ(package->GetDestination()[0], dest[0]) << "Destination initialized incorrectly";
  EXPECT_FLOAT_EQ(package->GetDestination()[1], dest[1]) << "Destination initialized incorrectly";
  EXPECT_FLOAT_EQ(package->GetDestination()[2], dest[2]) << "Destination initialized incorrectly";
}

//Checks GetRadius, GetVersion, and IsDynamic, which shouldn't change during iteration 1.
TEST_F(PackageTest, OtherGetterTests) {
  EXPECT_EQ(package->GetRadius(), 1) << "Radius initialized incorrectly";
  EXPECT_EQ(package->GetVersion(), 0) << "Version initialized incorrectly";
  EXPECT_EQ(package->IsDynamic(), false) << "dynamic_ initialized incorrectly";
}

//Checks the setters
TEST_F(PackageTest, SetterTests) {
  //ID
  package->SetId(1095);
  EXPECT_EQ(package->GetId(), 1095) << "SetID incorrect";

  //Name
  package->SetName("Package_1095");
  EXPECT_EQ(package->GetName(), "Package_1095") << "SetName incorrect";

  //Status
  package->SetStatus("Fragile");
  EXPECT_EQ(package->GetStatus(), "Fragile") << "SetStatus incorrect";


  //Position
  std::vector<float> new_position;
  new_position.push_back(237.723);
  new_position.push_back(876.920);
  new_position.push_back(-793.124);
  package->SetPosition(new_position);
  EXPECT_FLOAT_EQ(package->GetPosition()[0], new_position[0]) << "SetPosition incorrect";
  EXPECT_FLOAT_EQ(package->GetPosition()[1], new_position[1]) << "SetPosition incorrect";
  EXPECT_FLOAT_EQ(package->GetPosition()[2], new_position[2]) << "SetPosition incorrect";

  //Weight
  package->SetWeight(10.0);
  EXPECT_FLOAT_EQ(package->GetWeight(), 10.0) << "SetWeight incorrect";

  //Dynamic
  package->SetDynamic(true);
  EXPECT_EQ(package->IsDynamic(), true) << "SetDynamic incorrect";
}

TEST_F(PackageTest, CustomerCheck){
  package->SetCustomer(customer);
  EXPECT_EQ(package->GetCustomer(), customer) << "SetCustomer incorrect";
  EXPECT_FLOAT_EQ(package->GetCustomerRadius(), 1.0) << "Customer Radius incorrect";
}

TEST_F(PackageTest, DeliveredTest){
  package->SetStatus("Delivered");
  package->Update();
  EXPECT_FLOAT_EQ(package->GetPosition()[0], 0.0) << "Update incorrect";
  EXPECT_FLOAT_EQ(package->GetPosition()[1], -10000.0) << "Update incorrect";
  EXPECT_FLOAT_EQ(package->GetPosition()[2], 0.0) << "Update incorrect";
}


}  // namespace csci3081
