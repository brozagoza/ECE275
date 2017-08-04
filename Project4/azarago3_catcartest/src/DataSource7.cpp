#include "DataSource.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

// constructor
DataSource::DataSource( std::string filecontents )
: _filecontentsstream(filecontents)
{
    this->_filecontents = filecontents;
}

DataSource::~DataSource()
{
    // does nothing
}

// returns false if execution should stop
// due to inability to open file, or else
// if when validating returns false
bool DataSource::processFile()
{
    bool result=true;
    return result;
}

// returns false if any data are invalid
// should only be called after data are sorted
bool DataSource::validate()
{
    bool result = true;
    
    return result;
}

// reads data in from the file
bool DataSource::readData()
{
    bool result = true;

    return result;
}

// performs quick sort on the list
void DataSource::sort()
{
    return;
}

// returns ye olde vector straightaway
std::vector<Input> DataSource::getInputs()
{
    return this->_inputs;
}