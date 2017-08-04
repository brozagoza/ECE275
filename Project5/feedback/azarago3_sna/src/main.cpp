/*************/
/*
 * File: main.cpp
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 3 Dec 2015
 *
 * Description: This program is crazy. It takes in a list of twitter accounts and finds the one with the most degree incentrality. 
 *              It then prints all the users within two depth and their indgree incetrality.
 */

/* Note: comments in this file thusfar are insufficient for
 a perfect grade in comments */
#include "user.h"
#include "graph.h"
/*************/
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
/*************/
using namespace std;
/*************/


// it gets done now bois
int main (int argc, char *argv[])
{
    Graph chiken;
    ofstream outputFile(argv[2]);
    if (argc != 3)
    {
        outputFile << "Usage: sna inputFile outputFile" << endl;
        return -1;
    }
    
    if (chiken.readInFile(argv[1], argv[2]))
        chiken.printAlpha(argv[2]);
    
    
} // end main