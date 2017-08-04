#ifndef DATASINK_H
#define DATASINK_H
/*************/
/*
* File: DataSink.h
* Author: Alejandro Zaragoza
* NetID: azarago3
* Date: 26 October 2015
*
* Description: Header for DataSink.h
*/

/* Note: comments in this file thusfar are insufficient for
a perfect grade in comments */
#include "Input.h"
#include "DataSource.h"
#include "Director.h"
#include "State.h"
#include <vector>
using namespace std;


// M_PI and other variables are defined in here
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

// the MAX and MIN values for durration are used
// in the validate method

class DataSink {
public:
	// CONSTRUCTORS
	DataSink();								// constructs a new DataSource object


	// INSTANCE METHODS
	void WriteOutput(char* filename);		// writes to output file 
	void AppendState(State in);				// the state that is appended
	vector<State> getVector();
private:
	// VARIABLES
	vector<State> theVector;
};

#endif // DATASINK_H
