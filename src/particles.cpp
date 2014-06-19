// Last Modified: Fri 13 Jun 2014 11:24:48 AM EDT
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

particles::particles() : vAvg_(4), xAvg_(4), fAvg_(4), uAvg_(4) 
{
    np_ = 0;
    ids_ = NULL;
    v_ = NULL;
    x_ = NULL;
    f_ = NULL;
    r_ = NULL;
    u_ = NULL;
}

particles::~particles()
{
    std::cout<<" Destructing particles " << std::endl;
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
    int inputType=0;

    //Declaration
    std::string buffer;
    std::vector<std::string> tokens;

    //Get the lines
    std::getline((*fic_in),buffer);

    //Parse the header of the files
    boost::algorithm::split(tokens, buffer, boost::algorithm::is_any_of(" "));	

    // Depending on the header type, finally parse the data into the particles_ structure
    if (
	tokens[2]=="id"		&&
	tokens[3]=="type"	&&
	tokens[5]=="x"		&&
	tokens[8]=="ix"		&&
	tokens[11]=="vx"	&&
	tokens[14]=="fx"	&&
	tokens[17]=="omegax"	&&
	tokens[20]=="radius"	
	) inputType=1;
    
    if (
	tokens[2]=="id"		&&
	tokens[3]=="type"	&&
	tokens[5]=="x"		&&
	tokens[8]=="vx"		&&
	tokens[11]=="fx"	&&
	tokens[14]=="radius"	
	) inputType=2;
   
    if (inputType==0) 
	std::cout << "A valid LAMMPS input type has not been detected, please correct this..." << std::endl;

    else
    {	
	if (inputType==1)
	{
	    std::cout << "Input format : " << inputType << std::endl ;
	    for(int i=0 ; i<np_ ; i++)
	    {
		(*fic_in) >> ids_[i]; 
		for (int j=0 ; j<2 ; j++) (*fic_in) >> buffer;
		for (int j=0 ; j<3 ; j++) (*fic_in) >> x_[i][j];
		for (int j=0 ; j<3 ; j++) (*fic_in) >> buffer;
	    	for (int j=0 ; j<3 ; j++) (*fic_in) >> v_[i][j];
		for (int j=0 ; j<3 ; j++) (*fic_in) >> f_[i][j];
		for (int j=0 ; j<3 ; j++) (*fic_in) >> buffer;
		(*fic_in) >> r_[i]; 
		
		//Read a line
		std::getline((*fic_in),buffer);
	    }
	}
	
	if (inputType==2)
	{
	    std::cout << "Input format : " << inputType << std::endl; 
	     for(int i=0 ; i<np_ ; i++)
	    {
		//Cast into the right variable
		(*fic_in) >> ids_[i]; 
		(*fic_in) >> buffer;
		for (int j=0 ; j<3 ; j++) (*fic_in) >> x_[i][j];
		for (int j=0 ; j<3 ; j++) (*fic_in) >> v_[i][j];
		for (int j=0 ; j<3 ; j++) (*fic_in) >> f_[i][j];
		(*fic_in) >> r_[i]; 

		//Read a line
		std::getline((*fic_in),buffer);
	    }
	}
    }
}

void particles::print()
{
    std::cout << "Averaged quantities \n";
    std::cout << "vAvg : " << vAvg_[0] << " " << vAvg_[1] << " " << vAvg_[2] << " " << vAvg_[3] << "\n" ;
    std::cout << "xAvg : " << xAvg_[0] << " " << xAvg_[1] << " " << xAvg_[2] << " " << xAvg_[3] << "\n" ;
    std::cout << "fAvg : " << fAvg_[0] << " " << fAvg_[1] << " " << fAvg_[2] << " " << fAvg_[3] << "\n" ;
}

void particles::calcNorm()
{
    // Calculate the norm of each per-particle quantities
    for (int i=0 ; i<np_ ; i++)
    {
	v_[i][3]= sqrt(v_[i][0]*v_[i][0] + v_[i][1]*v_[i][1] + v_[i][2]*v_[i][2]);
	x_[i][3]= sqrt(x_[i][0]*x_[i][0] + x_[i][1]*x_[i][1] + x_[i][2]*x_[i][2]);
	f_[i][3]= sqrt(f_[i][0]*f_[i][0] + f_[i][1]*f_[i][1] + f_[i][2]*f_[i][2]);
    }
}

void particles::calcAverage()
{
    // Calculate the average of each variable and store them in a vector array
    for (int i=0 ; i< np_ ; i++)
    {
	for (int j=0; j< 4 ; j++)
	{
	    vAvg_[j] += v_[i][j];
	    xAvg_[j] += x_[i][j];
	    fAvg_[j] += f_[i][j];
	}
    }

    for (int j=0 ; j<4 ; j++)
    {
	vAvg_[j] = vAvg_[j]/np_;
	xAvg_[j] = xAvg_[j]/np_;
	fAvg_[j] = fAvg_[j]/np_;
    }
}

std::vector<double> particles::getAverageV()
{
    return vAvg_;
}

std::vector<double> particles::getAverageX()
{
    return xAvg_;
}

std::vector<double> particles::getAverageF()
{
    return fAvg_;
}

std::vector<double> particles::getAverageU()
{
    return uAvg_;
}


