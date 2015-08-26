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

/**********************
*  GENERAL INCLUDES
**********************/
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <omp.h>

/*********************
* HEADER INCLUDES
*********************/
#include "options.h"
#include "steps.h"
#include "particles.h"
#include "Averaging.h"
#include "terminal.h"
#include "trajectories.h"
#include "MixingIndex.h"
#include "Pca.h"

using namespace std;

int main(int argc, char* argv[])
{
     // Initilization of the code
    terminalInit();

    // Declarations and constructors
    steps* stp;
    trajectories trj;

    //Options constructor parses the input from the terminal ---> this is to be deprecated 
    options opt(argc, argv);

    // Calculate number of files in the folder
    opt.getFilesIdentification();

    // Constructors that use the new API
    //-----------------------------------------
    MixingIndex     mixingIndex(argc, argv, opt.getNumberOfFiles());
    Pca             pca(argc,argv);
    Averaging       avg(argc, argv, opt.getNumberOfFiles());
    
    // Allocate the steps
    stp = new steps[opt.getNumberOfFiles()];
  
    // Transfer information to each individual step
    opt.setSteps(stp);

    // Begin progress bar
    terminalLoadBarInit();
    
    for (int i=0 ; i<opt.getNumberOfFiles(); i++)
    {
	    stp[i].load();
	   // std::cout << "File iteration :\t"<<stp[i].getIter()<<std::endl;
	   
	    if (opt.getTrajectories() && i==0)
	    {
		trj.allocate(opt.getTrajectoriesType(), opt.getNumberOfFiles(),stp[i].getNumberParticles(),stp[i].getIds());
	    }
	   
            if (opt.getAveraging())
            {
                avg.setIter(i,stp[i].getIter());
                avg.particles(stp[i].getNumberParticles(),stp[i].getXArray(),stp[i].getVArray(),stp[i].getFArray(),stp[i].getUArray());
	    }

	    if (opt.getPlaneOn())
	    {
		//Copy the plane class to the local steps
		stp[i].setPlane(opt.getPlane());
		stp[i].giveParticlesToPlane();
		stp[i].planeAnalysis();
		stp[i].writePlane(opt.getOutputPath(), opt.getLabel());
	    }

	    if (opt.getTrajectories())
	    {
		trj.setStep(i, stp[i].getNumberParticles(),stp[i].getIds(),stp[i].getXArray());
	    }

            if (opt.getMixingIndex())
            {
                mixingIndex.manage(stp[i].getIter(),stp[i].getNumberParticles(),stp[i].getId(),stp[i].getXArray());
            }
            
            if (opt.getPca())
            {
                pca.manage(stp[i].getIter(),stp[i].getNumberParticles(),stp[i].getId(),stp[i].getXArray());
            }

           // Memory flushing
            if (i%opt.getBatchFreq()==0 && i>opt.getBatchFreq())
            {
                //Flush the batchFreq_ previous iterations
                for (int j =(i-2*opt.getBatchFreq()) ; j<(i-opt.getBatchFreq())  ; j++)
                {
                   stp[j].~steps(); 
                }
            }

	    // Write progress bar
	   terminalLoadBar(i,opt.getNumberOfFiles(),50);
    }

    // Output of global results

    if (opt.getAveraging()) avg.writeFile(opt.getOutputPath(), opt.getLabel());
    if (opt.getMixingIndex()) mixingIndex.write(opt.getOutputPath(), opt.getLabel());

    terminalClose();
    return 0; 
}


