#ifndef DATASOURCE_H
#define DATASOURCE_H

/*************/
/*
 * File: DataSource.h
 * Author: Your Name
 * NetID: Your NetID
 * Date:
 *
 * Description: (enter your description of what this file does).
 */

/* Note: comments in this file thusfar are insufficient for
 a perfect grade in comments */

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Input.h"

class DataSource
{
public:
    // constructor uses string instead of opening the file
    DataSource( std::string filecontents );
    
    // destructor does nothing
    ~DataSource( );
    
    // reads in the data ,
    // calls sort , and then
    // validates the data
    // ...
    // returns false if execution should stop
    // due to inability to read file, or else
    // if when validating returns false
    bool processFile ();
    
    // gets a copy of the inputs
    std::vector<Input> getInputs( );
    
private:
    std::vector<Input> _inputs;
    
    // the values from the file
    std::string _filecontents;
    
    // the contents of the file as a string
    // a streamed version of the file's contents
    std::stringstream _filecontentsstream;
public:
    // returns false if any data are invalid
    // should only be called after data are sorted
    bool validate ();
    
    // reads data in from the file. returns false if
    // unable to read data from the file at all, or if
    // any lines fail to parse correctly
    bool readData ();
    
    // performs quick sort on the list
    void sort ();
    
    // permits constructor testing; does not need to be tested
    std::string getFileContents() const { return _filecontents; }
};

#endif // DATASOURCE_H
