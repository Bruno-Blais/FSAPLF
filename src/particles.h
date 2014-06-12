// Last Modified: Thu 12 Jun 2014 11:28:25 AM EDT
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

public :
    particles();
    ~particles();
    void allocate(int n);
    double* getV(int);	    // Access velocity
    double* getX(int);	    // Access position
    void load(std::ifstream * );
    void print();	    // Print content of the class
};
#endif
