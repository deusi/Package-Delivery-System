#include "delivery_simulation.h"

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	//Create a new composite factory
	factory_ = new CompositeFactory();

	//Create an observer manager to manage observers
	observer_manager_ = new ObserverManager();

	//Create a delivery scheduler to help schedule deliveries
	delivery_scheduler_ = new DeliveryScheduler();

	//Add all factories for entities to composite factory's list.
	AddFactory(new DroneFactory);
	AddFactory(new CustomerFactory);
	AddFactory(new PackageFactory);
	AddFactory(new RobotFactory);
}

DeliverySimulation::~DeliverySimulation() {}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
	//Composite factory design.
    return factory_->CreateEntity(val);
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	factory_->AddFactory(factory);
}

void DeliverySimulation::AddEntity(IEntity* entity) {
	//Add entity to entity list
	entities_.push_back(entity);

	//Checks if entity has drone or robot in its name, adds it to transporter list if it does.
	if (entity->GetName() == "drone" || entity->GetName() == "robot") {
		PackageTransporter* transporter = dynamic_cast<PackageTransporter*> (entity);
		transporters_.push_back(transporter);
	}
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	graph_ = graph;
	delivery_scheduler_->SetGraph(graph); //When packages are being scheduled, the transporters need the graph.
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	//Currently, destination is assumed to be a customer.
	Package* package_to_deliver = dynamic_cast<Package*> (package);
	Customer* customer = dynamic_cast<Customer*> (dest);
	package_to_deliver->SetCustomer(customer);
	delivery_scheduler_->ScheduleDelivery(package_to_deliver, customer, transporters_, graph_);

	//Broadcast that this package is being scheduled for delivery.
	observer_manager_->BroadcastEvent(JsonHelper::CreateStatusJson("scheduled"), *package);
}


void DeliverySimulation::AddObserver(IEntityObserver* observer) {
	observer_manager_->AddObserver(observer);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
	observer_manager_->RemoveObserver(observer);
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
	IEntity* entity;

	//Store initial statuses of entities.
	observer_manager_->StoreStatuses(entities_, "initial");

	//Iterate through all entities for updating.
	for (int i = 0; i < entities_.size(); i++) {
		entity = entities_.at(i);

		//If entity is a package, call its update function.
		if(entity->GetName() == "package") {
			Package* package = dynamic_cast<Package*> (entity);

			// Reschedule a package that is on hold
			if (package->GetStatus() == "OnHold") {
				package->SetStatus("Waiting");
				ScheduleDelivery(package, package->GetCustomer());
			}
			package->Update();
		}

		//If entities can transport packages, call their update function.
		if(entity->GetName() == "drone" || entity->GetName() == "robot" ) {
			PackageTransporter* transporter = dynamic_cast<PackageTransporter*> (entity);
			transporter->Update(dt);
		}
	}

	//Gather new statuses and create events to broadcast.
	observer_manager_->StoreStatuses(entities_, "new");
	observer_manager_->CreateEvents(entities_);
}

// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
