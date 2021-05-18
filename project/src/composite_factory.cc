#include "composite_factory.h"

namespace csci3081 {

CompositeFactory::CompositeFactory() {}
CompositeFactory::~CompositeFactory() {}

//Add factory to list of factories.
void CompositeFactory::AddFactory(IEntityFactory* factory) {
    component_factories_.push_back(factory);
}

//Credit for this code goes to a piazza comment: https://piazza.com/class/kjuk3ynsg1f6os?cid=336_f1
IEntity* CompositeFactory::CreateEntity(const picojson::object& details) {
    for (auto component_factory : component_factories_) {
        IEntity* entity = component_factory->CreateEntity(details);
        if (entity) {
            return entity;
        }
    }
    return nullptr;
}

} //namespace csci3081