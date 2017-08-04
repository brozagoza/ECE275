#ifndef DIRECTOR_H
#define DIRECTOR_H
/*************/
/*
* File: Director.h
* Author: Alejandro Zaragoza
* NetID: azarago3
* Date: 26 October 2015
*
* Description: The dircetor controls the overall flow of everything.
*/

/* Note: comments in this file thusfar are insufficient for
a perfect grade in comments */
#include "Input.h"
#include "DataSink.h"
#include "DataSource.h"
#include "Director.h"
#include "State.h"
#include "Vehicle.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Director
{
public:
	// CONSTRUCTOR
	Director();

	// INSTANCE METHODS
	void ExecuteDirector(vector<Input> inputs, char* filename);

private:

};
#endif // DIRECTOR_H