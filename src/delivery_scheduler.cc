#include "delivery_scheduler.h"

namespace csci3081 {

void DeliveryScheduler::ScheduleDelivery(Package* package, Customer* customer, std::vector<PackageTransporter*> transporters, const IGraph* graph) {
    package->SetCustomer(customer);
	//Picks the transporter whose battery is not drained with the least ongoing deliveries to handle this delivery.
	int delivery_entity = AssignTransporter(transporters, package);

	//Calls functions in package_transporter to set up delivery.
	transporters.at(delivery_entity)->SetGraph(graph);
	transporters.at(delivery_entity)->AddDelivery(package);
}


int DeliveryScheduler::AssignTransporter(std::vector<PackageTransporter*> transporters, Package* package) {
	//Picks the transporter whose battery is not drained with the least ongoing deliveries and the lightest load to handle this delivery.
	int delivery_entity = 0;
	for(int i = 0; i < transporters.size(); i++) {
    //dont assign a package to a transporter that cant carry it
    	if(package->GetWeight() > transporters.at(i)->GetMaxWeight()) continue;
		if(transporters.at(i)->GetStatus() != "Drained"){ //if the transporter isnt dead
			if(transporters.at(delivery_entity)->GetStatus() == "Drained"){
				delivery_entity = i;
				continue;
			}
			//get the amount of trips the currently selected transporter and candidate transporter will need to take if they pick up this package
			double cur_trips = GetAssignedTrips(transporters.at(delivery_entity)) + package->GetWeight() / transporters.at(delivery_entity)->GetMaxWeight();
			double new_trips = GetAssignedTrips(transporters.at(i)) + package->GetWeight() / transporters.at(i)->GetMaxWeight();

			//if they are both going to be taking the same amount of trips, fill up the fullest one first
			if((int) ceil(cur_trips) == (int) ceil(new_trips) && cur_trips < new_trips) {
				delivery_entity = i;
			}
			else if(cur_trips > new_trips) { //if the trip numbers are uneven and the candidate would make fewer trips, select it
				delivery_entity = i;
			}
		}
	}
    return delivery_entity;
}

double DeliveryScheduler::GetAssignedTrips(PackageTransporter* transporter){
	return (transporter->GetMaxWeight() - transporter->GetUnassignedCapacity()) / transporter->GetMaxWeight();
}

} // namespace csci3081
