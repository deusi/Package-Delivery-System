#include "drone.h"

namespace csci3081 {


Drone::Drone(const picojson::object& details) {
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
	name_ = "drone";
	id_ = 1; //Will be changed by factory upon creation.
	version_ = 0;
	//Drone starts as idle, not moving, and without any deliveries.
	status_ = "Idle";
	dynamic_ = false;
	num_deliveries_ = 0;

	if (JsonHelper::ContainsKey(details, "max_weight")) {
    max_weight_ = JsonHelper::GetDouble(details, "max_weight");
  }
  else {
		max_weight_ = 10.0;
	}

	//Check if the battery capacity is given and set the battery accordingly
	if(JsonHelper::ContainsKey(details, "battery_capacity")) {
		float battery_capacity = JsonHelper::GetDouble(details, "battery_capacity");
		battery_ = new Battery(battery_capacity);
	}
	else {
		battery_ = new Battery();
	}
}

//Sets the drone's movement path from start to end
void Drone::SetPath(std::vector<float> start, std::vector<float> end) {

	IStrategy* strat[3];
	strat[0] = new SmartPath();
	strat[1] = new BeelinePath();
	strat[2] = new ParabolicPath();
	std::string pathString = "smart";
	if (JsonHelper::ContainsKey(details_, "path")){
		pathString = JsonHelper::GetString(details_, "path");
	}

	if (pathString == "smart"){
		path_ = strat[0]->SetPath(start, end, graph_);
	}

	else if (pathString == "beeline"){
        path_ = strat[1]->SetPath(start, end, graph_);
	}
	else if (pathString == "parabolic"){
		path_ = strat[2]->SetPath(start, end, graph_);
	}
}
} //namespace csci3081
