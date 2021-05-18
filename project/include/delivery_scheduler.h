/**
 * @file delivery_scheduler.h
 */
#ifndef DELIVERY_SCHEDULER_H_
#define DELIVERY_SCHEDULER_H_

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
#include <map>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class to manage delivery scheduling logic.
 * 
 * The functions in this class are called by DeliverySimulation while scheduling deliveries.
 */

class DeliveryScheduler {
public:
	/**
		 @brief Schedules a delivery. Assigns package to customer, and transporter to package. 
		 @param [in] package The package to be scheduled.
		 @param [in] customer The customer the package will be delivered to.
         @param [in] transporters A vector of all transporters that can be assigned a package to deliver.
	*/
    void ScheduleDelivery(Package* package, Customer* customer, std::vector<PackageTransporter*> transporters, const IGraph* graph);

	/**
		 @brief Helper function to ScheduleDelivery. Picks the transporter. 
         @param [in] transporters A vector of all transporters that can be assigned a package to deliver.
         @param [in] package The package to be assigned a transporter.
	*/
    int AssignTransporter(std::vector<PackageTransporter*> transporters, Package* package);

    /// Sets the graph of the map, passed into the transporters upon scheduling.
    void SetGraph(const IGraph* graph) { graph_ = graph; }

    /// 
    double GetAssignedTrips(PackageTransporter* transporter);


private:
    /// The graph of the map, passed into the transporters upon scheduling.
    const IGraph* graph_;

};


}  // namespace csci3081

#endif  // DELIVERY_SCHEDULER_H_
