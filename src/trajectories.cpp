// Last Modified: Wed 02 Jul 2014 05:10:48 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : averaging.cpp
*
*   Description :   Container class to establish trajectories for particles
*
*******************************************************************************************/


//*******************
//  GENERAL INCLUDES
//*******************
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

/********************
* HEADER INCLUDES
********************/
#include "trajectories.h"

#define LARGE 99999.
#define WIDTH 12
#define PRES 7

trajectories::trajectories() : ids_(1)
{
    x_=NULL;
    nIter_=NULL;
    ntrj_=0;
    nit_=0;
}

trajectories::~trajectories()
{
    for (int i =0 ; i<nit_ ;i++)
    {
	delete x_[i];
    }
    delete x_;
    delete nIter_;
}

void trajectories::allocate(int type, int nit, int ntrj,std::vector<int> ids)
{
    // Give the values to the local integer variables
    type_=type;
    ntrj_ = ntrj;
    nit_ = nit;
    ids_=ids;

    // Allocate local memory for the information about the averages
    nIter_= new int[nit_];
    x_ = new double*[nit_];
    y_ = new double*[nit_];
    z_ = new double*[nit_];

    for (int i = 0 ; i < nit ; i++)
    {
	x_[i] = new double[ntrj_];
    	y_[i] = new double[ntrj_];
	z_[i] = new double[ntrj_];
    }
}

void trajectories::setStep(int iter, int np, std::vector<int> ids, double** x)
{
   for (int i =0 ; i<np ; i++)
   {
	for (int j = 0 ; j < ntrj_ ; j++)
	//Particle of corresponding Id has been found
	if (ids[j] == ids_[i])
	{
	    x_[iter][j] = x[i][0];
	    y_[iter][j] = x[i][2];
	    z_[iter][j] = x[i][3];
	    break;
	}
   }
}

void trajectories::writeFile(std::string path, std::string label, std::string var)
{
    std::string filename = path+"/"+label+"_averaged_"+var;
    std::ofstream ficOut(filename.c_str());
    
    ficOut	<< std::setw(WIDTH) << "iter \t" 
		//<< std::setw(WIDTH) << "id \t" 	    
		<< std::setw(WIDTH) << "x \t" 	
		<< std::setw(WIDTH) << "y \t" 	    
		<< std::setw(WIDTH) << "z \t" 	
		<< std::setw(WIDTH) << "vx \t" 	    
		<< std::setw(WIDTH) << "vy \t" 	
		<< std::setw(WIDTH) << "vz "
		<< std::endl;

    for (int i=0 ; i<nit_ ; i++)
    {
	ficOut << std::setw(WIDTH);
	ficOut << std::setprecision(PRES);
	ficOut	<< ntrj_ << " " ;  
	ficOut << std::endl;
    }
    ficOut.close();
}

std::vector<int> trajectories::getIds(){return ids_;}
