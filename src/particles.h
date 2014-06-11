// Last Modified: Wed 11 Jun 2014 02:43:13 PM EDT
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

public :
    particles();
    ~particles();
    void allocate(int n);
    double* getV(int);	    // Access velocity
    double* getX(int);	    // Access position
};
#endif
