// Last Modified: Thu 12 Jun 2014 11:22:42 AM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : steps.h
*
*   Description : Container class for each individual iteration
*
*******************************************************************************************/

#include <string>
#include "particles.h"

#ifndef STEPS_H
#define STEPS_H 

class steps
{
private :
    particles particles_;		// Informatio about the particles
    std::string fname_;			// File name
    int nit_;				// Iteration number
    int nstp_;				// Step number
    int np_;				// Number of particles inside the particles_
    double t_;				// Time

public :
    steps();
    void setPath(std::string fname);
    void setNumber(int);		// Set the index of the step
    void print();			// Print the entire content of the class
    void load();			// Load the corresponding data file
};
#endif
