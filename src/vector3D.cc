#include "vector3D.h"

namespace csci3081 {

Vector3D::Vector3D(float x, float y, float z) {
    //Initialize Vector3D contents.
    x_ = x;
    y_ = y;
    z_ = z;

    //Calculates direction and magnitude given contents.
    this->SetMagnitude();
    this->SetDirection();
}

Vector3D::~Vector3D() {}

//Calculates magnitude of vector.
void Vector3D::SetMagnitude() {
    this->magnitude_ = sqrt(x_*x_ + y_*y_ + z_*z_);
    return;
}

//Normalizes vector to calculate direction.
void Vector3D::SetDirection() {
    //Ensures magnitude is set properly before using it.
    this->SetMagnitude();
    float mag = this->magnitude_;
    
    //Reset vector if size is wrong.
    if (direction_.size() != 3) {
        direction_.clear();
        direction_.push_back(0.0);
        direction_.push_back(0.0);
        direction_.push_back(0.0);
    }
    
    //Special case: Zero Vector.
    if (mag == 0) {
        direction_[0] = 0.0;
        direction_[1] = 0.0;
        direction_[2] = 0.0;
        return;
    }
    //Standard case.
    else {
        direction_[0] = x_ / mag;
        direction_[1] = y_ / mag;
        direction_[2] = z_ / mag;
        return;
    }
}

//Update vector x,y,z and magnitude/direction.
void Vector3D::UpdateVector(float x, float y, float z) {
    x_ = x;
    y_ = y;
    z_ = z;
    this -> SetMagnitude();
    this -> SetDirection();
}

} //namespace csci3081