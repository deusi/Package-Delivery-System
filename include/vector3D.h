/**
 * @file vector3D.h
 */
#ifndef VECTOR_3D_H_
#define VECTOR_3D_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <cmath>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for Vector3D objects.
 * 
 * Handles computations for 3D vectors. 
 * Used by package transporters to help compute movements.
 * 
 */

class Vector3D {
	public:
		/**
         @brief Constructor: Given 3 floats x, y, z, it sets the corresponding x, y, z values.
		 @param [in] x Float x value.
		 @param [in] y Float y value.
		 @param [in] z Float z value.
		 Default values are 0.0 for all.
        */
		Vector3D(float x, float y, float z);

		/**
         @brief Destructor: Currently does nothing.
        */
		~Vector3D();

		/**
         @brief Calculates and sets the magnitude_ attribute of the vector upon call.
        */
		void SetMagnitude();

		/**
         @brief Calculates and sets the direction_ attribute of the vector upon call.
        */
		void SetDirection();

		/**
         @brief Updates vector contents.
		 @param [in] x float for x-value
		 @param [in] y float for y-value.
		 @param [in] z float for z-value
        */
		void UpdateVector(float x, float y, float z);
		/**
         @brief Gets x-value.
        */
		float GetX() { return x_; }
		/**
         @brief Gets y-value.
        */
		float GetY() { return y_; }
		/**
         @brief Gets z-value.
        */
		float GetZ() { return z_; }
		/**
         @brief Gets direction.
        */
		std::vector<float> GetDirection() { return direction_; }
		/**
         @brief Gets magnitude.
        */
		float GetMagnitude() { return magnitude_; }

	private:
		/// x-value for the vector.
		float x_;
		/// y-value for the vector.
		float y_;
		/// z-value for the vector.
		float z_;
		/// direction for the vector.
		std::vector<float> direction_;
		/// magnitude for the vector.
		float magnitude_;
};
}  // namespace csci3081


#endif  // VECTOR_3D_H_