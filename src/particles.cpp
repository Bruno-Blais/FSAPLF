// Last Modified: Thu 12 Jun 2014 11:32:35 AM EDT
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
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

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
	delete f_[i];
    }
    delete x_;
    delete v_;
    delete f_;
    delete ids_;
    delete r_;
}

void particles::allocate(int n)
{
    //Allocate local memory for the information about the particles
    np_ = n;
    
    ids_ = new int[n];
    r_ = new double[n];
    v_ = new double*[n];
    x_ = new double*[n];
    f_ = new double*[n];

    for (int i = 0 ; i < np_ ; i++)
    {
	v_[i] = new double[4];
	x_[i] = new double[4];
	f_[i] = new double[4];
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

void particles::load(std::ifstream *fic_in)
{
    //Declaration
    std::string buffer;
    std::vector<std::string> tokens;

    //Get the lines
    std::getline((*fic_in),buffer);

    //Parse the header of the files
    boost::algorithm::split(tokens, buffer, boost::algorithm::is_any_of(" "));	

    // Depending on the header type, finally parse the data into the particles_ structure
}

void particles::print()
{


}
