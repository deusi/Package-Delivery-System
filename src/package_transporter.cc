#include "package_transporter.h"

namespace csci3081 {

//Trivial Getters and Setters.
int PackageTransporter::GetNumDeliveries() { return num_deliveries_; }
std::string PackageTransporter::GetStatus() { return status_; }
void PackageTransporter::SetStatus(std::string status) { status_ = status; }
void PackageTransporter::SetGraph(const IGraph* graph) { graph_ = graph; }
std::vector<std::vector<float>> PackageTransporter::GetPath(){ return path_; }
double PackageTransporter::GetMaxWeight(){ return max_weight_; }

//Adding a package to deliver.
void PackageTransporter::AddDelivery(Package* package) {
	num_deliveries_++;
	packages_to_deliver_.push_back(package);
}

//Update function, handles updating position/contents of the package transporter.
void PackageTransporter::Update(float dt) {
	Package* current_package;

	//If package transporter is Idle and there are more packages to deliver, set status of package
  //transporter to TravelingToPackage and set its path from where it is to the package.
	if (status_ == "Idle" && packages_to_deliver_.size() > 0 && packages_to_deliver_.at(0)->GetWeight() <= GetAvailableWeight()) {
		current_package = packages_to_deliver_[0];
		SetStatus("TravelingToPackage");
		SetPath(GetPosition(), current_package->GetPosition());
		dynamic_ = true;
	}

	//this if statement corrects statuses created only for redrawing the path (for triggering the observers)
	if(status_ == "TravelingToPackage!") status_ = "TravelingToPackage";
	else if(status_ == "DeliveringPackage!") status_ = "DeliveringPackage";

	//For when the package transporter is moving to the package.
	if (status_ == "TravelingToPackage") {
		current_package = packages_to_deliver_[0];
		int range = radius_ + current_package->GetRadius(); //Radius to allow pickup is sum of radii.
		SetPosition(CalculateNextPosition(dt, range)); //Update Position.
		for(auto package : packages_in_inv_){
			package->SetPosition(GetPosition());
		}

		//If there is nothing left in the path for the package transporter to follow, it has reached the package.
		if (path_.size() == 0) {
			packages_in_inv_.push_back(current_package); //add the package to our inventory
			packages_to_deliver_.erase(packages_to_deliver_.begin()); //remove it from the to-grab vector
			current_package->SetDynamic(true); //set the picked up package to dynamic
			current_package->SetStatus("InTransit"); //change the picked up package's status

			//deliver the package(s) if we cant carry more or if there are no more packages to grab
			if(packages_to_deliver_.size() == 0 || packages_to_deliver_.at(0)->GetWeight() > GetAvailableWeight()){
				//Adjust transporter info
				SetStatus("DeliveringPackage");
				SetPath(GetPosition(), packages_in_inv_[0]->GetDestination());
				//Set path from all packages in inv to destination of the current package.
			}
			//grab another package
			else{
				SetStatus("TravelingToPackage!");
				SetPath(GetPosition(), packages_to_deliver_.at(0)->GetPosition());
			}
		}
	}

	//For when the package transporter is delivering the package.
	if (status_ == "DeliveringPackage") {
		current_package = packages_in_inv_[0];
		int range = radius_ + current_package->GetCustomerRadius(); //Radius to allow dropoff is sum of radii.
		SetPosition(CalculateNextPosition(dt, range)); //Update Position.
		for(auto package : packages_in_inv_){
			package->SetPosition( GetPosition() ); //Make package move with package transporter.
		}

		//If nothing is left in the path for the package transporter to follow, it has reached the destination.
		if (path_.size() == 0) {
			//Adjust package information.
			current_package->SetStatus("Delivered");
			packages_in_inv_.erase( packages_in_inv_.begin() );
			num_deliveries_--;
			if(packages_in_inv_.size() == 0){
				//Package transporter will now change to Idle.
				dynamic_ = false;
				SetStatus("Idle");
			}
			else{ //go to the next package's destination
				SetStatus("DeliveringPackage!");
				SetPath(GetPosition(), packages_in_inv_.front()->GetCustomer()->GetPosition());
			}
		}
	}

	// change the status to drained if the battery is empty
	if (battery_->CheckEmpty()) {
		//Package transporter will now change to Drained.
		dynamic_ = false;
		SetStatus("Drained");
	}

	// update the status of each package if the transporter's battery is drained
	if ((status_ == "Drained") && (packages_to_deliver_.size() > 0)) {
		while(packages_to_deliver_.size() > 0){
			current_package = packages_to_deliver_.at(0);
			//Adjust package information.
			current_package->SetDynamic(false);
			current_package->SetStatus("OnHold");

			// update position of the package to be on the ground
			//std::vector<float> init_pos = current_package->GetInitialPosition();
			//float init_y = init_pos.at(1);
			//std::vector<float> current_position = current_package->GetPosition();
			//current_position.at(1) = init_y;
			//current_package->SetPosition(current_position);

			// delete the package from the list of deliveries
			packages_to_deliver_.erase( packages_to_deliver_.begin() );
			num_deliveries_--;
		}
	}

	if ((status_ == "Drained") && (packages_in_inv_.size() > 0)) {
		while(packages_in_inv_.size() > 0){
			current_package = packages_in_inv_.at(0);
			//Adjust package information.
			current_package->SetDynamic(false);
			current_package->SetStatus("OnHold");

			// update position of the package to be on the ground
			std::vector<float> init_pos = current_package->GetInitialPosition();
			float init_y = init_pos.at(1);
			std::vector<float> current_position = current_package->GetPosition();
			current_position.at(1) = init_y;
			current_package->SetPosition(current_position);

			// delete the package from the list of deliveries
			packages_in_inv_.erase( packages_in_inv_.begin() );
			num_deliveries_--;
		}
	}

	//If package transporter was not idle or drained, battery needs to be updated.
	if ((status_ != "Idle") && (status_ != "Drained")) {
		battery_->UpdateBattery(dt);
	}
}

//return the remaining weight capacity of this transporter
double PackageTransporter::GetAvailableWeight(){
	double cur_weight = 0.0;
	for(auto package : packages_in_inv_){
		cur_weight += package->GetWeight();
	}
	return max_weight_ - cur_weight;
}

double PackageTransporter::GetUnassignedCapacity(){
	double weight = GetAvailableWeight();
	for(auto package : packages_to_deliver_){
		weight -= package->GetWeight();
	}
	return weight;
}

//Calculate the next position of the entity.
std::vector<float> PackageTransporter::CalculateNextPosition(float dt, float range) {
	std::vector<float> current_pos = GetPosition();
	std::vector<float> new_pos = {0.0, 0.0, 0.0}; //Initialize as a 3 element vector.
	double change_direction_constant = 3.0; //Constant to adjust when the entity changes direction in path.

	//Error checking for if the path to follow is empty.
	if (path_.size() == 0) {
		return current_pos;
	}

	//Sets up a Vector3D object of the next leg of the path.
	float next_leg_x = (path_[0][0] - current_pos[0]);
	float next_leg_y = (path_[0][1] - current_pos[1]);
	float next_leg_z = (path_[0][2] - current_pos[2]);
	Vector3D next_leg_of_path(next_leg_x, next_leg_y, next_leg_z);

	//Calculates next position using formula provided in class.
	for (int i = 0; i < 3; i++) {
		new_pos.at(i) = current_pos.at(i) + speed_ * (next_leg_of_path.GetDirection()).at(i) * dt;
	}

	//If the path size is 1, that means that the entity is about to reach the current destination, and will
	//stop once it is within the range given by the sum of radii.
	if (path_.size() == 1) {
		if (next_leg_of_path.GetMagnitude() <= range) {
		path_.erase( path_.begin(), path_.end() );
		}
	}
	//If the entity has finished a leg of the path, erase it from the path to move onto the next leg of the path.
	else if (next_leg_of_path.GetMagnitude() <= change_direction_constant) {
		path_.erase( path_.begin() );
	}
	return new_pos;
}

} //namespace csci3081
