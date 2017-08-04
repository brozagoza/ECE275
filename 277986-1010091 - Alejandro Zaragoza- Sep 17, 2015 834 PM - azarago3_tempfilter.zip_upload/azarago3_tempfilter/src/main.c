/**************************************************************************************************/

/*
 * File: main.c
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 9/8/2015
 *
 * Description: Main functionality for simple C program that reads an input file formatted with
 * temperature data, manipulates and smooths that data, and write analysis to an output file.
 *
 */

/**************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "bool.h"
#include "tempdata.h"
#include "filter.h"

/**************************************************************************************************/

int main(int argc, char *argv[])
{
   ACTempData acTemps[MinPerDay];
   int end = 0;
   
   /*
    * check for the correct number of command line arguments.  If incorrect
    * provide a simple usage message to the assist the user
    *
    */
	if( argc != 3 ) {
      printf("\nUsage: %s inputFile outputFile \n\n", argv[0]);
      return -1;
	}
	
	if (!ReadTempDataFromFile(acTemps, argv[1], &end)) {
		printf("Could not read from input file %s\n", argv[1]);
		return -1;
	}
	else
		ReadTempDataFromFile(acTemps, argv[1], &end);

   RemoveErroneousData(acTemps, end);
   LowPassFilter(acTemps, end);
   TrendExtraction(acTemps, end);
   
   if( !WriteTempDataToFile(acTemps, argv[2], end) ) {
      printf("Could not write to output file %s\n", argv[2]);
      return -1;
   }
   else
   {
	   WriteTempDataToFile(acTemps, argv[2], end);
   } // end else



	return 0;
}

/**************************************************************************************************/
