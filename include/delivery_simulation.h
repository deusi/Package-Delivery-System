/**
 * @file delivery_simulation.h
 */
#ifndef DELIVERY_SIMULATION_H_
#define DELIVERY_SIMULATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>
#include "composite_factory.h"
#include "observer_manager.h"
#include "delivery_scheduler.h"
#include "entity_base.h"
#include "json_helper.h"
#include "drone_factory.h"
#include "customer_factory.h"
#include "package_factory.h"
#include "robot_factory.h"
#include "package_transporter.h"
#include "drone.h"
#include "customer.h"
#include "package.h"
#include "robot.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the facade for the delivery system
 *
 * This class will delegate operations for the whole delivery system.
 * See the documentation for IDeliverySystem for more information.
 */

class DeliverySimulation : public IDeliverySystem {
 public:
  /**
   * @brief Constructor: Sets up the composite factory to aid in entity creation.
   */
  DeliverySimulation();

  /// Deconstructor: Currently does not do anything.
  ~DeliverySimulation();

  /**
  Given the picojson::object val, this creates an entity.
  Based on the type of entity, there may be different fields.
  You can see the vals that will be passed in the project/web/scenes
    directory. Some of the fields are for our backend system and you don't
    need to worry about them. (for instance, mesh, rotation, offset, etc.)

  Some fields in val that you will need to create the entity correctly:

    type: string (could be "drone/customer/package/robot")

    name: string

    position: array (contains [x_position, y_position, z_position])

    direction: array (contains [x, y, z])

    speed: float

    battery_capacity: float

  Don't add the entity to the simulation until it is passed in via AddEntity.
  */
  IEntity* CreateEntity(const picojson::object& val);

  /**
   *  This function adds a factory to the composite factory pattern.
   */
  void AddFactory(IEntityFactory* factory);

  /**
   *  @brief This function adds an entity to the simulation. 
   * 
   *  Also adds package transporters to a vector of transporters to cycle through while
   *  scheduling deliveries.
   */
  void AddEntity(IEntity* entity);

  /**
  @brief This function simply stores a reference to the IGraph* to the graph_ attribute.
  
  The IGraph contains useful functions such as the GetPath function which can 
  be used to get a path from one position to another.
  */
  void SetGraph(const IGraph* graph);

  /**
  This function tells the simulation that the IEntity* package should be delivered
  to the IEntity* dest (which is likely a customer). It assigns the transporter with the 
  least number of ongoing deliveries a package and assigns the package to a customer.
  */
  void ScheduleDelivery(IEntity* package, IEntity* dest);

  /**
  Adds an observer to the vector of observers.
  */
  void AddObserver(IEntityObserver* observer);

  /**
  Removes an observer from the vector of observers.
  */
  void RemoveObserver(IEntityObserver* observer);

  /**
  GetEntities returns all entities that have been ADDED to the system
  */
  const std::vector<IEntity*>& GetEntities() const;

  /**
  @brief This function is used to advance time in the simulation.
  
  float dt refers to the amount of time the update call should advance the simulation by. 
  For instance if a drone moves 1 unit of distance per unit of time, and Update is called 
  with dt=.05, then the drone should move 1 * .05 = .05 units of distance.

  The function calls all the package transporters' update functions to allow them to 
  change position and checks if packages have been delivered (and in that case, they are 
  slingshotted off the map).
  */

  void Update(float dt);

  /**
   * @brief You do not need to worry about this function.
   * 
   * This function takes care of turning json into function calls of your system.
   * YOU DO NOT NEED TO IMPLEMENT THIS
   *it is already implemented in the delivery_simulation.cc we have provided.
   */
  void RunScript(const picojson::array& script, IEntitySystem* system) const;

 private:
  // Stores all entities in the system.
  std::vector<IEntity*> entities_;

  // Stores all package transporters in the system to cycle through when calling ScheduleDelivery.
  std::vector<PackageTransporter*> transporters_;

  // Stores the graph of the scene.
  const IGraph* graph_;

  // Factory for generating entities.
  CompositeFactory* factory_;

  // Observer manager to handle observers.
  ObserverManager* observer_manager_;

  // Delivery scheduler for scheduling deliveries.
  DeliveryScheduler* delivery_scheduler_;
};

}  // namespace csci3081

#endif  // DELIVERY_SIMULATION_H_