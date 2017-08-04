/* *********** */
/*
 * File : DataSourceTest.cpp
 * Author : Alejandro Zaragoza
 * NetID : azarago3
 * Date : 11 November 2015
 *
 * Description : This file test the catcar using various tests and cases that should return the expected values
 *               indicated below inside the methods themselves. If something does not add up, then an individual
 *               test may fail.
 *
 */
/* *********** */
#include "DataSourceTest.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
/***************/


/*=======================================================================================================================
 |  Constructor DataSourceTest
 |
 |  Constructor that initializes a string with a "file." This file is used later when initialzing a test for DataSource.
 |
 |
 =======================================================================================================================*/
DataSourceTest::DataSourceTest()
{
    // testStr is the first 11 inputs of test file 3
    testStr = "0 1 0\n0.4 1 0.03819\n0.1 1 0.009549\n0.2 1 0.0191\n0.3 1 0.02865\n";
    
} // end constructor


/*=======================================================================================================================
 |  Method test()
 |
 |  This method calls the various tests to make sure that it passes the various tests.
 |
 |
 =======================================================================================================================*/
bool DataSourceTest::test()
{

    
    // prints at beginning
    cout << "Beginning tests" << endl;
    
    // DataSource Tests
    if (constructorTest())
        cout << "   UNIT TEST PASSED: DataSource" << endl;
    else
        cout << "   UNIT TEST FAILED: DataSource" << endl;
    
    // processFile Tests
    if (processFileTest())
        cout << "   UNIT TEST PASSED: processFile" << endl;
    else
        cout << "   UNIT TEST FAILED: processFile" << endl;
    
    
    // getInputs test
    if (getInputsTest())
        cout << "   UNIT TEST PASSED: getInputs" << endl;
    else
        cout << "   UNIT TEST FAILED: getInputs" << endl;
    
    //Validate tests
    if (validateTest())
        cout << "   UNIT TEST PASSED: validate" << endl;
    else
        cout << "   UNIT TEST FAILED: validate" << endl;
    
    //readData tests
    if (readDataTest())
        cout << "   UNIT TEST PASSED: readData" << endl;
    else
        cout << "   UNIT TEST FAILED: readData" << endl;
    
    //sort tests
    if (sortTest())
        cout << "   UNIT TEST PASSED: sort" << endl;
    else
        cout << "   UNIT TEST FAILED: sort" << endl;
    
    
    //prints at the end
    cout << "Tests complete" << endl;
    
    return true;
}

/*=======================================================================================================================
 |  Method constructorTest()
 |
 |  This method tests the constructor and makes sure that the file content that was passed in matches the string provided
 |  exactly.
 |
 |
 =======================================================================================================================*/
bool DataSourceTest::constructorTest()
{
    DataSource tester(testStr);
    
    if (testStr.compare(tester.getFileContents()) == 0)         // strings must match to pass the test
        return true;
    else
        return false;
    
} // end constructorTest



/*=======================================================================================================================
 |  Method processFileTest()
 |
 |  This method tests the constructor and makes sure that the file content that was passed in matches the string provided
 |  exactly.
 |
 |
 =======================================================================================================================*/
bool DataSourceTest::processFileTest()
{
    DataSource tester(testStr);         // test case that must pass
    //DataSource tester2("pofdsafds");    // terrible test case that must fail
    
    if (!tester.processFile())
        return false;
    
    //if (tester2.processFile())
        //return false;
    
    return true; // all tests pass so it's all good my friends :)
} // end processFileTest


/*=======================================================================================================================
 |  Method getInputsTest()
 |
 |  Tests that the inputs returned from the DataSource.cpp match expectations as a vector.
 |
 |
 =======================================================================================================================*/
bool DataSourceTest::getInputsTest()
{
    unsigned int i = 0;
    
    DataSource tester(testStr);
    tester.readData();
    
    vector<Input> testerIn = tester.getInputs();    // the vector being tested against
    vector<Input> compareTo;    // the vector hard coded to test with
    
    Input tempInput;
    
    tempInput.setTimeStamp(0);
    tempInput.setTireAngleRate(0);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    tempInput.setTimeStamp(0.4);
    tempInput.setTireAngleRate(0.03819);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    tempInput.setTimeStamp(0.1);
    tempInput.setTireAngleRate(0.009549);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    tempInput.setTimeStamp(0.2);
    tempInput.setTireAngleRate(0.0191);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    tempInput.setTimeStamp(0.3);
    tempInput.setTireAngleRate(0.02865);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    
    if (testerIn.size() != compareTo.size()) // different size must return false
        return false;
    
    for (i = 0; i < testerIn.size(); i++) // different values must return false
    {
        if (testerIn.at(i).getTimeStamp() != compareTo.at(i).getTimeStamp())
            return false;
        
        if (testerIn.at(i).getTireAngleRate() != compareTo.at(i).getTireAngleRate())
            return false;
        
        if (testerIn.at(i).getVelocity() != compareTo.at(i).getVelocity())
            return false;
    
    } // end for loop
    
    
    
    return true;
} // end getInputsTest


/*=======================================================================================================================
 |  Method validateTest
 |
 |  This method tests that validate test should return false and true when expected.
 |
 |
 =======================================================================================================================*/
bool DataSourceTest::validateTest()
{
    DataSource tester(testStr);
    tester.readData();
    tester.sort();
    
    if (!tester.validate())
        return false;
    
    DataSource tester2(testStr);
    tester2.readData();
    
    if (tester2.validate())
        return false;
    
    return true;
} // end validateTest


/*=======================================================================================================================
 |  Method readDataTest()
 |
 |  This method should return true or false depending if the data was read in correctly.
 |
 |
 =======================================================================================================================*/
bool DataSourceTest::readDataTest()
{
    DataSource tester(testStr);
    
    if (!tester.readData())
        return false;
    
    DataSource tester2("t4ewg");
    
    if (tester2.readData())
        return false;
    
    return true;

} // end readDataTest



/*=======================================================================================================================
 |  Method sortTest()
 |
 |  This method tests that the sort method works correctly, sorting the inputs from the file.
 |
 |
 =======================================================================================================================*/
bool DataSourceTest::sortTest()
{
    unsigned int i = 0;
    
    DataSource tester(testStr);
    tester.readData();
    tester.sort();
    
    vector<Input> testerIn = tester.getInputs(); // the vector being tested against
    vector<Input> compareTo;    // the hard coded vector
    
    Input tempInput;    // holds the input temporarily
    
    tempInput.setTimeStamp(0);
    tempInput.setTireAngleRate(0);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    tempInput.setTimeStamp(0.1);
    tempInput.setTireAngleRate(0.009549);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    tempInput.setTimeStamp(0.2);
    tempInput.setTireAngleRate(0.0191);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    tempInput.setTimeStamp(0.3);
    tempInput.setTireAngleRate(0.02865);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    tempInput.setTimeStamp(0.4);
    tempInput.setTireAngleRate(0.03819);
    tempInput.setVelocity(1);
    compareTo.push_back(tempInput);
    
    
    if (testerIn.size() != compareTo.size())
        return false;
    
    
    for (i = 0; i < testerIn.size(); i++)
    {
        if (testerIn.at(i).getTimeStamp() != compareTo.at(i).getTimeStamp())
            return false;
        
        if (testerIn.at(i).getTireAngleRate() != compareTo.at(i).getTireAngleRate())
            return false;
        
        if (testerIn.at(i).getVelocity() != compareTo.at(i).getVelocity())
            return false;
        
    } // end for loop
    
    
    
    return true;
} // end sortTest