/* *********** */
/*
* File : State.cpp
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
#include "Vehicle.h"
#include "Input.h"
#include "State.h"
using namespace std;
/***************/

State::State()
{
	_xpos = 0;
	_ypos = 0;
	_tire_angle = 0;
	_timestamp = 0;
	_heading = 0;

	return;
} // end constructor

State::State(double x1, double x2, double x3, double x4, double timestamp)
{
	_xpos = x1;
	_ypos = x2;
	_tire_angle = x3;
	_timestamp = x4;
	_heading = timestamp;

	return;
} // end constructor



double State::getXPos() const
{
	return _xpos;
} // end getXPos


void State::setXPos(double xpos)
{
	_xpos = xpos;
} // end setXPos


double State::getYPos() const
{
	return _ypos;
} // end getYPos


void State::setYPos(double ypos)
{
	
	_ypos = ypos;
} // end setYPos



double State::getTireAngle() const
{
	return _tire_angle;
} // end getTireAngle


void State::setTireAngle(double angle)
{
	_tire_angle = angle;
} // end setTireAngle


double State::getHeading() const
{
	return _heading;
} // end getHeading


void State::setHeading(double heading)
{	
	_heading = heading;
} // end setHeading



double State::getTimeStamp() const
{
	return _timestamp;
} // end getTimeStamp



void State::setTimeStamp(double timestamp)
{
	_timestamp = timestamp;
} // end setTimeStamp
