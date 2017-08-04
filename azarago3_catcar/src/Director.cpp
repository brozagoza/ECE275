/* *********** */
/*
* File : Director.cpp
* Author : Alejandro Zaragoza
* NetID : azarago3
* Date : 20 October 2015
*
* Description : THis file directs the flow of execution of the text files after the file is read in. It writes to
*               the file and calculates.
*
*/
/* *********** */
#include "Director.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/***************/

Director::Director()
{

} // end constructor

void Director::ExecuteDirector(vector<Input> inputs, char* filename)
{
	Vehicle temp;
	DataSink outtie;
	State tempState;

	int unsigned i = 0;
	double durration = 1.0;

	

	for (i = 0; i < inputs.size(); i++)
	{
		

		if (i == inputs.size() - 1) 
			durration = 0.200;
		else
			durration = inputs.at(i + 1).getTimeStamp() - inputs.at(i).getTimeStamp();
		
		//if (i == 0)
		//{
		//	//double _velocity; // commanded vehicle velocity (u1)
		//	//double _tire_angle_rate; // commanded tire angle rate (u2)
		//	tempState.setTireAngle(inputs.at(i).getTireAngleRate());
		//	tempState.setHeading(inputs.at(i).getVelocity() * (1/L) * sin(tempState.getTireAngle()));
		//	tempState.setXPos( inputs.at(i).getVelocity() * cos(tempState.getTireAngle()) * cos(tempState.getHeading()));
		//	tempState.setXPos(inputs.at(i).getVelocity() * cos(tempState.getTireAngle()) * sin(tempState.getHeading()));
		//	
		//} // end if
		//else
		//{
			temp.stateUpdate(inputs.at(i), durration);	// updates the state based on the info provided
			tempState = temp.getState();
		//} // end else




		if (i >= inputs.size() - 1)
		{
			tempState.setTimeStamp(0.200 + inputs.at(i).getTimeStamp());
		}
		else
		{
			
			Input tempStateNext = inputs.at(i + 1);
			tempState.setTimeStamp(tempStateNext.getTimeStamp());
		}


		outtie.AppendState(tempState);		// adds the next state to outtie
	} // end for loop


	outtie.WriteOutput(filename);
	
} // end execute