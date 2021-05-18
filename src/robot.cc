#include "robot.h"

namespace csci3081 {

Robot::Robot(const picojson::object& details) {
	//Retrieve information from json object.
	position_ = JsonHelper::GetStdFloatVector(details, "position");
	direction_ = JsonHelper::GetStdFloatVector(details, "direction");
	// check if the speed is above allowed max speed (hardcoded to 30) and set accordingly
	double speedCheck = JsonHelper::GetDouble(details, "speed");
	if(speedCheck > MAX_SPEED){
		speed_ = MAX_SPEED;
	}
	else {
		speed_ = speedCheck;
	}
	radius_ = JsonHelper::GetDouble(details, "radius");
	details_ = details;

	name_ = "robot";
	id_ = 4; //Will be changed by factory upon creation.
	version_ = 0;
	if(JsonHelper::ContainsKey(details, "max_weight")) {
    max_weight_ = JsonHelper::GetDouble(details, "max_weight");
  }
  else {
		max_weight_ = 25.0;
	}

	//Robot starts as idle, not moving, and without any deliveries.
	status_ = "Idle";
	dynamic_ = false;
	num_deliveries_ = 0;

	//Check if the battery capacity is given and set the battery accordingly
	if(JsonHelper::ContainsKey(details, "battery_capacity")) {
		float battery_capacity = JsonHelper::GetDouble(details, "battery_capacity");
		battery_ = new Battery(battery_capacity);
	}
	else {
		battery_ = new Battery();
	}
}

//Sets the robot's grounded movement path from start to end using the smart route.
void Robot::SetPath(std::vector<float> start, std::vector<float> end) {
	IStrategy* strat = new SmartPath();
	path_ = strat->SetPath(start, end, graph_);

    //Makes all path_ points have 0 height for the robot to travel on the ground.
    for (std::vector<float> vertex : path_) {
        vertex[1] = 0.0;
    }
}

} //namespace csci3081
