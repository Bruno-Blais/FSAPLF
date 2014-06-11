// Last Modified: Wed 11 Jun 2014 03:36:49 PM EDT
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
#include "steps.h"
#include "particles.h"
#include "terminal.h"


using namespace std;

int main(int argc, char* argv[])
{
    // Declarations
    options opt;
    steps* stp;

   

    // Initilization of the code
    terminalInit();
    
    // Acquire options from terminal arguments
    opt.setMode(argc,argv);

    // Calculate number of files in the folder
    opt.getFilesIdentification();




    return 0; 

}
