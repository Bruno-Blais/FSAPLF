// Last Modified: Thu 12 Jun 2014 03:21:24 PM EDT
/*******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : terminal.cpp
*
*   Description : Routines for interaction with the terminal in fsaplf
*
********************************************************************************************/

/*******************
*  GENERAL INCLUDES
********************/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

void terminalInit()
{
    cout << endl << endl;
    cout << "******************************************************************" << endl;
    cout << "* FSAPLF                                                         *" << endl;
    cout << "* Framework for the Statistical Analysis of Particle-Laden Flows *" << endl;
    cout << "* Version 0.2						         *" << endl;
    cout << "* Created by Bruno Blais				         *" << endl;
    cout << "******************************************************************" << endl;
    cout << endl;
}


void terminalClose()
{
    cout << endl << endl;
    cout << "******************************************************************" << endl;
    cout << "* FSAPLF has exited normally                                     *" << endl;
    cout << "******************************************************************" << endl;
    cout << endl;
}
