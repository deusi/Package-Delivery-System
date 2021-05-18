#include "robot_factory.h"

namespace csci3081 {

RobotFactory::RobotFactory() {}
RobotFactory::~RobotFactory() {}

IEntity* RobotFactory::CreateEntity(const picojson::object& details) {
    Robot* robot = nullptr;

    if (JsonHelper::GetString(details, "type") == "robot") {
        robot = new Robot(details);
        robot->SetId(curr_id_++); //Robot IDs start at 4000 and go up as more are created.
    }
    
    return robot;
}

} //namespace csci3081