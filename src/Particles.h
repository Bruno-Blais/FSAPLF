// Last Modified: Wed 26 Aug 2015 04:49:04 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : Particles.h
*
*   Description : Container class for all the Particles of a file
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

class Particles
{
private :
    int np_;	            // Number of Particles
    int* ids_;		    // Identification of the Particles
    double** v_;	    // Velocity vector
    double** x_;	    // Positions vector
    double** f_;	    // Fluid-Solid interaction forces (fdrag)
    double** u_;	    // Velocity of the fluid
    double*  r_;	    // radiuses

    //Average properties
   std::vector<double> vAvg_; // Average velocity
   std::vector<double> xAvg_; // Average position
   std::vector<double> fAvg_; // Average force
   std::vector<double> uAvg_; // Average fluid velocity

public :
    Particles();
    ~Particles();
    void allocate(int n);		// Allocate the required memory for the Particles array
    void load(std::ifstream*);		// Load particle information
    void print();			// Print content of the class
    void calcNorm();			// Calculate the norm of each variables

    // Related to averaging
    void calcAverage();			// Calculate the average of each variables
    std::vector<double> calcPercentageMax(double**, int, double);
    
    // Accessors
    int getNumber();
    int* getId();
    double* getV(int);			// Access velocity
    double* getX(int);			// Access position
    double* getRArray();
    double** getXArray();
    double** getVArray();
    double** getFArray();
    double** getUArray();

    std::vector<int> getIds();

};
#endif
