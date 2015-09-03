// Last Modified: Wed 26 Aug 2015 04:59:30 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : Particles.cpp
*
*   Description :   Manipulation of each time step
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
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

/********************
* HEADER INCLUDES
********************/
#include "options.h"
#include "Steps.h"
#include "plane.h"

#define verbose 0

Steps::Steps()
{
    fname_="INVALID";
    nit_=0;
    t_=0.;
    nstp_=0.;
    np_=0.;
}

Steps::~Steps()
{
}

void Steps::setPath(std::string fname)
{
    fname_=fname;
}

void Steps::setNumber(int i)
{
    nstp_=i;
}

void Steps::setPlane(plane p)
{
    plane_=p;
}

void Steps::print()
{
    std::cout << "\n------------------------------\nInformation about file " 
    << nstp_ <<  "\n------------------------------" << std::endl;
    std::cout << "Path : " << fname_ << std::endl;
    std::cout << "Local number of the iteration : " << nit_ << std::endl;
    std::cout << "Local time : " << t_ << std::endl;
    std::cout << "Local number of Particles : " << np_ << std::endl;

    // Add the particle print here
    particles_.print();
}

void Steps::load()
{
    std::ifstream fic_in; // input file identifier
    fic_in.open(fname_.c_str()); // Conversion of string to char so file may be opened
    std::string buffer;
    std::string secBuffer;

    if (fic_in.fail())
    {
	std::cout << "File : " << fname_ << " could not be opened correctly " << std::endl;
    }
    else
    {
	if(verbose) std::cout << std::endl << "Opening file : " << fname_ << std::endl;

	//Remove garbage line 1
	std::getline(fic_in,buffer);
	
	//Read timestep
	fic_in >> nit_;
	getline(fic_in,buffer); //closing the line

	std::getline(fic_in,buffer);
	fic_in >> np_;

	for (int i=0 ; i< 5 ; i++)
	{
	    std::getline(fic_in,buffer);
	}
	particles_.allocate(np_);
	particles_.load(&fic_in);
    }
}

void Steps::setTime(double dt)
{
    t_ = nit_ * dt;
}

void Steps::giveParticlesToPlane()
{
    plane_.setNumber(np_);
    plane_.setParticles(particles_.getRArray(), particles_.getXArray());
}

void Steps::planeAnalysis()
{
    plane_.analyse();
}

void Steps::writePlane(std::string path, std::string label)
{
    plane_.write(path,label, nit_);
}

//Accesors

int Steps::getIter()
{
    return nit_;
}

int Steps::getStep()
{
    return nstp_;
}

int Steps::getNumberParticles()
{
    return np_;
}

int* Steps::getId()
{
    return particles_.getId();
}

double** Steps::getXArray()
{
    return particles_.getXArray();
}

double** Steps::getVArray()
{
    return particles_.getVArray();
}

double** Steps::getFArray()
{
    return particles_.getXArray();
}

double** Steps::getUArray()
{
    return particles_.getVArray();
}

std::vector<int> Steps::getIds()
{
    return particles_.getIds();
}

