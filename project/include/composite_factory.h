
/**
 * @file composite_factory.h
 */
#ifndef COMPOSITE_FACTORY_H_
#define COMPOSITE_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/common.h>

namespace csci3081{

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The composite factory class to create entities based on the composite factory pattern.
 */

class CompositeFactory : public entity_project::IEntityFactory {
    public:
        /**
         @brief Constructor: Currently does nothing.
        */
        CompositeFactory();
        /**
         @brief Destructor: Currently does nothing.
        */
        ~CompositeFactory();

        /**
         @brief Adds a factory to component_factories_ vector.
        */
        void AddFactory(IEntityFactory* factory);

        /**
         @brief Cycles through all entity factories until a non-null object is created, then returns the object.
         @param [in] details A json object containing the details of the entity to be created.

         As according to the composite factory pattern. 
         Code is largely similar to that found in a piazza comment by a TA.
          - https://piazza.com/class/kjuk3ynsg1f6os?cid=336_f1 
        */
        IEntity* CreateEntity(const picojson::object& details);
    private:
        /// Holds all component factories.
        std::vector<IEntityFactory*> component_factories_;
};

} //namespace csci3081

#endif //COMPOSITE_FACTORY_H_