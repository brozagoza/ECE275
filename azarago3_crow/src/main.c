/*
 Author: Jonathan Sprinkle
 Net ID: sprinkjm
 Date:   25 August 2015
 Assignment 0
 
 Contains the main function. 
 
*/

#include <stdio.h>
#include <stdlib.h>

/* The maximum string size. */
#define MAX_STRING 32

/* include the header for the function we want to call after we get
   the inputs from the user. */
#include "process.h"

int main( void )
{
	/* Read from scanf into this buffer */
	char buffer[MAX_STRING+1];
	/* Used to store the result from scanf */
	int result = 0;
	
	/* Prompt the user. */
	printf("Enter your word: ");

	/* Scan the word from the user.
	   Note the use of 32 to limit the amount of the string we capture,
	   in order to prevent a buffer overflow situation; your logic will
	   be different when processing the command line arguments. */
	result = scanf("%32s", buffer);
	
	/* we want to make sure that scanf returns a 1, since that will 
	   indicate that exactly 1 string was matched. */
	if (result == 1) {
		process(buffer);
	}
	/* This should tell the user that something went wrong */
	else
	{
		printf("Error! Did not match input format.\n");
		/* since something prevented us from running the program
		   at all, we return that we failed. */
		return EXIT_FAILURE;
	}
	
	/* return success, if we got to this point. */
	return EXIT_SUCCESS;
	
}
