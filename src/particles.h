// Last Modified: Fri 13 Jun 2014 11:12:40 AM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : particles.h
*
*   Description : Container class for all the particles of a file
*
*******************************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

#ifndef PARTICLES_H
#define PARTICLES_H 

class particles
{
private :
    int np_;	            // Number of particles
    int* ids_;		    // Identification of the particles
    double** v_;	    // Velocity vector
    double** x_;	    // Positions vector
    double** f_;	    // Fluid-Solid interaction forces (fdrag)
    double** u_;	    // Velocity of the fluid
    double*  r_;	    // radiuses

//Average properties
   std::vector<double> vAvg_; 
   std::vector<double> xAvg_;
   std::vector<double> fAvg_;
   std::vector<double> uAvg_;

public :
    particles();
    ~particles();
    void allocate(int n);
    double* getV(int);			// Access velocity
    double* getX(int);			// Access position
    void load(std::ifstream*);		// Load particle information
    void print();			// Print content of the class
    void calcAverage();			// Calculate the average of each variables
    void calcNorm();			// Calculate the norm of each variables
    std::vector<double> getAverageV();	// Return average velocity
    std::vector<double> getAverageX();	// Return average position
    std::vector<double> getAverageF();	// Return average force
    std::vector<double> getAverageU();	// Return average fluid velocity
};
#endif
