/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : plane.h
*
*   Description :   Container class for the plane averaging functions and data
*		    Plane averaging consists in calculating the voidfraction profile on surfaces
*		    Plane can be cylindrical, squares, rectangles or circles
*		    As of now, only full (circles, squares and rectangles) are implemented
*
*******************************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

#ifndef PLANE_H
#define PLANE_H 

class plane
{
private :
    int np_;	            // Number of particles
    double** x_;	    // Positions vector
    double*  r_;	    // radiuses

public :
    plane();
    ~plane();
    void setParticles(double**, double*);		// Allocate the required memory for the particles array
    void print();			// Print content of the class

    // Related to planes
    //double sectionVoidFraction(int axis, double h);
};
#endif
