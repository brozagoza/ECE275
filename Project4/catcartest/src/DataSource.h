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
#include <iostream>
#include <string>
#include <sstream>
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
	DataSource(string filecontents );
    
    
    // DECONSTRUCTOR
    ~DataSource( );

    
    bool processFile( );
    
	vector<Input> getVector();
private:
	// VARIABLES
	vector<Input> _inputs;					// vector of all the input objects
    string _filecontents;                   // the contents of the file as a string
    stringstream _filecontentsstream;       // a streamed version of the file's contents
    

	// INSTANCE METHODS
	void QuickSort(int i, int k);				// used by sort() 
	int Partition(int i, int k);				// used by sort()
    
public:
    // returns false if any data are invalid
    // should only be called after data are sorted
    bool validate( );
    
    // reads data in from teh file. returns false
    // if unable to read data from the file at all of if
    // any lines fail to parse correctly
    bool readData( );
    
    // performs quick sort on the list
    void sort ( );
    
    string getFileContents() const { return _filecontents; }
};

#endif // DATASOURCE_H
