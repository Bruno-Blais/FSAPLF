// Last Modified: Mon 09 Jun 2014 06:12:49 PM EDT
/**********************************************************************************************************
*
*   Framework for Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : main.cpp
*
*   Description : Main file for FSAPLF code
*
************************************************************************************************************/

/*******************
*  GENERAL INCLUDES
********************/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>



/********************
* HEADER INCLUDES
********************/
#include "library.h"


using namespace std;

int main()
{

    lib testMaking;

    testMaking.test=1;

    cout << "Is it working correctly? " << endl;

    testMaking.testFunc();

    return 0; 
}
