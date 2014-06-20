// Last Modified: Thu 19 Jun 2014 05:10:59 PM EDT
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
#include <vector>
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

    /*
    * Information about planes
    * Current implementation of the class is more generic than needed in order
    * to allow for more complex analysis in the future like holed-up circle  or circles that 
    * do not cover the entire domain
    * This will eventually me pushed all into a different class maybe?
    */

    int nPlane_;			// Number of planes
    int planeType_;			// Type of planes (1- square 2-circles)
    std::vector<double> dimensions_;	// Tools to calculate the size of the plane
    std::vector<double> length_;	// Beggining and end in all axes
    double* voidfraction_;		// fraction of solid particles
    

public :
    steps();
    ~steps();
    void setPath(std::string fname);
    void setNumber(int);		// Set the index of the step
    void print();			// Print the entire content of the class
    void load();			// Load the corresponding data file
    void average();			// Averaging function

    // Accessors
    std::vector<double> getAverageV();
    std::vector<double> getAverageX();
    std::vector<double> getAverageF();
    std::vector<double> getAverageU();
};
#endif
