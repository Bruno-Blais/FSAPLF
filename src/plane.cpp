// Last Modified: Fri 20 Jun 2014 09:20:05 AM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : particles.cpp
*
*   Description :   Manipulation of the information concerning the particle at a single
*		    iteration
*
*******************************************************************************************/


//*******************
//  GENERAL INCLUDES
//*******************
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

/********************
* HEADER INCLUDES
********************/
#include "plane.h"

#define PI 3.14159265359

plane::plane()
{
    np_=0;
    x_=NULL;
    r_=NULL;
}

plane::~plane()
{
}

void plane::setParticles(double** x, double* r)
{
    x_=x;
    r_=r;
}

void plane::print()
{
}

