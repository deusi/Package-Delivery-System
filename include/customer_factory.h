/**
 * @file customer_factory.h
 */
#ifndef CUSTOMER_FACTORY_H_
#define CUSTOMER_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/common.h>
#include "customer.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The factory class to create customers.
 * 
 * Creates customers based on the composite factory pattern.
 */

class CustomerFactory : public entity_project::IEntityFactory {
    public:
        /**
         @brief Constructor: Currently does nothing.
        */    
        CustomerFactory();
        /**
         @brief Destructor: Currently does nothing.
        */
        ~CustomerFactory();

        /**
         @brief Creates and returns a customer object.
         @param [in] details A json object containing the details of the entity to be created.
         
         Initializes the ID of the customers as 3000, 3001, 3002, etc.
        */
        IEntity* CreateEntity(const picojson::object& details);
    
    private:
        /// Current ID to assign to customers as they are created. Increments each 
        /// time a customer is created.
        int curr_id_ = 3000;
};

} //namespace csci3081

#endif //CUSTOMER_FACTORY_H_