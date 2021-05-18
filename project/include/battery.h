/**
 * @file battery.h
 */
#ifndef BATTERY_H_
#define BATTERY_H_

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The class for Batteries.
 * 
 * Used by all package transporters.
 */

class Battery {
    public:
        /**
         @brief Constructor: Initializes a battery given a max_charge.
         @param [in] max_charge A float with the maximum charge of the battery.
         
        Initializes the battery to full charge, error checks if max_charge is non-positive.
        */
        Battery(float max_charge);

        /**
         @brief Constructor: Initializes a battery to default values.
         
        Default max_charge is 10,000.
        */
        Battery();

        /**
         @brief Destructor: Currently does nothing.
        */
        ~Battery();

        /**
         @brief Updates battery charge after time has passed.
         @param [in] dt A float indicating the change in time.

         Battery level will never go below 0. Updates is_empty_ as appropriate. 
        */
        void UpdateBattery(float dt);

        /**
         @brief Checks is_empty_.
        */
        bool CheckEmpty();
        /**
         @brief Gets curr_battery_level_.
        */        
        float GetCharge();
        /**
         @brief Gets max_charge_.
        */   
        float GetMaxCharge();
        /**
         @brief Sets max_charge_.
        */   
        void SetMaxCharge(float max_charge);

    private:
        /// Holds the max charge of a battery. Default is 10000.
        float max_charge_ = 10000;
        /// Bool for if the battery is empty or not. Starts at not empty.
        bool is_empty_;
        /// Current battery level. Starts at max charge.
        float curr_battery_level_;
};

}  // namespace csci3081

#endif //BATTERY_H_