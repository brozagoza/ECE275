/* *********** */
/*
* File : main.cpp
* Author : Alejandro Zaragoza
* NetID : azarago3
* Date : 20 October 2015
*
* Description : This program takes in a file and drives a car. Yay.
*
*/
/* *********** */
#include "Input.h"
#include "DataSource.h"
#include "Director.h"
#include "DataSink.h"
#include <iostream>
#include <fstream>
using namespace std;
/* *********** */


int main(int argc, char *argv[]) 
{
	DataSource theInputs;	// used to input the file
	DataSink failure;		// used to execute a failed input file


	if (argc != 3)
	{
		cout << "Usage: catcar controlInputs stateOutputs" << endl;
		return -1;
	} // end if

	theInputs.ReadControlInputs(argv[1]);

	if (!theInputs.validate())
	{
		failure.WriteOutput(argv[2]);
		return -1;
	} // end if


	Director theMan;										// the man
	theMan.ExecuteDirector(theInputs.getVector(), argv[2]); // woah there man calm down


	return 0;
} // end main