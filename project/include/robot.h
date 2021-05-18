/**
 * @file robot.h
 */
#ifndef ROBOT_H_
#define ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "package_transporter.h"
#include "strategies.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for Robots.
 * 
 * Handles robot objects. Inherits from the EntityBase class, which in turn inherits
 * from the IEntity class. All IEntity functions are implemented in EntityBase.
 * 
 */

class Robot : public csci3081::PackageTransporter {
	public:
        /**
         @brief Constructor: Creates and initializes a robot object.

		 @param[in] details Json object containing details for the robot.

		 Reads position, direction, speed, name, radius from the json object.
		 Sets the name to "robot".

		 Initializes robot as not moving (dynamic_ = false, status_ = "Idle"), and without deliveries.
		 Currently assigns a default battery to the robot. Battery features will be implemented later.

		 Creates a default battery for the robot.
        */
		Robot(const picojson::object& details);

		/**
		 @brief Destructor: Currently does nothing. (I don't believe there is any dynamic memory allocation).
		*/
		~Robot() {};

		/**
		 @brief Sets path_ for the robot to follow a grounded path based on one from IGraph's GetPath function. 
		 @param [in] start A vector triple of floats for the start position of the path to follow.
		 @param [in] end A vector triple of floats for the end position of the path to follow.
		*/
		void SetPath(std::vector<float> start, std::vector<float> end) override;
};

} //namespace csci3081

#endif //ROBOT_H_