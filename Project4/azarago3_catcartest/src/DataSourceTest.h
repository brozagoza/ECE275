/* *********** */
/*
 * File : DataSourceTest.h
 * Author : Alejandro Zaragoza
 * NetID : azarago3
 * Date : 11 November 2015
 *
 * Description : Simply the header file for the DataSourceTest.cpp file that is included. For more information
 *               refer to the .cpp file.
 *
 */
/* *********** */
#include <iostream>
#include <string>



#include "DataSource.h"

using namespace std;
/* *********** */


/*
 CLASS THAT DOES THE TESTING FOR DATASOURCE. LETS GET JIGGIDY.
 */
class DataSourceTest
{
public:
    DataSourceTest();   // constructor
    
    bool test();        // Tests everything. Called by main.
    
private:
    
    bool constructorTest(); // DataSource test
    
    bool processFileTest(); // processFile test. Reads in data, calls sort, and then validate data.
    
    bool getInputsTest();   // getInputs test. Test fails if the returned vector does not match
                            // expectations.
    
    bool validateTest();    // validate test
    
    bool readDataTest();    // readData test
    
    bool sortTest();        // sort test
    
    string testStr;         // string used for testing
};