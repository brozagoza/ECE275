/*
 Author: Jonathan Sprinkle
 Net ID: sprinkjm
 Date:   25 August 2015
 Assignment 0
 
 Contains the implementation for the principal logic of the 
 program, which is the process function.
 
 */

/* get the function signature for what we implement */
#include "process.h"
/* we will need to include string in order to have strcmp */
#include <string.h>

/* process
   This function performs the principal logic of the program, by 
   echoing differently, depending on whether the word matches 
   "Snow" or "Corn".

   If the word matches "Snow" or "Corn" then the echoed line will
   be
    "Snow," the bird said. "Snow, snow."
   or
    "Corn," the bird said. "Corn, corn."

   Otherwise, the echoed line should just be the passed in word
   with no quotes. */

void process( char *word )
{
	/* define the two words that we know we may want to match */
	/* Snow */
	char snow[] = "Snow";
	/* Corn */
	char corn[] = "Corn";
	
	/* if we are passed a NULL pointer, then bad things will happen. */
	if (word != NULL)
	{
		/* match for Snow */
		if (strcmp(snow,word) == 0)
		{
			printf("\"Snow,\" the bird said. \"Snow, snow.\"\n");
		}
		/* match for Corn */
		else if( strcmp(corn,word) == 0)
		{
			printf("\"Corn,\" the bird said. \"Corn, corn.\"\n");
		}
		else
		{
			printf("%s\n", word);
		}
	}
	else
	{
		printf("Error! Received a NULL pointer.\n");
	}
	
}