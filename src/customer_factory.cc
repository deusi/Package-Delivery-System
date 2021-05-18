#include "customer_factory.h"

namespace csci3081 {

CustomerFactory::CustomerFactory() {}
CustomerFactory::~CustomerFactory() {}

IEntity* CustomerFactory::CreateEntity(const picojson::object& details) {
    Customer* customer = nullptr;

    if (JsonHelper::GetString(details, "type") == "customer") {
        customer = new Customer(details);
        customer->SetId(curr_id_++); //Customer IDs start from 3000 and go up as more are created.
    }
    
    return customer;
}

} //namespace csci3081