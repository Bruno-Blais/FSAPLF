// Last Modified: Wed 14 Jan 2015 11:42:50 AM EST
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
#include <cmath>

using namespace std;

void terminalInit()
{
    cout << endl << endl;
    cout << "****************************************************************************" << endl;
    //cout << "    ______ _____  ___  ______ _      _____"<<endl 
    //     << "    |  ___/  ___|/ _ \\ | ___ \\ |    |  ___|"<<endl
    //     << "    | |_  \ `--./  /_\\ \\| |_/ / |    | |_    "<<endl
    //     << "    |  _|  `--. \\  _  ||  __/| |    |  _|  "<<endl
    //     << "    | |   /\\__/ / | | || |   | |____| |    "<<endl
    //     << "    \\_|   \\____/\\_| |_/\\_|   \\_____/\\_|   "<<endl;
    //cout << "*                                                                          *" << endl;
    cout << "* FSAPLF                                                                   *" << endl;
    cout << "* Framework for the Statistical Analysis of Particle-Laden Flows           *" << endl;
    cout << "* Version 0.3						                   *" << endl;
    cout << "* Created by Bruno Blais				                   *" << endl;
    cout << "****************************************************************************" << endl;
    cout << endl;
}

void terminalLoadBarInit()
{
    cout << endl;
    cout <<"Progress Bar:"<< endl;
}

void terminalClose()
{
    cout << endl << endl;
    cout << "****************************************************************************" << endl;
    cout << "* FSAPLF has exited normally                                               *" << endl;
    cout << "****************************************************************************" << endl;
    cout << endl;
}


void terminalLoadBar(unsigned int x, unsigned int n, unsigned int w)
{
    if ( (x != n) && (x % (n/100+1) != 0) ) return;
 
    float    ratio=  x/(float)n;
    unsigned int    c=  ratio * w;
 
    cout << setw(3) << (int)(ratio*100) << "% [";
    for (unsigned int x=0; x<c; x++) cout << "=";
    for (unsigned int x=c; x<w; x++) cout << " ";
    cout << "]\r" << flush;
}
