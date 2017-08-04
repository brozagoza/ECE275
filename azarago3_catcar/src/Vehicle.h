#ifndef VEHICLE_H
#define VEHICLE_H
/*************/
/*
 * File: Vehicle.h
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 20 Oct 2015
 *
 * Description: Header for vehicle.cpp. This file is for the declaration of the class, constructors, and methods.
 */

/* Note: comments in this file thusfar are insufficient for
   a perfect grade in comments */
#include "State.h"
#include "Input.h"
// wheelbase length in meters
#define L 2.6187

/* Class comment goes here */
class Vehicle {
private:
    State _state; // the current state of the vehicle
    void setState( State x ); // sets the value for _state
    
public:
    // constructs a new Vehicle object with the default State value
    Vehicle( );
    // executes the Vehicle for the duration specified
    // this method does not do any correctness checking on values in u
    void stateUpdate( Input u, double duration );
    
    State getState( ) const; // gets the value for _state
};

#endif // VEHICLE_H
