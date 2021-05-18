#include "package.h"

namespace csci3081 {

Package::Package(const picojson::object& details) {
	//Retrieve information from json object.
	position_ = JsonHelper::GetStdFloatVector(details, "position");
	direction_ = JsonHelper::GetStdFloatVector(details, "direction");
	radius_ = JsonHelper::GetDouble(details, "radius");
	details_ = details;

	name_ = "package";
	id_ = 2; //Will be changed by factory upon creation.
	if (JsonHelper::ContainsKey(details, "weight")) {
    		weight_ = JsonHelper::GetDouble(details, "weight");
  	}
  	else {
		weight_ = 2.0;
	}
	version_ = 0;

	//Initialize destination.
	std::vector<float> dest{0.0, 0.0, 0.0};
	destination_ = dest;
	//Initialize package as not moving and waiting to be picked up.
	dynamic_ = false;
	status_ = "Waiting";

	// initialize position
	init_pos_ = position_;
}

//Trivial getters and setters.
std::string Package::GetStatus() { return status_; }
void Package::SetStatus(std::string status) { status_ = status; }
const std::vector<float>& Package::GetDestination() const { return destination_; };
float Package::GetWeight() const { return weight_; };
void Package::SetWeight(float weight) { weight_ = weight; };

//To get customer radius when drone is delivering package.
float Package::GetCustomerRadius() const {
	return customer_->GetRadius();
}

// returns a pointer to the associated customer
Customer* Package::GetCustomer(){
	return customer_;
}

//Sets customer and uses its location as destination of package.
void Package::SetCustomer(Customer* customer) {
	customer_ = customer;
	destination_ = customer->GetPosition();
}

//Slingshot package if delivered.
void Package::Update() {
	if (status_ == "Delivered") {
		SetPosition( {0.0, -10000.0, 0.0} ); //Slingshot package off the map.
	}
}

// return initial position
const std::vector<float>& Package::GetInitialPosition() const { return init_pos_; };

} //namespace csci3081
