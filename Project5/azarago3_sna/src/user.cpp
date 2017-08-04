/*************/
/*
 * File: user.cpp
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 3 Dec 2015
 *
 * Description: main
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


/* =====================================================================================================================
 *  Constructor User
 *
 *  Constructs a user object from the given string
 *
 ===================================================================================================================== */
User::User (string username)
{
    _username = username;
    _indegree = 0;
    
} // end constructor


/* =====================================================================================================================
 *  Method addFollower
 *
 *  Adds follower to this user as a string into a vector.
 *
 ===================================================================================================================== */
void User::addFollower(string follower)
{
    followers.push_back(follower);
    
    ++_indegree;
    
} // end addFollower


/* =====================================================================================================================
 *  Method getFollowers
 *
 *  Returns a vector of string object containing the followers of this user.
 *
 ===================================================================================================================== */
vector<string> User::getFollowers()
{
    return followers;
}


/* =====================================================================================================================
 *  Method getIndegree
 *
 *  Finds the master of the given slave that was passed.
 *
 ===================================================================================================================== */
int User::getIndegree()
{
    return _indegree;
} // end getIndegree


/* =====================================================================================================================
 *  Method getUsername
 *
 *  Returns the username as a string.
 *
 ===================================================================================================================== */
string User::getUsername()
{
    return _username;
} // end getUsername


