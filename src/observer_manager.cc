#include "observer_manager.h"

namespace csci3081 {

void ObserverManager::AddObserver(IEntityObserver* observer) {
	observers_.push_back(observer);
}

void ObserverManager::RemoveObserver(IEntityObserver* observer) {
    // Line reused from observer code provided in Canvas.
	observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void ObserverManager::BroadcastEvent(const picojson::value& event, IEntity& entity){
	for(IEntityObserver* observer : observers_) observer->OnEvent(event, entity);
}

void ObserverManager::StoreStatuses(std::vector<IEntity*> entities, std::string initial_or_new) {
    std::vector<std::string> statuses;
	
    // Iterate through entities and store statuses.
    for(IEntity* e : entities){
		if (e->GetName() == "package") {
			statuses.push_back(dynamic_cast<Package*>(e)->GetStatus());
		}
		else if (e->GetName() == "drone" || e->GetName() == "robot") {
			statuses.push_back(dynamic_cast<PackageTransporter*>(e)->GetStatus());
		}
        else if (e->GetName() == "customer") {
			statuses.push_back(dynamic_cast<Customer*>(e)->GetStatus());
        }
	}

    // Store statuses in correct variable.
    if (initial_or_new == "initial") {
        initial_statuses_ = statuses;
    }
    else if (initial_or_new == "new") {
        new_statuses_ = statuses;
    }
}

void ObserverManager::CreateEvents(std::vector<IEntity*> entities) {
    //Iterate through all statuses to check for changes.
    for (int i = 0; i < new_statuses_.size(); i++) {
        if (new_statuses_[i] != initial_statuses_[i]) {
            
            //"Switch" based on status change. (Sadly switches don't work on strings)
            
            //Package change in state.
            if (new_statuses_[i] == "InTransit") {
                BroadcastEvent(JsonHelper::CreateStatusJson("en route"), *(entities[i]));
            }
            else if (new_statuses_[i] == "Delivered") {
                BroadcastEvent(JsonHelper::CreateStatusJson("delivered"), *(entities[i]));
            }

            //Package transporter change in state.
            else if (new_statuses_[i] == "Idle") {
                if (dynamic_cast<PackageTransporter*>(entities[i])->GetNumDeliveries() == 0) {
                    BroadcastEvent(JsonHelper::CreateStatusJson("idle"), *(entities[i]));
                }
            }
            else if (new_statuses_[i] == "Drained") {        
                BroadcastEvent(JsonHelper::CreateStatusJson("idle"), *(entities[i]));
            }
            else { //If the transporter isn't idle, it is moving.
                if (entities[i]->GetName() == "drone" || entities[i]->GetName() == "robot") {
                    BroadcastEvent(JsonHelper::CreateStatusJson("moving", dynamic_cast<PackageTransporter*>(entities[i])->GetPath()), *(entities[i]));
                }
            }					
        }
    }
}

} //namespace csci3081