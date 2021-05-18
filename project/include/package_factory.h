/**
 * @file package_factory.h
 */
#ifndef PACKAGE_FACTORY_H_
#define PACKAGE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/common.h>
#include "package.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The factory class to create packages.
 * 
 * Creates packages based on the composite factory pattern.
 */

class PackageFactory : public entity_project::IEntityFactory {
    public:
        /**
         @brief Constructor: Currently does nothing.
        */ 
        PackageFactory();
        /**
         @brief Destructor: Currently does nothing.
        */
        ~PackageFactory();

        /**
         @brief Creates and returns a package object.
         @param [in] details A json object containing the details of the entity to be created.

         Initializes the ID of the package as 2000, 2001, 2002, etc.
        */
        IEntity* CreateEntity(const picojson::object& details);
        
    private:
        /// Current ID to assign to packages as they are created. Increments each 
        /// time a package is created.
        int curr_id_ = 2000;
};

} //namespace csci3081

#endif //PACKAGE_FACTORY_H_