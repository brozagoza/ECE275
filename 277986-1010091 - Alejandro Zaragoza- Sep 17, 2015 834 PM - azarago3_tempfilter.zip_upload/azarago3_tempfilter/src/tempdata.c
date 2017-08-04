/**************************************************************************************************/

/*
 * File: tempdata.c
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 9/8/2015
 *
 * Description: Implementation of functions for operating on the ACTempData structure.
 *              Note that the LowPassFilter fcn has been moved to filter.{h,c}
 *
 */

/**************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "bool.h"
#include "tempdata.h"

/**************************************************************************************************/

/* Reads tempertures from an input file specified by fileName line-by-line using the format:
 *
 *    HH:MM TT.T
 *
 * HH:MM represents the time at which the temperature was recorded and is specific in 24 hour
 * format.
 *
 * TT.T represents the recorded temperature reported in Fahrenheit as a double precision value.
 *
 * The time and temperature will be separated by one or more whitespace characters.
 *
 * All lines that do not exactly match this format will be ignored.
 *
 * Returns false if the specified file could not be opened, and true otherwise.
 *
 */
bool ReadTempDataFromFile(ACTempData acTemps[], char *fileName, int *end)
{
	FILE* inFile = NULL;			// File Pointer
	inFile = fopen(fileName, "r");	// opens the file for reading
	int i = 0,						// the famous index IS BACK AND ITS BETTER THAN EVER!!!!!!!
		hour = 0,					// used for what time to store the data in
		min = 0,
		num = 0;
	double temp = 0;				// used to temporally store temp



	if (inFile == NULL)				// if File could not be opened
		return false;

	for (i = 0; i < MinPerDay; i++)
	{
		acTemps[i].exists = false;							// sets all arrays to false until later determined if true or not
	} // end for loop



	while (!feof(inFile))
	{
		fscanf(inFile, "%d%*c%d%lf", &hour, &min, &temp);		// scans in HH:MM T.TTT
		num = min + (hour * 60);
		acTemps[num].temperature = temp;						// stores the temp in the proper min of day

		acTemps[num].exists = true;								// file exits so it can be written later

		if (num + 1 >= MinPerDay)
			break;

	} // end while loop

	*end = num;				// end is given the last array


	fclose(inFile);
   return true;
}

/**************************************************************************************************/

/*
 * Remove any erroneous temperature readings. An error temperature reading is defined as a
 * temperature reading that is either more than 5 degrees above or 5 below the temperature
 * recorded in the previous minute. All erroneous temperature readings should be marked as invalid.
 * The first element read in from a file is always considered valid.
 */
void RemoveErroneousData(ACTempData acTemps[], int end)
{
	int i = 0,				// the usual index. ITS BACK
		initial = -1;		// index of the first valid temperature in the array


/*============================================================================
||	For loop sets all the values in the array to false so it can be easier.
============================================================================*/
	for (i = 0; i < MinPerDay; i++)
		acTemps[i].valid = false;
/*==========================================================================*/

	i = 0;					// resets i to 0

/*============================================================================
||	This while loop is used to find the start of the time of day that the
||	temperature is recorded in. It stores the initial temperature so that the
||	loop can start at the first time.
============================================================================*/
	while (initial == -1 && i < MinPerDay)
	{

		if ((acTemps[i].temperature) > 0)
		{
			initial = i;				// stores the index of the first valid temperature
			acTemps[i].valid = true;	// sets the first valid minofday to valid
		}

		++i;
	} // end while loop
/*==========================================================================*/


	for (i = initial + 1; i <= end; i++)
	{
	


		if ( ((acTemps[i].exists == true) && (acTemps[i-1].exists == true)) 
			&& 
			(
			 (acTemps[i].temperature >(acTemps[i-1].temperature + 5) ) || 
			 (acTemps[i].temperature < (acTemps[i-1].temperature - 5))
			) 
			)
		{
			acTemps[i].valid = false;			// if previous temp is 5 above or 5 below, mark as invalid

			if (i + 1 < end)
				acTemps[i + 1].valid = true;

			++i;
		} // ends the lord of the if statements HAHAHAHAHA
		else if (acTemps[i].exists == true)
		{
			acTemps[i].valid = true;
			
		}
									
	} // end for loop



	for (i = 0; i < MinPerDay; i++)
	{
		if (acTemps[i].exists == false)
			acTemps[i].status = false;
	}
} // end function

/**************************************************************************************************/

/*
 * Analyzes the sequence of valid temperatures to determine the state of the AC. If a non-valid
 * temperature reading is found, the trend extraction should restart at the next valid temperature
 * reading. Trend extraction analysis operate as follows:
 *
 * 1. The AC status for the first entry in a sequence of valid reading is always Off.
 *
 * 2. For a valid temperature reading that does not start a sequence:
 *
 *    A. If the previous AC status was Off, then consider the following: If (1) the previous 
 *       temperature is valid, and (2) the current temperature is less than the previous temperature, 
 *       and (3) the next temperature is valid and less than the current temperature, then the AC 
 *       status for the current temperature will be On.
 *
 *    B. If the previous AC status was On, then consider the following: If the current temperature 
 *       is less than or equal to the previous temperature, then the AC status for the current 
 *       temperature will be On
 *
 *    C. Otherwise, the AC status for the current temperature will be Off.
 *
 */
void TrendExtraction(ACTempData acTemps[], int end)
{
	int initial = -1,
		i = 0;

	/*============================================================================
	||	This while loop is used to find the start of the time of day that the
	||	temperature is recorded in. It stores the initial temperature so that the
	||	loop can start at the first time.
	============================================================================*/
	while (initial == -1 && i < MinPerDay)
	{


		if ((acTemps[i].temperature) > 0)
		{
			initial = i;				// stores the index of the first valid temperature
			acTemps[i].status = false;
		}
		++i;
	} // end while loop
	/*==========================================================================*/


	/*=========================================================================
	|	This for loop is used to determine what the AC status will be (on/off).
	|	It can easily be infered what is on or off by the comments by the if and
	|	else statements. This for loop goes until it reaches the second to last
	|	array.
	==========================================================================*/
	for (i = initial + 1; i < end; i++)
	{
		if (
			(acTemps[i - 1].status == false) &&						// previous AC status was off
			(acTemps[i - 1].valid == true) &&						// the previous temperature is valid
			(acTemps[i].temperature < acTemps[i - 1].temperature) &&// current temp is less than previous temp
			(acTemps[i + 1].valid == true) &&						// next temp is valid
			(acTemps[i + 1].temperature < acTemps[i].temperature)	// next temp is less than current
			)
		{
			acTemps[i].status = true;		// AC Status is turned ON
		}
		else if (
			(acTemps[i - 1].status == true) &&						// previous AC status was on
			(acTemps[i].temperature <= acTemps[i - 1].temperature)	// current temp less/equal to prev temp
			)
		{
			acTemps[i].status = true;		// AC Status is turned ON
		}
		else
			acTemps[i].status = false;
	} // end for loop
	  /*==========================================================================*/
	  /*==========================================================================*/


	  /*============================================================================
	  ||	The same if/else statements are here, but in this case 'i' will equal
	  ||	'end,' which IS the last array with a value from the text file. The
	  ||	i+1 checks are not here because that would cause the array to go
	  ||	out of bounds.
	  ============================================================================*/
	if (
		(acTemps[i - 1].status == false) &&						// previous AC status was off
		(acTemps[i - 1].valid == true) &&						// the previous temperature is valid
		(acTemps[i].temperature < acTemps[i - 1].temperature)	// current temp is less than previous temp
		)
	{
		acTemps[i].status = true;		// AC Status is turned ON
	}
	else if (
		(acTemps[i - 1].status == true) &&						// previous AC status was on
		(acTemps[i].temperature <= acTemps[i - 1].temperature)	// current temp less/equal to prev temp
		)
	{
		acTemps[i].status = true;		// AC Status is turned ON
	}
	else
		acTemps[i].status = false;
	/*==========================================================================*/

   
}

/**************************************************************************************************/

/* Writes all valid tempertures readings and AC status to an output file specified by fileName
 * using the format:
 *
 *    HH:MM TT.TTT AC
 *
 * HH:MM reports the time at which the temperature was recorded specified in 24 hour format.
 *
 * TT.TTT represents the filtered temperature value in Fahrenheit as a double precision value with
 * three decimal digits of precision.
 *
 * AC reports the determined status of the air conditioner, where a 0 represents the the AC
 * was Off and a 1 represents the AC was On.
 *
 * Each entry is separated by a single tab character (\t).
 *
 * Retruns false if the specified file could not be written to, and true otherwise.
 *
 */
bool WriteTempDataToFile(ACTempData acTemps[], char *fileName, int end)
{
	FILE* outFile = NULL;			// File Pointer
	outFile = fopen(fileName, "w");	// opens the file for reading

	int i = 0,						// the index is back BROS
		initial = -1,				// stores the index of the first temp value
		hour = 0,
		min = 0;

	

	/*============================================================================
	||	This while loop is used to find the start of the time of day that the
	||	temperature is recorded in. It stores the initial temperature so that the
	||	loop can start at the first time.
	============================================================================*/
	while (initial == -1)
	{
		if (i == MinPerDay && end != 0)				// if for any reason the text file is empty, end program
			return false;
		else if (i == MinPerDay && end == 0)		// catches blank text documents
			return true;

		if ((acTemps[i].temperature) > 0)
		{
			initial = i;				// stores the index of the first valid temperature
			acTemps[i].status = false;
		}
		++i;
	} // end while loop
	/*==========================================================================*/


	for (i = initial; i <= end; i++)
	{
		hour = i / 60;			// stores the hours
		min = i % 60;			// stores the minutes

		if (acTemps[i].exists == true && acTemps[i].valid == true)
		{
		if (hour < 10 && min < 10)
			fprintf(outFile, "0%d:0%d\t%.3lf\t%d\n", hour, min, acTemps[i].temperature, acTemps[i].status);
		else if (hour < 10 && min >= 10)
			fprintf(outFile, "0%d:%d\t%.3lf\t%d\n", hour, min, acTemps[i].temperature, acTemps[i].status);
		else if (hour >= 10 && min < 10)
			fprintf(outFile, "%d:0%d\t%.3lf\t%d\n", hour, min, acTemps[i].temperature, acTemps[i].status);
		else if (hour >= 10 && min >= 10)
			fprintf(outFile, "%d:%d\t%.3lf\t%d\n", hour, min, acTemps[i].temperature, acTemps[i].status);
		}

		
	} // end for loop

	fclose(outFile);

   return true;
}

/**************************************************************************************************/

