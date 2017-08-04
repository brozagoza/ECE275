#ifndef GRAPH_H
#define GRAPH_H
/*************/
/*
 * File: graph.h
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 3 Dec 2015
 *
 * Description: Check the cpp file for more info
 */

/* Note: comments in this file thusfar are insufficient for
 a perfect grade in comments */
#include "user.h"
/*************/
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
/*************/

class Graph
{
private:
    vector<User> userDatabase;
    
public:
    // constructor
    Graph ();
    
    // reads in the file
    bool readInFile (char* filename, char* outname);
    
    // check if user already exists
    bool userCheck (string user);
    
    // find the master
    int findMaster (string user);
    
    vector<User> suggestedFriendsVector (User high);
    
    vector<User> printSuggestions (vector<User> suggestedFriends);
    
    // just to print the young alpha
    bool equalCompare(string maxStr, string otherStr);
    void printAlpha (char* filename);
    
    vector<User> alphabetize (vector<User> in);
    
    vector<User> removeDuplicates (vector<User> in);
};

#endif // end