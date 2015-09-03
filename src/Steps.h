// Last Modified: Wed 26 Aug 2015 05:07:53 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : Steps.h
*
*   Description : Container class for each individual iteration
*
*******************************************************************************************/

#include <string>
#include <vector>
#include "Particles.h"
#include "plane.h"

#ifndef STEPS_H
#define STEPS_H 

class Steps
{
private :
    Particles particles_;		// Information about the particles
    std::string fname_;			// File name
    int nit_;				// 
    int nstp_;				//
    int np_;				// Number of Particles inside the particles_
    double t_;				// Time

    /*
    * Information about planes
    * Current implementation of the class is more generic than needed in order
    * to allow for more complex analysis in the future like holed-up circle  or circles that 
    * do not cover the entire domain
    * This will eventually be pushed all into a different class maybe?
    */
    plane plane_;

public :
    Steps();
    ~Steps();
    void setPath(std::string fname);
    void setNumber(int);			// Set the index of the step
    void setTime(double);			// Set the value of the time using the time step number and dt
    void setPlane(plane);			// Set the plane for plane analysis 
    void print();				// Print the entire content of the class
    void load();				// Load the corresponding data file
    void giveParticlesToPlane();		// Give a copy of the particle pointers to the planes
    void planeAnalysis();			// Do the plane analysis
    void writePlane(std::string, std::string);

    // Accessors
    int getIter();
    int getStep();
    int getNumberParticles();

    int*     getId();
    double** getXArray();
    double** getVArray();
    double** getFArray();
    double** getUArray();

    std::vector<int>	getIds();
};
#endif
