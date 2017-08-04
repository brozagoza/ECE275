#include "DataSource.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

// for sort
#include <algorithm>

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
    
    result = readData();
    if (result)
    {
        // next step: sort the data
        sort();
        
        // next step: validate the data
        result = validate();
        
    }
    
    return result;
}

// returns false if any data are invalid
// should only be called after data are sorted
bool DataSource::validate()
{
    bool result = true;
    // iterate over all the data values in order
    // to ensure they are correct
    for (unsigned int i=0; i<_inputs.size() && result; i++)
    {
        // The first element of the sorted list must be at exactly time 0.
        if (i == 0)
        {
            if (_inputs[i].getTimeStamp() != 0)
            {
                // invalid!
                result = false;
            }
        }
        else
        {
            // Duration between sorted input objects must be between [5,205]ms.
            if ( (_inputs[i].getTimeStamp() - _inputs[i-1].getTimeStamp() > 0.2) ||
                (_inputs[i].getTimeStamp() - _inputs[i-1].getTimeStamp() < 0.005 ) )
            {
                // invalid!
                result = false;
            }
            // Commanded velocity must be between [0, 30] m/s;
            else if( _inputs[i].getVelocity() < 0 ||
                    _inputs[i].getVelocity() > 30)
            {
                // invalid!
                result = false;
            }
            // Commanded tire angle rate must be between [−0.5236, 0.5236] 1/s (+/- pi/6 rad/sec);
            else if( _inputs[i].getTireAngleRate() < MIN_TIRE_ANGLE_RATE ||
                    _inputs[i].getTireAngleRate() > MAX_TIRE_ANGLE_RATE )
            {
                // invalid!
                result = false;
            }
            // Time values must be non-negative
            else if( _inputs[i].getTimeStamp() < 0 )
            {
                // invalid!
                result = false;
            }
        }
    }
    
    return result;
}

// reads data in from the file
bool DataSource::readData()
{
    bool result = true;
    // u1 = velocity
    // u2 = tire angle rate
    // ts = sample time
    double u1,u2,ts=0.0f;
    
    // open up the file for reading in the constructor
    if (!_filecontentsstream.good())
    {
        // uh oh, something's wrong
        // Unable to open streamstring; aborting
        result = false;
    }
    else
    {
        
        while (_filecontentsstream.good())
        {
            // let's read it, line by line
            _filecontentsstream >> ts;
            _filecontentsstream >> u1;
            _filecontentsstream >> u2;
            if (_filecontentsstream.good())
            {
                Input input(u1,u2,ts);
                _inputs.push_back(input);
            }
        }
        
        if( !_filecontentsstream.eof())
        {
            // uh oh, something's wrong
            // Error reading from streamstring; aborting
            result = false;
        }
    }
    

    return result;
}

// SPEED: let STL do the sorting stuff
// in order to confirm that it will work
bool compareInputs( Input a, Input b )
{
    return a.getTimeStamp() < b.getTimeStamp();
}

// performs quick sort on the list
void DataSource::sort()
{
    // NOTE: your own sorting routine should replace this one
    std::sort(_inputs.begin(), _inputs.end(), compareInputs);
}

// return the member variable
std::vector<Input> DataSource::getInputs()
{
    return this->_inputs;
}
