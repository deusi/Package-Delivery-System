/**
 * @file robot_factory.h
 */
#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/common.h>
#include "robot.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The factory class for creating robots.
 * 
 * Creates robots based on the composite factory pattern.
 */

class RobotFactory : public entity_project::IEntityFactory {
    public:
        /**
         @brief Constructor: Currently does nothing.
        */ 
        RobotFactory();
        /**
         @brief Destructor: Currently does nothing.
        */
        ~RobotFactory();

        /**
         @brief Creates and returns a robot object.
         @param [in] details A json object containing the details of the entity to be created.
         
         Initializes the ID of the robot as 4000, 4001, 4002, etc.
        */
        IEntity* CreateEntity(const picojson::object& details);
        
    private:
        /// Current ID to assign to robots as they are created. Increments each 
        /// time a robot is created.
        int curr_id_ = 4000;
};

} //namespace csci3081

#endif //ROBOT_FACTORY_H_