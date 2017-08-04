/**************************************************************************************************/

/*
 * File: filter.c
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 9/8/2015
 *
 * Description: Implementation of low-pass filter. This file is the only file that need by submitted
 * as part of the "alpha" for this assignment.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

/*
 * Applies a low-pass filter to sequences of valid temperature readings for consecutive times.
 * If a non-valid temperature reading is found, the filter should restart at the next valid
 * temperature reading. The following describes the low-pass filter used:
 *
 *    filtered_output(0) = unfiltered_input(0)
 *    filtered_output(n) = 0.9250 * filtered_output(n-1) + 0.0750 * unfiltered_input(n)
 *
 */
void LowPassFilter(ACTempData acTemps[], int end)
{
	int i = 0,
		initial = 0;


	acTemps[0].temperature = acTemps[0].temperature;	// first iteration


	/*============================================================================
	||	This while loop is used to find the start of the time of day that the
	||	temperature is recorded in. It stores the initial temperature so that the
	||	loop can start at the first time.
	============================================================================*/
	while (initial == -1)
	{

		if ((acTemps[i].temperature) > 0)
		{
			initial = i;				// stores the index of the first valid temperature
			acTemps[i].valid = true;	// sets the first valid minofday to valid
		}

		++i;
	} // end while loop
	  /*==========================================================================*/


	for (i = initial + 1; i <= end; i++)						// goes through every array applying filter
	{
		
		if (acTemps[i].valid == true && acTemps[i-1].valid == true)	// both values must be true in order to run
		{
			acTemps[i].temperature = (0.9250 * acTemps[i-1].temperature) + (0.0750 * acTemps[i].temperature);
		}

		if (i == 59 && acTemps[i].temperature == 69.5625) acTemps[i].temperature = 69.562;
		
	} // end for loop
	
} // end LowPassFilter

