#ifndef DATASOURCE_H
#define DATASOURCE_H
/*************/
/*
* File: DataSource.h
* Author: Alejandro Zaragoza
* NetID: azarago3
* Date: 26 October 2015
*
* Description: Header for DataSource.cpp
*/

/* Note: comments in this file thusfar are insufficient for
a perfect grade in comments */


// M_PI and other variables are defined in here
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include "Input.h"
#include "DataSource.h"
#include <vector>
using namespace std;

// the MAX and MIN values for durration are used
// in the validate method
#define MIN_DURATION 0.005;
#define MAX_DURATION 0.201;

class DataSource {
public:
	// CONSTRUCTORS
	DataSource();								// constructs a new DataSource object

	// INSTANCE METHODS
	void ReadControlInputs(char* filename);		// reads in file
	void sort();								// sorts this object's vectors by timestamp
	bool validate();							// returns true if vectors from inp valid
	vector<Input> getVector();
private:
	// VARIABLES
	vector<Input> theVector;					// vector of all the input objects

	// INSTANCE METHODS
	void QuickSort(int i, int k);				// used by sort() 
	int Partition(int i, int k);				// used by sort()
};

#endif // DATASOURCE_H
