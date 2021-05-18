/**
 * @file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>
#include "json_helper.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating entities.
 *
 * This class is the base for all entities in the delivery system.
 * This uses the IEntity interface, and implements all required functions so that
 * the entities which inherit from this class will inherit the functions as well.
 * 
 */
class EntityBase : public IEntity {
	public:
		/**
         @brief Virtual Destructor: To call derived entity's destructors upon deletion.
        */
		virtual ~EntityBase() {}
	
		/**
         @brief Returns details_ of the entity.
        */
		const picojson::object& GetDetails() { return details_; }
		/**
         @brief Returns id_ of the entity.
        */
		int GetId() const { return id_; };
		/**
         @brief Returns name_ of the entity.
        */
		const std::string& GetName() { return name_; };
		/**
         @brief Returns position_ of the entity.
        */
		const std::vector<float>& GetPosition() const { return position_; };
		/**
         @brief Returns direction_ of the entity.
        */
		const std::vector<float>& GetDirection() const { return direction_; };
		/**
         @brief Returns radius_ of the entity.
        */
		float GetRadius() const { return radius_; };
		/**
         @brief Returns version_ of the entity.
        */
		int GetVersion() const { return version_; };
		/**
         @brief Returns dynamic_ for the entity.
        */
		bool IsDynamic() const { return dynamic_; };
		/**
		 @brief Gets status_.
		*/	
		std::string GetStatus() { return status_; };
		/**
		 @brief Sets status_.
		*/			
		void SetStatus(std::string status) { status_ = status; };
		/**
         @brief Sets id_ of the entity.
        */
		void SetId(int id) { id_ = id; };
		/**
         @brief Sets name_ of the entity.
        */
		void SetName(std::string name) { name_ = name; };
		/**
         @brief Sets position_ of the entity.
        */
		void SetPosition(std::vector<float> position) { position_ = position; };
		/**
         @brief Sets dynamic_ for the entity.
        */
		void SetDynamic(bool dynamic) { dynamic_ = dynamic; }


	protected:
		///Picojson object containing all the details of the entity.
		picojson::object details_;
		///The ID of the entity, assigned by the factories after creation.
		int id_;
		///The name of the entity.
		std::string name_;
		///The position of the entity. A vector triple of floats.
		std::vector<float> position_;
		///The direction of the entity. A vector triple of floats.
		std::vector<float> direction_;
		///The radius of the entity.
		float radius_;
		///The version of the entity.
		int version_;
		///Bool value for if the entity should move or not.
		bool dynamic_;
		/// Status of the entity. 
		std::string status_;
};

}  // namespace csci3081


#endif  // ENTITY_BASE_H_