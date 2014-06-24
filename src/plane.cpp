// Last Modified: Tue 24 Jun 2014 04:36:18 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : plane.cpp
*
*   Description :   Container class for the plane averaging functions and data
*
*******************************************************************************************/


//*******************
//  GENERAL INCLUDES
//*******************
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

/********************
* HEADER INCLUDES
********************/
#include "plane.h"
#include "writing.h"

#define PI 3.14159265359
#define WIDTH 12
#define PRES 7

plane::plane() : dimensions_(6), length_(6)
{
    planeNumber_=0;
    x_=NULL;
    r_=NULL;
    planeType_=0;
    planeAxis_=0;    
    planeNumber_=0;
}

plane::~plane()
{
}

void plane::set(int planeType, int planeAxis, int planeNumber)
{
    x_=NULL;
    r_=NULL;
    planeType_ = planeType;
    planeAxis_ = planeAxis;
    planeNumber_ = planeNumber;
    voidfraction_ = new double[planeNumber_];
    pos_ = new double[planeNumber_];
}

void plane::setParticles(double* r, double** x)
{
    r_=r;
    x_=x;
}

void plane::setDimensions(double l)
{
    dimensions_[0]=l;
}

void plane::setLength(double bottom, double top)
{
    length_[0]=bottom;
    length_[1]=top;
}

void plane::setNumber(int np)
{
    np_=np;
}

void plane::print()
{
}

void plane::analyse()
{
    double area;	    // Area of the plane
    double areaParticles;   // Area occupied by the particles
    double h;		    // Local position alongside the axis
    double dh;		    // Increment in the position

    if (planeType_ < 3)
    {
	//Case of the square
	if ( planeType_ == 1)
	    area = dimensions_[0] * dimensions_[0];
	
	//Case of the circle
	if ( planeType_ == 2) 
	    area = PI * dimensions_[0] * dimensions_[0];

	//Case of a rectangle
	if ( planeType_ == 3)
	    area = dimensions_[0] * dimensions_[1];

	dh = (length_[1]-length_[0]) / (planeNumber_-1);
	h = length_[0];
	for(int i=0 ; i < planeNumber_ ; i++)
	{
	   areaParticles=planeVoidFraction(planeAxis_,h);
	   voidfraction_[i] = 1. - areaParticles / area;
	   pos_[i] = h;
	   h +=dh;
	}
    }
}

double plane::planeVoidFraction(int axis, double h)
{
    //Calculate the void fraction on a given plane
    // axis is the vector normal to the plane, it can either be : 0-x 1-y 2-z
    // h is the position on axis of the plane
    // function returns the Area of sphere on that plane
    double x=0;
    double r=0;
    double r2s=0;
    double area=0;

    for (int i=0 ; i< np_ ; i++)
    {
	x = x_[i][axis];
	r = r_[i];
	if (((( x+r > h ) && ( x-r > h)) || ((x+r<h) && (x-r<h))) == false)
	{
	    //Particle crosses the plane
	    r2s = r*r-(x-h)*(x-h);
	    area += PI *r2s;
	}
    }

    return area;
}

void plane::write(std::string path, std::string label, int nit)
{
    std::string filename = path+"/"+label+"_plane_"+writingIntToString(nit);
    std::ofstream ficOut(filename.c_str());
    for (int i=0 ; i<planeNumber_ ; i++)
    {
	ficOut	<< std::setw(WIDTH) << std::setprecision(PRES) << pos_[i] << " "  
		<< std::setw(WIDTH) << std::setprecision(PRES) << voidfraction_[i] << " "
		<< std::endl;
    }
    ficOut.close();
}

//Accesssors
int plane::getType(){return planeType_;}
int plane::getAxis(){return planeAxis_;}
int plane::getNumber(){return planeNumber_;}
