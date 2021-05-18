/**
 * @file drone.h
 */
#ifndef DRONE_H_
#define DRONE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "package_transporter.h"
#include <math.h> 
#include "strategies.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for Drones.
 * 
 * Handles drone objects. Inherits from the EntityBase class, which in turn inherits
 * from the IEntity class. All IEntity functions are implemented in EntityBase.
 * 
 */

class Drone : public csci3081::PackageTransporter {
	public:
        /**
         @brief Constructor: Creates and initializes a drone object.

		 @param[in] details Json object containing details for the drone.

		 Reads position, direction, speed, name, radius from the json object.
		 Sets the name to "drone".

		 Initializes drone as not moving (dynamic_ = false, status_ = "Idle"), and without deliveries.
		 Currently assigns a default battery to the drone. Battery features will be implemented later.

		 Creates a default battery for the drone.
        */
		Drone(const picojson::object& details);

		/**
		 @brief Destructor: Currently does nothing. (I don't believe there is any dynamic memory allocation).
		*/
		~Drone() {};

		/**
		 @brief Sets path_ for the drone to follow, with different route possibilities. 
		 @param [in] start A vector triple of floats for the start position of the path to follow.
		 @param [in] end A vector triple of floats for the end position of the path to follow.
		*/
		void SetPath(std::vector<float> start, std::vector<float> end) override;

};

} //namespace csci3081

#endif //DRONE_H_
