// Last Modified: Thu 12 Jun 2014 04:06:17 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : averaging.cpp
*
*   Description :   Contains the averaged properties for all files
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

/********************
* HEADER INCLUDES
********************/
#include "averaging.h"

#define LARGE 9999.

averaging::averaging()
{
}

averaging::~averaging()
{
}

void averaging::allocate(int n)
{
    //Allocate local memory for the information about the averages
    
    r_ = new double[n];
    v_ = new double*[n];
    x_ = new double*[n];
    f_ = new double*[n];

    for (int i = 0 ; i < n ; i++)
    {
	v_[i] = new double[4];
	x_[i] = new double[4];
	f_[i] = new double[4];
    }

/*
    box_[0] = -LARGE;
    box_[1] = LARGE;
    box_[2] = -LARGE;
    box_[3] = LARGE;
    box_[4] = -LARGE;
    box_[5] = LARGE;
*/
}

void averaging::setV (int k, double *v)
{
    for (int i=0 ; i<4 ; i++)
    {
	v_[k][i] = v[i];
    }
}

void averaging::setX (int k, double *v)
{
    for (int i=0 ; i<4 ; i++)
    {
	x_[k][i] = v[i];
    }
}

void averaging::setF (int k, double *v)
{
    for (int i=0 ; i<4 ; i++)
    {
	f_[k][i] = v[i];
    }
}
