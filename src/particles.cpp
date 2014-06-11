// Last Modified: Wed 11 Jun 2014 08:49:26 AM EDT
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


/*******************
*  GENERAL INCLUDES
********************/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

/********************
* HEADER INCLUDES
********************/
#include "particles.h"

particles::particles()
{
    np_ = 0;
    ids_ = NULL;
    v_ = NULL;
    x_ = NULL;
}

particles::~particles()
{
    for (int i = 0 ; i< np_ ; i++)
    {
	delete x_[i];
	delete v_[i];
    }
    delete x_;
    delete v_;
    delete ids_;
}

void particles::allocate(int n)
{
    //Allocate local memory for the information about the particles
    np_ = n;
    
    ids_ = new int[n];
    v_ = new double*[n];
    x_ = new double*[n];

    for (int i = 0 ; i < np_ ; i++)
    {
	v_[i] = new double[3];
	x_[i] = new double[3];
    }
}

double* particles::getV(int id)
{
    //Returns the pointer to the velocity of a particle using it's id
    return v_[id]; 
}

double* particles::getX(int id)
{
    //Returnes pointer to position
    return x_[id];
}
