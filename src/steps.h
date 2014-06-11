// Last Modified: Wed 11 Jun 2014 02:43:55 PM EDT
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


#include <string>
#include "particles.h"

#ifndef STEPS_H
#define STEPS_H 

class steps
{
private :
    particles particle_;
    std::string fname_;	    //File name
    int nit_;		    //Iteration number
    double t;		    //Time

public :
    steps();
    ~steps();
};
#endif
