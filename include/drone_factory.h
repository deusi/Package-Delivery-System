/**
 * @file drone_factory.h
 */
#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/common.h>
#include "drone.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The factory class for creating drones.
 * 
 * Creates drones based on the composite factory pattern.
 */

class DroneFactory : public entity_project::IEntityFactory {
    public:
        /**
         @brief Constructor: Currently does nothing.
        */ 
        DroneFactory();
        /**
         @brief Destructor: Currently does nothing.
        */
        ~DroneFactory();

        /**
         @brief Creates and returns a drone object.
         @param [in] details A json object containing the details of the entity to be created.
         
         Initializes the ID of the drone as 1000, 1001, 1002, etc.
        */
        IEntity* CreateEntity(const picojson::object& details);
        
    private:
        /// Current ID to assign to drones as they are created. Increments each 
        /// time a drone is created.
        int curr_id_ = 1000;
};

} //namespace csci3081

#endif //DRONE_FACTORY_H_