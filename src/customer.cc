#include "customer.h"

namespace csci3081 {

Customer::Customer(const picojson::object& details) {
	//Read info from json object.
	position_ = JsonHelper::GetStdFloatVector(details, "position");
	direction_ = JsonHelper::GetStdFloatVector(details, "direction");
	radius_ = JsonHelper::GetDouble(details, "radius");
	details_ = details;

	name_ = "customer";
	id_ = 3; //Default ID, should be set to something else by factory.
	version_ = 0;
	dynamic_ = false;
}


} //namespace csci3081