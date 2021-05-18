#include "package_factory.h"

namespace csci3081 {

PackageFactory::PackageFactory() {}
PackageFactory::~PackageFactory() {}

IEntity* PackageFactory::CreateEntity(const picojson::object& val) {
    Package* package = nullptr;

    if (JsonHelper::GetString(val, "type") == "package") {
        package = new Package(val);
        package->SetId(curr_id_++); //Package IDs start at 2000 and go up as more are created.
    }

    return package;
}

} //namespace csci3081