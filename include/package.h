/**
 * @file package.h
 */
#ifndef PACKAGE_H_
#define PACKAGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"
#include "customer.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for Packages.
 *
 * Handles package objects. Inherits from the EntityBase class, which in turn inherits
 * from the IEntity class. All IEntity functions are implemented in EntityBase.
 *
 */

class Package : public csci3081::EntityBase {
	public:
        /**
         @brief Constructor: Creates and initializes a package object.

		 @param[in] details Json object containing details for the package.

		 Reads position, direction, name, radius from the json object.
		 Sets the name to "package".

		 Initializes package as not moving (dynamic_ = false, status_ = "Waiting"), and without a customer/destination.
		 Customer and destination are assigned after ScheduleDelivery in delivery_simulation is called.
        */
		Package(const picojson::object& details);

		/**
		 @brief Destructor: Currently does nothing.
		*/
		~Package() {};

		/**
		 @brief Returns status_. Can be "Waiting", "InTransit", or "Delivered".
		*/
		std::string GetStatus();
		/**
		 @brief Sets status_. Can be "Waiting", "InTransit", or "Delivered".
		*/
		void SetStatus(std::string status);
		/**
		 @brief Returns destination_. Assigned after SetCustomer is called.
		*/
		const std::vector<float>& GetDestination() const;
		/**
		 @brief Returns weight_.
		*/
		float GetWeight() const;
		/**
		 @brief Sets weight_.
		*/
		void SetWeight(float weight);
		/**
		 @brief Returns customer's radius. For use by the drone when delivering to customer.
		 @return Float containing customer's radius
		*/
		float GetCustomerRadius() const;
		/**
		 @brief Gets a customer of a package. Returns a pointer to a cusomer.
		*/
		Customer* GetCustomer();
		/**
		 @brief Sets a customer for the packages, and uses it to set destination_.
		 @param [in] customer A pointer to a customer object that a drone will deliver the package to.
		*/
		void SetCustomer(Customer* customer);

		/**
		 @brief Returns initial position of the package
		*/
		const std::vector<float>& GetInitialPosition() const;

		/**
		 @brief Slingshots the package off the map if it is delivered.
		*/
		void Update();

	private:
		///Store the destination of the package.
		std::vector<float> destination_;
		///Stores the weight of the package. For iteration 1, will always be 0.
		float weight_;
		///Stores customer of the package.
		///For iteration 1, all packages are assumed to have an associated customer.
		Customer* customer_;
		///Status of the package. Can be "Waiting", "InTransit", or "Delivered".
		std::string status_;
		// intial position
		std::vector<float> init_pos_;
};

}

#endif //PACKAGE_H_
