// Last Modified: Fri 13 Jun 2014 10:51:26 AM EDT
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
#include "options.h"
#include "steps.h"
#include "particles.h"
#include "averaging.h"
#include "terminal.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Declarations
    steps* stp;
    averaging avg;

    // Initilization of the code
    terminalInit();

    //Options constructor parses the input from the terminal
    options opt(argc, argv);

    // Calculate number of files in the folder
    opt.getFilesIdentification();

    // Allocate the steps
    stp = new steps[opt.getNumberOfFiles()];
   
    // If averaging if on, allocate that up
    if(opt.getAveraging()) avg.allocate(opt.getNumberOfFiles());


    // Transfer information to each individual step
    opt.setSteps(stp);

    for (int i=0 ; i<opt.getNumberOfFiles(); i++)
    {
	    stp[i].load();

	    if (opt.getAveraging())
		    stp[i].average();
	    stp[i].print();
    }

    terminalClose();
    return 0; 
}
