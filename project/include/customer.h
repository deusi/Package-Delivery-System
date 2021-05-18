/**
 * @file customer.h
 */
#ifndef CUSTOMER_H_
#define CUSTOMER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity_base.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for Customers.
 * 
 * Handles customer objects. Inherits from the EntityBase class, which in turn inherits
 * from the IEntity class. All IEntity functions are implemented in EntityBase.
 */

class Customer : public csci3081::EntityBase {
	public:
        /**
         @brief Constructor: Creates and initializes a customer object.
		 @param[in] details Json object containing details for the customer.
		 
		 Reads position, direction, name, radius from the json object.
		 Sets the name to "customer".

		 Initializes customer as not moving (dynamic_ = false).
        */
    	Customer(const picojson::object& details);
};

} //namespace csci3081

#endif //CUSTOMER_H_