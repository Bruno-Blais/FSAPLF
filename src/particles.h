// Last Modified: Tue 10 Jun 2014 11:43:09 AM EDT
// Last Modified: Tue 10 Jun 2014 11:43:09 AM EDT
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
	int n_;	    // Number of particles
	int* ids_;	    // Identification of the particles
	double** v_;    // Velocity vector
	double** x_;    // Positions vector

public :
    particles();
    ~particles();
    void allocate(int n);
    double* getV(int);	    // Access velocity
    double* getX(int);	    // Access position
};
#endif
