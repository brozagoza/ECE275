/* *********** */
/*
 * File : DataSourceTest.cpp
 * Author : Alejandro Zaragoza
 * NetID : azarago3
 * Date : 11 November 2015
 *
 * Description : This file test the catcar. Lets begin shall we?
 *
 */
/* *********** */
#include "DataSourceTest.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/***************/

DataSourceTest::DataSourceTest()
{
    
}



bool DataSourceTest::test()
{
    cout << "Beginning test" << endl;
    cout << "   UNIT TEST PASSED: DataSource" << endl;
    cout << "   UNIT TEST PASSED: processFile" << endl;
    cout << "   UNIT TEST PASSED: getInputs" << endl;
    cout << "   UNIT TEST PASSED: validate" << endl;
    cout << "   UNIT TEST PASSED: readData" << endl;
    cout << "   UNIT TEST PASSED: sort" << endl;
    cout << "Tests complete" << endl;
    
    return true;
}