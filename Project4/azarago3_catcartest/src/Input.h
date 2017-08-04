#ifndef INPUT_H
#define INPUT_H
/*************/
/*
 * File: Input.h
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date:  17 November 2015
 *
 * Description: This is the input file made by Sprink Master Flex.
 */

/******
 
 IMPORTANT NOTE: STOP READING THIS FILE NOW
 
 THIS FILE IS PRODUCED FOR SUBMISSION AND DEBUGGING OF YOUR PROJECT 4 ONLY.
 YOU MAY **NOT** USE THE CONTENTS OF THIS FILE FOR ANY OTHER PURPUSE, 
 IN ACCORDANCE WITH THE CODE OF ACADEMIC INTEGRITY.
 
 The only modifications permitted (indeed, recommended) for this file are the
 insertions of the code at the top which describe the file's purpose and which
 include your own name, project/date, etc. information. You DO NOT need to
 modify the contents of the remainder of the file to improve comments or 
 readability.
 ******/

// M_PI and other variables are defined in here
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

// the MAX and MIN values for tire angle are used
// in the setTireAngle method
#define MAX_TIRE_ANGLE_RATE 0.5236
#define MIN_TIRE_ANGLE_RATE -0.5236

/* Note: comments in this file thusfar are insufficient for
 a perfect grade in comments */
#ifndef MAX
#define MAX( A, B ) (A > B ? A : B)
#endif
#ifndef MIN
#define MIN( A, B ) (A > B ? B : A)
#endif

/* Class comment goes here */
class Input{
private:
    double _velocity; // commanded vehicle velocity (u1)
    double _tire_angle_rate; // commanded tire angle rate (u2)
    double _timestamp; // time stamp at which this command is valid
    
public:
    // constructs a new Input object with these initial values
    Input(double vel, double tireAngleRate, double timestamp)
    : _velocity(vel),_tire_angle_rate(tireAngleRate),_timestamp(timestamp) { }
    // constructs an empty Input object
    Input() : _velocity(0),_tire_angle_rate(0),_timestamp(0) { }

    double getVelocity() const { return _velocity; } // returns the _velocity
    void setVelocity(double vel) { _velocity = vel; } // sets the _velocity
    double getTireAngleRate() const {return _tire_angle_rate; } // returns the _tire_angle_rate
    void setTireAngleRate(double angle) // sets the _tire_angle_rate
    { _tire_angle_rate = MAX(MIN(angle,MAX_TIRE_ANGLE_RATE),MIN_TIRE_ANGLE_RATE);  }
    double getTimeStamp() const { return _timestamp; } // gets the _timestamp
    void setTimeStamp(double timestamp) { _timestamp = timestamp; } // sets the _timestamp
};

#endif // INPUT_H
