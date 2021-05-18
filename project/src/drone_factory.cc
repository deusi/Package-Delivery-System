#include "drone_factory.h"

namespace csci3081 {

DroneFactory::DroneFactory() {}
DroneFactory::~DroneFactory() {}

IEntity* DroneFactory::CreateEntity(const picojson::object& details) {
    Drone* drone = nullptr;

    if (JsonHelper::GetString(details, "type") == "drone") {
        drone = new Drone(details);
        drone->SetId(curr_id_++); //Drone IDs start at 1000 and go up as more are created.
    }
    
    return drone;
}

} //namespace csci3081