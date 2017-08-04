/*************/
/*
 * File: graph.cpp
 * Author: Alejandro Zaragoza
 * NetID: azarago3
 * Date: 3 Dec 2015
 *
 * Description: Graph class that reads in all the files and prints out the required
 */

/* Note: comments in this file thusfar are insufficient for
 a perfect grade in comments */
/*************/
#include "graph.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
/*************/



//// USED FOR WHEN COMPARING STRINGS WITHOUT TAKING INTO CONSIDERATION THE CASE OF THE STRINGS
namespace
{
    struct case_insensitive_less : public std::binary_function< char,char,bool >
    {
        bool operator () (char x, char y) const
        {
            return toupper( static_cast< unsigned char >(x)) <
            toupper( static_cast< unsigned char >(y));
        }
    };
    
    bool NoCaseLess(const std::string &a, const std::string &b)
    {
        return std::lexicographical_compare( a.begin(),a.end(),
                                            b.begin(),b.end(), case_insensitive_less() );
    }
    
} // end case checker bruh lets go





/* ========================================================================
 *  Graph Constructor
 *
 *  Simply creates a graph that just contains a vector of Users.
 *
 ======================================================================== */
Graph::Graph ()
{
    vector<User> userDatabase;
} // end constructor



/* =====================================================================================================================
 *  Method readinFile
 *
 *  Takes in the path to the input file as a string and inputs the users from this file into vectors.
 *
 ===================================================================================================================== */
bool Graph::readInFile (char* filename, char* outname)
{
    string master;                    // used to temporarily hold the line
    string slave;                     // temporarily holds the follower
    ifstream inputFile(filename);     // file being opened
    
    if (!inputFile)
    {
        ofstream outputFile(outname);
        
        outputFile << "FILE IS BROKEN BRUH" << endl;
        return false;
    }
    
    if (inputFile.peek() == std::ifstream::traits_type::eof())
    {
        ofstream outputFile(outname);
        
        outputFile << "FILE IS EMPTY BRUH" << endl;
        return false;
    }
    
    while (inputFile >> master)
    {
        inputFile >> slave;
        
        if (!userCheck (master))    // if the user isn't already in the database
        {
            
            userDatabase.push_back(master);
            userDatabase.back().addFollower(slave);
        }
        else                        // since user is already in the database just add a new follower
        {
            userDatabase.at( findMaster(master) ).addFollower( slave );
        }
        
        
        int unsigned i = 0;
        bool done = false;
        for (i = 0; i < userDatabase.size(); i++)
        {
            // used to find out if slave has already been declared as a user even if it doesnt have followers
            if (slave.compare( userDatabase.at(i).getUsername()) == 0)
                done = true;
        }
        
        if (!done)
            userDatabase.push_back(slave);
        
        
        
    } // end while loop
    
    
    return true;
} // end readinFile

/* =====================================================================================================================
 *  Method userCheck
 *
 *  Simply checks if the user already exists in
 *
 ===================================================================================================================== */
bool Graph::userCheck (string user)
{
    int unsigned i = 0;
    
    for (i = 0; i < userDatabase.size(); i++)
    {
        if  (userDatabase.at(i).getUsername().compare(user) == 0)
            return true;
    } // end for loop
    
    return false;
    
} ///////////////////////////////// end userCheck



/* =====================================================================================================================
 *  Method findMaster
 *
 *  Finds the master of the given slave that was passed.
 *
 ===================================================================================================================== */
int Graph::findMaster (string user)
{
    int unsigned i = 0;
    
    for (i = 0; i < userDatabase.size(); i++)
    {
        if (userDatabase.at(i).getUsername().compare(user) == 0)
            return i;
    }
    
    return -1;
} //////////////////////////////////////////////////////////////// findMaster











/* =====================================================================================================================
 *  Method printAlpha
 *
 *  Originally to just print the alpha, now prints all the requirements.
 *
 ===================================================================================================================== */
void Graph::printAlpha(char* filename)
{
    int unsigned i = 0;
    int maxIndex = 0;
    
    
    for (i = 0; i < userDatabase.size(); i++)
    {
       // cout << userDatabase.at(i).getUsername() << " followers:" << userDatabase.at(i).getIndegree() << endl;
        
        
        
        
        if ( userDatabase.at(i).getIndegree() == userDatabase.at(maxIndex).getIndegree())
        {
            
            if ( equalCompare(userDatabase.at(i).getUsername(), userDatabase.at(maxIndex).getUsername()) == true )
                maxIndex = i;
            
            
        } // end if statement
        
        else if (userDatabase.at(i).getIndegree() > userDatabase.at(maxIndex).getIndegree())
            maxIndex = i;
        
        

        
    } // end for loop
    
    ofstream outputFile(filename);
    
    
    outputFile << "Looking for new accounts for " << userDatabase.at(maxIndex).getUsername() << " (" << userDatabase.at(maxIndex).getIndegree() <<  ") to follow" << endl;
    
    
    vector <User> suggestedFriends;
    suggestedFriends = suggestedFriendsVector (userDatabase.at(maxIndex)); // will return a vector containing what to be printed
    
    suggestedFriends = printSuggestions(suggestedFriends);
    
    for (i = 0; i < suggestedFriends.size(); i++)
        outputFile << suggestedFriends.at(i).getUsername() << " " << "(" << suggestedFriends.at(i).getIndegree() << ")" << endl;
    
    outputFile.close();
    
} // print for the alpha


/* =====================================================================================================================
 *  Method suggestedFriendsVector
 *
 *  Collects all the suggested friends into one vector. Debugging print statements commented out.
 *
 ===================================================================================================================== */
vector<User> Graph::suggestedFriendsVector (User high)
{
    vector <string> depthOneFollowersString =  high.getFollowers();
    vector <User> depthOneFollowers; // followerCeption dawg
    
    //cout << "THIS MAX USER HAS FOLLOWERS: " << depthOneFollowersString.size() << endl;
    
    int unsigned i = 0;
    int unsigned j = 0;
    int unsigned r = 0;
    
    //cout << endl;
    
    for (j = 0; j < userDatabase.size(); j++)
        for (i = 0; i < depthOneFollowersString.size(); i++)
        {
            // cout << theFollowers.at(i) << " ";
            
           // cout << userDatabase.at(j).getUsername() << endl;
            
            if (userDatabase.at(j).getUsername().compare( depthOneFollowersString.at(i)) == 0)
            {
                if (userDatabase.at(j).getIndegree() == 0)
                    break;
                
                depthOneFollowers.push_back(userDatabase.at(j));
                cout << userDatabase.at(j).getUsername() << " with follow " << userDatabase.at(j).getFollowers().size() << " added to the shit" << endl;
                break;
            }
        } // end for inner for loop
    
    //cout << endl;
    
    //cout << "DEPTH ONE SIZE IS " << depthOneFollowers.size() << endl;
    
    //cout << endl;
    //// DEPTH TWO FOLLOWERS ARE NOW IN THEIR OWN VECTOR MY BROTHERS LET US FIGHT
    vector <string> depthTwoFollowerString;
    
    for (r = 0; r < depthOneFollowers.size(); r++)
    {
        //cout << depthOneFollowers.at(r).getUsername() << " ";
        vector <string> temp = depthOneFollowers.at(r).getFollowers(); // holds all the followers of this man
        //cout << temp.size() << endl;
        
        for (i = 0; i < temp.size(); i++)
        {
            depthTwoFollowerString.push_back(temp.at(i));
            //cout << temp.at(i) << " added to the depthTwoStr" << endl;
        }
        
    } // end for loop
    //cout << endl;
    //cout << "DEPTH TWO SIZE IS " << depthTwoFollowerString.size();
    
    
    ////// TO ERASE THE REPEATS IN THE DEPTH TWO ONE
    for (r = 0; r < depthTwoFollowerString.size(); r++)
    {
        for (i = 0; i < depthOneFollowersString.size(); i++)
        {
            if (depthTwoFollowerString.at(r).compare( depthOneFollowersString.at(i)) == 0)
                depthTwoFollowerString.erase(remove(depthTwoFollowerString.begin(), depthTwoFollowerString.end(),depthTwoFollowerString.at(i).c_str()));
        } // end inner for
        
        // vec.erase(std::remove(vec.begin(), vec.end(), 8), vec.end());
    } // end for
    
    cout << " DEPTH TWO SIZE IS " << depthTwoFollowerString.size() << endl;
    
    
    //////// TO HOLD ALL THE ONES TO BE PRINTED (before sorting them of course hehehe)
    vector<User> suggestedFriends;
    
    // adds all the second friends
    for (j = 0; j < userDatabase.size(); j++)
        for (i = 0; i < depthTwoFollowerString.size(); i++)
        {
            // cout << theFollowers.at(i) << " ";
            
             //cout << userDatabase.at(j).getUsername() << endl;
            
            if (userDatabase.at(j).getUsername().compare( depthTwoFollowerString.at(i)) == 0)
            {
                suggestedFriends.push_back(userDatabase.at(j));
                //cout << userDatabase.at(j).getUsername() << " with follow " << userDatabase.at(j).getFollowers().size() << " added to the bitchNIGGA" << endl;
                break;
            }
        } // end for inner for loop
    
    // adds all the first friends
    for (i = 0; i < depthOneFollowers.size(); i++)
    {
        suggestedFriends.push_back(depthOneFollowers.at(i));
        
    }
    //cout << "the total amount of people to be printed out is " << suggestedFriends.size() << endl;
    
    // prints all the mother fuckers up to this point ; )
    cout << "PRINTING THE ONES IN THE NEGATIVE DIRECTION OF USER" << endl;
    for (i = 0; i < suggestedFriends.size(); i++)
        cout << suggestedFriends.at(i).getUsername() << " " << endl;
    
    
    
    ////////////////////////////////////////////////////////////////////////////////////////
    ///// ALRIGHT HOES LETS WORK BACKWARDS... AS IN THE OTHERWAY ALRIGHT LETS DO THIS WOOH
    ///////////////////////////////////////////////////////////////////////////////////////
    cout << "PRINTING ALL THE ONES IN THE OTHER DIRECTION YOU HOE BAG" << endl;
    for (i = 0; i < userDatabase.size(); i++)
    {
        vector<string> atIfollowers = userDatabase.at(i).getFollowers();
        bool thisGuyIsCool = false;
        
        for (j = 0; j < atIfollowers.size(); j++)
        {
            if (atIfollowers.at(j).compare(high.getUsername()) == 0)
                thisGuyIsCool = true;
        } // end for
        
        int unsigned f = 0;
        
        for (f = 0; f < userDatabase.size(); f++)
        {
            
        } // end for
    } // end for
    
    
    
    
    
    ///////////////////////////////////////////////////////////////////////////////////////
    ///// BELOW THIS COMMENT IT STORES ALL THE USERS THAT ARE NOT BEING FOLLOWED BY THE GUY
    ///////////////////////////////////////////////////////////////////////////////////////
    vector <User> results; // holds the final results as a string
    
    // remove all the ones that are already being follower by the bro with highest in degree
    for (i = 0; i < suggestedFriends.size(); i++)
    {
        vector <string> followers = suggestedFriends.at(i).getFollowers(); // holds the followers currently
        bool addMe = true;
        
        for (j = 0; j < followers.size(); j++)
        {
            if (followers.at(j).compare (high.getUsername()) == 0)
                addMe = false;
        } // end for loop
        
        if (addMe)
        {
            results.push_back(suggestedFriends.at(i));
            cout << suggestedFriends.at(i).getUsername() << "POOOOOOOOOPOPOPOPOP" << endl;
        }
        
    } // end for loop
    vector <User> results2;
    
    for (i = 0; i < results.size(); i++)
    {
        if (!(results.at(i).getUsername().compare(high.getUsername()) == 0))
            results2.push_back(results.at(i));
    }
    
    suggestedFriends = results2;
    
    
    return suggestedFriends;
} // end suggestedFriends


/* =====================================================================================================================
 *  Method printSuggestions
 *
 *  Prints the suggestions in the end of the program.
 *
 ===================================================================================================================== */
vector<User> Graph::printSuggestions(vector<User> suggestedFriends)
{
//    
    int i = 0;
    int j = 0;
    int first = 0;
    User temp("taco");
    
    
    /// Selection sort done on the vector for finding the order to be printed in
    for (i = suggestedFriends.size() - 1; i > 0; i--)
    {
        first = 0;
        
        for (j = 1; j <= i; j++)
        {
            if ( suggestedFriends.at(j).getIndegree() < suggestedFriends.at(first).getIndegree())
                first = j;
            else if (suggestedFriends.at(i).getIndegree() == suggestedFriends.at(first).getIndegree())
            {
                if ( equalCompare(suggestedFriends.at(j).getUsername(), suggestedFriends.at(first).getUsername()) )
                    first = i;
            } // end else if
            
        } // end inner for loop
        
        
        temp = suggestedFriends.at(first);
        suggestedFriends.at(first) = suggestedFriends.at(i);
        suggestedFriends.at(i) = temp;
    } // end outter for loop
    
    
    
    suggestedFriends = alphabetize(suggestedFriends);
    
    return suggestedFriends;
    
} //////////// end print Suggestions


/* =====================================================================================================================
 *  Method alphabetize
 *
 *  Puts the vectors in alphabetical order.
 *
 ===================================================================================================================== */
vector<User> Graph::alphabetize (vector<User> in)
{
    vector<User> inStrings;
    
    int unsigned i = 0;
    int unsigned j = 0;
    
    
    
    for (i = 0; i < in.size();)
    {
        vector<string> usersAtThisSize;
        
        int currentDegree = in.at(i).getIndegree();
        
        
        while ( in.at(i).getIndegree() == currentDegree)
        {
            usersAtThisSize.push_back(in.at(i).getUsername());
            ++i;
            if (i == in.size())
                break;
        }
        
        //sort(usersAtThisSize.begin(), usersAtThisSize.end());
        sort(usersAtThisSize.begin(),usersAtThisSize.end(),NoCaseLess);
        
        for (j = 0; j < usersAtThisSize.size(); j++)
        {
            int unsigned x = 0;
            for (x = 0; x < in.size(); x++)
            {
                if (in.at(x).getUsername().compare(usersAtThisSize.at(j)) == 0)
                {
                    inStrings.push_back(in.at(x));
                }
            } // end for loop
        } // end for loop

        
        //break;
        
    } // end for loop
    
    inStrings = removeDuplicates(inStrings);
    
    return inStrings;
}

/* =====================================================================================================================
 *  Method removeDuplicates
 *
 *  Removes duplicates from the users vector that will be printed in the end.
 *
 ===================================================================================================================== */
vector<User> Graph::removeDuplicates (vector<User> in)
{
    vector<User> returnMe;
    
    int unsigned i = 0;
    int prev = 0;
    
    
    for (i = 0; i < in.size();)
    {
        returnMe.push_back(in.at(i));
        ++i;
        
        if (i == in.size())
            break;
        
        while (in.at(i).getUsername().compare( returnMe.at(prev).getUsername()) == 0)
            ++i;
        
        
        
        ++prev;
    } // end for
    
    
    

    return returnMe;
} // end removeDuplicates

/* =====================================================================================================================
 *  Method equalCompare
 *
 *  Determines if the otherStr being passed in goes first alphabetically then the current string.
 *
 ===================================================================================================================== */
bool Graph::equalCompare(string maxStr, string otherStr)
{
    int unsigned strLen = 0; // the length of the shorter string
    
    
    if (maxStr.length() > otherStr.length())
        strLen = otherStr.length();
    else
        strLen = maxStr.length();
    
    
    int unsigned i = 0;
    
    
    for (i = 0; i < maxStr.length(); i++)
        maxStr.at(i) = tolower(maxStr.at(i));
    
    for (i = 0; i < otherStr.length(); i++)
        otherStr.at(i) = tolower(otherStr.at(i));
    
    
    
    
    for (i = 0; i < strLen; i++)
    {
        if (otherStr.at(i) == '_')
            otherStr.at(i) = 47;
        
        if (maxStr.at(i) == '_')
            maxStr.at(i) = 47;
        
        
        if ((int)otherStr.at(i) > (int)maxStr.at(i))
            return true;
        else if ((int)otherStr.at(i) < (int)maxStr.at(i))
            return false;
        
        
    } // end for loop
    
    
    
    
    return false;
} // end equalCompare
////////////////////////////////////////////////////////



