/* *********** */
/*
* File : Vehicle.cpp
* Author : Alejandro Zaragoza
* NetID : azarago3
* Date : 20 October 2015
*
* Description : This file contains the vehicle class consisting of an empty constructor, setState that sets the state,
*				stateUpdate that updates the values given an INPUT and duration, and getState that returns the current
*				state value.
*
*/
/* *********** */
#include <iostream>
#include "Vehicle.h"
#include "Input.h"
#include "State.h"
using namespace std;
/***************/


// setState function that 
void Vehicle::setState(State x)
{
	_state = x;
} // end setState method


/*************************************************************************************************************************
*	Constructor Vehicle()
*
*	This constructor creates a new Vehicle object, containing a single State object declared to all '0'.
*
*************************************************************************************************************************/
Vehicle::Vehicle()
{
	State _state(0, 0, 0, 0, 0);

	return;
} // end constructor


/*************************************************************************************************************************
*	Method stateUpdate()
*
*	This method updates the values of this Vehicle's object's state using the set-in-stone functions with parameters
*	Input u and double duration. This method also has an checker to make sure that the values fall between a range of
*	predescribed values.
*
*************************************************************************************************************************/
void Vehicle::stateUpdate(Input u, double duration)
{
	double value = 0.0;		// variable used to hold the current value to be passed in
	double tempX = _state.getXPos();
	double tempY = _state.getYPos();
	double tempAngle = _state.getTireAngle();
	double tempHead = _state.getHeading();

	// XPOS // Update x1(t + /\t)
	value = tempX + (duration * u.getVelocity() * cos(tempAngle) * cos(tempHead));
	_state.setXPos(value);
	// End update


	// YPOS // Update x2(t + /\t)
	value = tempY + (duration * u.getVelocity() * cos(tempAngle) * sin(tempHead));
	_state.setYPos(value);
	// End Update


	// TIRE ANGLE // Update x3(t + /\t)
	value = tempAngle + (duration * u.getTireAngleRate());

	if (value < MIN_TIRE_ANGLE)			// if less than -pi / 6 set it to -pi/6
			value = MIN_TIRE_ANGLE;
	if (value > MAX_TIRE_ANGLE)			// if greater than pi/6 set it to pi/6
			value = MAX_TIRE_ANGLE;

	_state.setTireAngle(value);
	// End Update

	// HEADING // Update x4(t + /\t)
	value = tempHead + (duration * u.getVelocity() * (1/L) * sin(tempAngle));

	if (value < 0)					// if less than 0, set it to the range [0,2pi)
		while (value < 0)
			value = value + M_TWO_TIMES_PI;
	if (value >= M_TWO_TIMES_PI) // if greater than 2pi, set it to the range [0,2pi)
		while (value > M_TWO_TIMES_PI)
			value = value - M_TWO_TIMES_PI;

	_state.setHeading(value);
	// End Update



} // ends stateUpdate


State Vehicle::getState() const
{
	return _state;
} // end getState