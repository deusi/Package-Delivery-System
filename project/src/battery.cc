#include "battery.h"

namespace csci3081 {

//Constructor when given max_charge
Battery::Battery(float max_charge) {
    //Error checking max_charge. When a number 0 or below is passed in, it is set to 1.
    if (max_charge > 0) {
        max_charge_ = max_charge;
    }
    else {
        max_charge_ = 1;
    }

    //Initialize battery as full.
    curr_battery_level_ = max_charge_;
    is_empty_ = false;
}

//Constructor without arguments. Default charge is 10000.
Battery::Battery() {
    max_charge_ = 10000;
    curr_battery_level_ = max_charge_;
    is_empty_ = false;
}

Battery::~Battery() {}

//Updates battery given a time. Won't make the battery level go below 0 and instead change is_empty_ to true.
void Battery::UpdateBattery(float dt) {
    curr_battery_level_ -= dt;
    if (curr_battery_level_ <= 0) {
        curr_battery_level_ = 0;
        is_empty_ = true;
    }
    return;
}

//Basic getters and setters.
bool Battery::CheckEmpty() { return is_empty_; }
float Battery::GetCharge() { return curr_battery_level_; }
float Battery::GetMaxCharge() { return max_charge_; }

//Sets max charge, error checking if it is above 0.
void Battery::SetMaxCharge(float max_charge) {
    if (max_charge > 0) {
        max_charge_ = max_charge;
    }
    else {
        max_charge_ = 1;
    }
}

}  // namespace csci3081