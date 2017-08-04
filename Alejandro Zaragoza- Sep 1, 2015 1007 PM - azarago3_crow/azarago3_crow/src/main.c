/*
 Author: Alejandro Zaragoza
 Net ID: azarago3
 Date:   3 September 2015
 Assignment 0
 
 This function reads in from the command line and prints out statements or calls functions according to what the command line says.
 
 
*/

#include <stdio.h>
#include <string.h>

/*
Defining a function that prints the usage statement.
*/
int printUsage();


int main(int argc, char* argv[])
{
	int i = 0;

	//printf("Checking for correct number of parameters...\n");


	if (argc == 2)
	{
		//printf("Correct list of args... checking special words\n");
		if (strcmp(argv[1], "Snow") == 0 ||
			strcmp(argv[1], "Corn") == 0)
		{
			printf("\"%s.\" the bird said, \"%s, %s.\"\n", argv[1], argv[1], argv[1]);			// if command line contains "Snow" or "Corn" this is printed
		} //  end if
		else
		{
			printf("%s\n", argv[1]);															// simply prints what the command line contained
		}
	} // end if
	else if (argc > 2)
	{
		//printf("Echoing all remaining arguments...\n");
		for ( i = 1; i < argc; i++)
		{
			printf("%s\n", argv[i]);
		} // end for loop
	} // end else if
	else
	{
		//printf("Error, not enough args, printing Usuage statement\n");
		printUsage();
	}
	return 0;
}


/*
This function simply returns the print usage statement from the project 0 handout.
*/
int printUsage()
{
	printf("This program that echoes a word differently, depending on the word that is passed in. Usage: crow [word]\n");
	printf("\tcrow [word]\n");
	return 0;
} // end printUsage
