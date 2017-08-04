/* *********** */
/*
* File : DataSink.cpp
* Author : Alejandro Zaragoza
* NetID : azarago3
* Date : 20 October 2015
*
* Description : Writes the resulting vector from Director to a file. This is an object.
*
*/
/* *********** */
#include "DataSink.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/***************/

// constructor
DataSink::DataSink()
{
	//theVector;
} // end constructor

// method
void DataSink::WriteOutput(char* filename)
{
	ofstream outputFile;			// file being written to
	outputFile.open(filename);

	int unsigned i = 0;
	for (i = 0; i < theVector.size(); i++)
	{
		outputFile << theVector.at(i).getTimeStamp() << ",";
		outputFile << theVector.at(i).getXPos() << ",";
		outputFile << theVector.at(i).getYPos() << ",";
		outputFile << theVector.at(i).getTireAngle() << ",";
		outputFile << theVector.at(i).getHeading() << endl;

	} // end for loop

	outputFile.close();
} // end WriteOutput

// method
void DataSink::AppendState(State in)
{
	theVector.push_back(in);
} // end AppendState

// method
vector<State> DataSink::getVector()
{
	return theVector;
} // end getVector