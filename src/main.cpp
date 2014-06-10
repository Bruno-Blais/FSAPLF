// Last Modified: Tue 10 Jun 2014 12:18:00 PM EDT
/*******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : main.cpp
*
*   Description : Main file for FSAPLF code
*
********************************************************************************************/

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
#include "options.h"
#include "particles.h"
#include "terminal.h"


using namespace std;

int main(int argc, char* argv[])
{
    //Declarations
    options opt;



    //Beggining of code
    
    terminalInit();

    opt.setMode(argc,argv);



    return 0; 

}
