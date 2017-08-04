/* *********** */
/*
* File : Input.cpp
* Author : Alejandro Zaragoza
* NetID : azarago3
* Date : 20 October 2015
*
* Description : This file contains the functions that involve the lists. Including adding, removing, initialzing,
*				etc. This was also the alpha for our assignment in case you didn't know mister.
*
*/
/* *********** */
#include <iostream>
using namespace std;
#include "Vehicle.h"
#include "Input.h"
#include "State.h"
/***************/


Input::Input(double vel, double tireAngleRate, double timestamp)
{
	_velocity = vel;
	_tire_angle_rate = tireAngleRate;
	_timestamp = timestamp;
} // end input constructor

Input::Input()
{
	_velocity = 0;
	_tire_angle_rate = 0;
	_timestamp = 0;
} // end input constructor

double Input::getVelocity() const
{
	return _velocity;
} // end getVelocity

void Input::setVelocity(double vel)
{
	_velocity = vel;
} // end setVelocity

double Input::getTireAngleRate() const
{
	return _tire_angle_rate;
} // getTireAngleRate

void Input::setTireAngleRate(double angle)
{
	_tire_angle_rate = angle;
} // end setTireAngleRate

double Input::getTimeStamp() const
{
	return _timestamp;
} // end getTireAngleRate

void Input::setTimeStamp(double timestamp)
{
	_timestamp = timestamp;
} // end setTimeStamp