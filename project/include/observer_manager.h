/**
 * @file observer_manager.h
 */
#ifndef OBSERVER_MANAGER_H_
#define OBSERVER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <string>
#include "composite_factory.h"
#include "entity_base.h"
#include "json_helper.h"
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
 * @brief The class to manage observer logic.
 * 
 * The functions in this class are called by DeliverySimulation to handle observers.
 */

class ObserverManager {

public:
  /// Adds an observer to the vector of observers.
  void AddObserver(IEntityObserver* observer);
  
  /// Removes an observer from the vector of observers.
  void RemoveObserver(IEntityObserver* observer);
  
  /// Sends the input event to all observers in this system.
  void BroadcastEvent(const picojson::value& event, IEntity& entity);

  /// Stores the statuses of entities in the system.
  void StoreStatuses(std::vector<IEntity*> entities, std::string initial_or_new);

  /// Creates events to be broadcasted using BroadcastEvent.
  void CreateEvents(std::vector<IEntity*> entities);

private:
  // Stores all observers in the system
  std::vector<IEntityObserver*> observers_;

  // Stores the initial statuses of entities prior to updating.
  std::vector<std::string> initial_statuses_;

  // Stores the new statuses of entities after updating.
  std::vector<std::string> new_statuses_;
};

}  // namespace csci3081

#endif  // OBSERVER_MANAGER_H_
