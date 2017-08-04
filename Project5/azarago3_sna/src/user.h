#ifndef USER_H
#define USER_H
/*************/
/*
 * File: user.h
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 3 Dec 2015
 *
 * Description: This is a class for the User objects used in program 5. This object contains the vairious traits such as followers and
 *              those following. The methods are described as are below.
 */

/* Note: comments in this file thusfar are insufficient for
 a perfect grade in comments */
/*************/
#include <string>
#include <vector>
using namespace std;
/*************/


class User
{
private:
    string _username;           // the username of the user
    
    int _indegree;              // indegree Centrality
    
    vector<string> followers;    // the followers my friend
    
    
    
public:
    // constuctor
    User (string username);
    
    // add to follower
    void addFollower (string follower);
    
    
    // return username
    string getUsername();
    
    // return indegree
    int getIndegree();
    
    // get followers vector
    vector<string> getFollowers();
    
    
};

#endif // USER_H