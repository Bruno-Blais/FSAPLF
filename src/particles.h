// Last Modified: Mon 09 Jun 2014 06:43:49 PM EDT
/**********************************************************************************************************
*
*   Framework for Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : particles.h
*
*   Description : Container class for all the particles of a file
*
************************************************************************************************************/

#ifndef LIBRARY_H
#define LIBRARY_H 

#include <vector>

class particles
{
    public :
	particles();
	~particles();

    private :
    int* id;	    // Identification of the particles
    double* v[];    // Velocity vector
    double* x[];
};

double* getV(int);	    // Access velocity
double* getX(int);	    // Access position

#endif
