// Last Modified: Thu 12 Jun 2014 01:38:38 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : particles.cpp
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
#include "steps.h"

steps::steps()
{
    fname_="INVALID";
    nit_=0;
    t_=0.;
    nstp_=0.;
    np_=0.;
}

void steps::setPath(std::string fname)
{
    fname_=fname;
}

void steps::setNumber(int i)
{
    nstp_=i;
}

void steps::print()
{
    std::cout << "\n------------------------------\nInformation about file " 
    << nstp_ <<  "\n------------------------------" << std::endl;
    std::cout << "Path : " << fname_ << std::endl;
    std::cout << "Local number of the iteration : " << nit_ << std::endl;
    std::cout << "Local time : " << t_ << std::endl;
    std::cout << "Local number of particles : " << np_ << std::endl;

    // Add the particle print here
    // particles_.prin
}

void steps::load()
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
	std::cout << std::endl << "Opening file : " << fname_ << std::endl;

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
