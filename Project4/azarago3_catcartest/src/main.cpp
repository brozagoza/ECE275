#include "DataSource.h"
#include "DataSourceTest.h"
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char *argv[])
{
    
    // If any arguments are passed a usage statement will execute
    if (argc > 1)
    {
        string str(argv[0]);
        str = str.substr( str.length()-11, str.length());
        cout << "Usage: " << str << endl;
        return -1;
    }
    // end if statement (usage statement)
    
    
    
    
    
    // below is what was done for the alpha. super basic stuff my friends
    DataSourceTest temp;
    temp.test();
    // swag masters all aboard the swag train hahaha
}