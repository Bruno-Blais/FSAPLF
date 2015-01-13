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
*   Plane types :
*	1- Square
*	2- Circle
*	3- Rectangle
*	4- Radial profiles
*
*
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
    int planeType_;			// Plane type
    int planeAxis_;			// Plane axis 
    int planeNumber_;			// Number of surfaces in a analysis
    std::vector<double> dimensions_;	// Dimensions
    std::vector<double> length_;	// Intervals to cover
    int	np_;				// Number of particles - allows to loop over the arrays
    double*  r_;			// radiuses
    double** x_;			// Positions vector
    double* pos_;			// Position on the axis that the plane is calculated
    double* voidfraction_;		// Fraction of fluid on the plane

public :
    plane();
    ~plane();

    void set(int, int, int);			    // set the plane mode
    void setDimensions(double);			    // Sets the dimensions of the plane
    void setDimensions(double, double);		 
    void setLength(double, double);		    // Sets the interval over which the analysis takes place (bottom, top, etc)
    void setIter(int);				    // Set the iteration number
    void setNumber(int);			    // Set the number of particles on which the analysis is carried out
    void setParticles(double*, double**);	    // Allocate the required memory for the particles array

    void print();				    // Print content of the class
    void analyse();				    // Carry the analysis
    double planeVoidFraction(int,double);	    // Calculate the void fraction on a simple plane of constant normal
						    // along an axis
    void write(std::string, std::string, int);	    // Write the results to a file

    //Accessors functions
    int getType();
    int getAxis();
    int getNumber();
};
#endif
