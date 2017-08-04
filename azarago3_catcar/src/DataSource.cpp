/* *********** */
/*
* File : DataSource.cpp
* Author : Alejandro Zaragoza
* NetID : azarago3
* Date : 20 October 2015
*
* Description : THis file reads in the file and assigns it to a vector. This object is used for inputing text files for the car.
*
*/
/* *********** */
#include "DataSource.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/***************/

// constructor
DataSource::DataSource()
{
	//theVector;
} // end constructor

/* ********************************************************************************* */
//  ReadControlInputs method
/* ********************************************************************************* */
void DataSource::ReadControlInputs(char* filename)
{
	string line;						// used to temporarily hold the line
	ifstream controlInputsFile;			// file being opened
	controlInputsFile.open(filename);	
	double sampleTime = 0.0;
	double velocity = 0.0;
	double tireAngleRate = 0.0;


	while (controlInputsFile >> sampleTime)
	{
		controlInputsFile >> velocity;
		controlInputsFile >> tireAngleRate;

		Input tempInp(velocity, tireAngleRate, sampleTime);
		theVector.push_back(tempInp);
	} // end while loop

	controlInputsFile.close();	// lets put that file to bed
    
    for (int i = 0; i < theVector.size(); i++)
    {
        cout << theVector.at(i).getTimeStamp() << " " << theVector.at(i).getTireAngleRate() << " "
        << theVector.at(i).getVelocity() << " " << endl;
    }
    
	sort();

	controlInputsFile.close();
	return;
} // end ReadFile

/* *************************************************************************************************************
|	sort()
|
|	Purpose: Sorts the vector by timestamps. Calls upon two private functions to get the job done,
|
****************************************************************************************************************/
void DataSource::sort()
{
	QuickSort(0, theVector.size() - 1);
    
    

} // end sort

  /**************************************************************************************************************
  |	QuickSort(int i, int k)
  |
  |	Purpose: Aids in the sorting of the vectors. Uses recurrsion and another method "Partition."
  |
  ****************************************************************************************************************/
void DataSource::QuickSort(int i, int k)
{
	int j = 0;

	/* If there are 1 or zero elements to sort,
	partition is already sorted hehehe i get this off somewhere*/
	if (i >= k)
		return;

	/* Partition the data within the array. Value j returned
	from partitioning is location of last element in low partition. */
	j = Partition(i, k);

	/* Recursively sort low partition (i to j) and
	high partition (j + 1 to k) */
	QuickSort(i, j);
	QuickSort(j + 1, k);

	return;
} // end QuickSort


  /* *************************************************************************************************************
  |	Partition(int i, int k)
  |
  |	Purpose: Partitions the vector from the two given values.
  |
  ****************************************************************************************************************/
int DataSource::Partition(int i, int k)
{
	int l = 0;
	int h = 0;
	int midpoint = 0;
	Input pivot;
	Input temp;
	bool done = false;

	// Picking a middle as pivot
	midpoint = i + (k - i) / 2;
	pivot = theVector.at(midpoint);

	l = i;
	h = k;

	while (!done)
	{
		// Increment 1 while theVector.at(l).timestamp < pivot.timestamp
		while (theVector.at(l).getTimeStamp() < pivot.getTimeStamp())
			++l;

		// Decrement h while pivor.timestamp < theVector.at(h).timestamp
		while (pivot.getTimeStamp() < theVector.at(h).getTimeStamp())
			--h;

		// If there are zero or one element remaing, all #s partitioned Return h
		if (l >= h)
			done = true;
		else
		{
			temp = theVector.at(l);
			theVector.at(l) = theVector.at(h);
			theVector.at(h) = temp;

			++l;
			--h;
		} // end else

	} // end while

	return h;
} // end Partition

bool DataSource::validate()
{
	// The rst element of the sorted list must be at exactly time 0.
	if (theVector.at(0).getTimeStamp() != 0)
		return false;

	int unsigned i = 0;
	for (i = 0; i < theVector.size(); i++)
	{
		// Commanded tire angle rate must be between [-0.5236, 0.5236]
		if (theVector.at(i).getTireAngleRate() < MIN_TIRE_ANGLE_RATE || theVector.at(i).getTireAngleRate() > MAX_TIRE_ANGLE_RATE)
			return false;

		// Commanded velocity must be between [0, 30] m/s
		if (theVector.at(i).getVelocity() < 0 || theVector.at(i).getVelocity() > 30)
			return false;

		// Time Values must be non-negative
		if (theVector.at(i).getTimeStamp() < 0)
			return false;

		// Duration between shared sorted input objects must be between [5, 201]ms
		if (i != theVector.size() - 1)
		{
			double durration = theVector.at(i + 1).getTimeStamp() - theVector.at(i).getTimeStamp();
			if (durration < 0.005 || durration > 0.201)
				return false;
		} // end if

	} // end for

	return true;
} // end validate

vector<Input> DataSource::getVector()
{
	return theVector;
}