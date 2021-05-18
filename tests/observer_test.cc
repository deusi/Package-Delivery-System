#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <EntityProject/entity_observer.h>


#include <iostream>

namespace csci3081 {

class TestObserver: public entity_project::IEntityObserver {
    public:
        ~TestObserver() override {}
        void OnEvent(const picojson::value& event, const IEntity& entity) override{
            event_last = event;
            entity_last = entity;
        }
        picojson::value& event_last;
        IEntity& entity_last;
};

using entity_project::IEntity;


class ObserverTest: public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
    factory = new CompositeFactory();
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
  CompositeFactory* factory;
  TestObserver* test_observer;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(ObserverTest, SetupFactoryAndTestObservers) {
  factory->AddFactory(new PackageFactory);
  factory->AddFactory(new DroneFactory);

  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "drone");
  JsonHelper::AddStringToJsonObject(obj, "name", "drone");
  JsonHelper::AddFloatToJsonObject(obj, "radius", 1.0);
  JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
  std::vector<float> position_to_add;
  position_to_add.push_back(498.292);
  position_to_add.push_back(253.883);
  position_to_add.push_back(-228.623);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add;
  direction_to_add.push_back(1);
  direction_to_add.push_back(0);
  direction_to_add.push_back(0);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  IEntity* entity = factory->CreateEntity(obj);
  system->AddEntity(entity);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());

  //tests to make sure the observer can be added and removed successfully without crashing
  system->AddObserver(test_observer);
  system->RemoveObserver(test_observer);

}

}  // namespace csci3081
