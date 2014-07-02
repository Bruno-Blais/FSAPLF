// Last Modified: Wed 02 Jul 2014 11:34:55 AM EDT
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

    // Begin progress bar
    terminalProgressInit(opt.getNumberOfFiles());

    // Parallelism will be done on this loop using openmp
    for (int i=0 ; i<opt.getNumberOfFiles(); i++)
    {
	    stp[i].load();
	    //std::cout << "File iteration :\t"<<stp[i].getIter()<<std::endl;
	    if (opt.getAveraging())
	    {
		    stp[i].average();
		    avg.setIter(i,stp[i].getIter());
		    avg.setV(i,stp[i].getAverageV());
		    avg.setX(i,stp[i].getAverageX());
		    avg.setF(i,stp[i].getAverageF());
	    }

	    if (opt.getPlaneOn())
	    {
		//Copy the plane class to the local steps
		stp[i].setPlane(opt.getPlane());
		stp[i].giveParticlesToPlane();
		stp[i].planeAnalysis();
		stp[i].writePlane(opt.getOutputPath(), opt.getLabel());
	    }
	   // stp[i].print();

	    // Write progress bar
	   terminalProgress(i,opt.getNumberOfFiles());
    }

    // Output of global results

    if (opt.getAveraging()) avg.writeFile(opt.getOutputPath(), opt.getLabel());

    terminalClose();
    return 0; 
}
