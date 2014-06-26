// Last Modified: Thu 26 Jun 2014 03:54:34 PM EDT
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
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

/********************
* HEADER INCLUDES
********************/
#include "averaging.h"

#define LARGE 99999.
#define WIDTH 12
#define PRES 7

averaging::averaging()
{
    r_=NULL;
    v_=NULL;
    x_=NULL;
    f_=NULL;
    u_=NULL;
}

averaging::~averaging()
{
    for (int i =0 ; i<n_ ;i++)
    {
	delete v_[i];
	delete x_[i];
	delete f_[i];
	delete u_[i];
    }
    delete v_;
    delete x_;
    delete f_;
    delete u_;
    delete r_;
}

void averaging::allocate(int n)
{
    //Allocate local memory for the information about the averages
    n_ = n;
    nIter_ = new int[n];
    t_ = new double[n];
    r_ = new double[n];
    v_ = new double*[n];
    x_ = new double*[n];
    f_ = new double*[n];
    u_ = new double*[n];

    for (int i = 0 ; i < n ; i++)
    {
	v_[i] = new double[24];
	x_[i] = new double[24];
	f_[i] = new double[24];
	u_[i] = new double[24];
    }
}

void averaging::setIter(int k, int iter)
{
    nIter_[k]=iter; 
}

void averaging::setV (int k, std::vector<double> v)
{
    for (int i=0 ; i<24 ; i++)
	v_[k][i] = v[i];
}

void averaging::setX (int k, std::vector<double> v)
{
    for (int i=0 ; i<24 ; i++)
	x_[k][i] = v[i];
}

void averaging::setF (int k, std::vector<double> v)
{
    for (int i=0 ; i<24 ; i++)
	f_[k][i] = v[i];
}

void averaging::writeFile(std::string path, std::string label)
{
    writeSingleFile(path,label,"x",x_,24);
    writeSingleFile(path,label,"v",v_,24);
    writeSingleFile(path,label,"f",f_,24);
    writeSingleFile(path,label,"u",u_,24);
}

void averaging::writeSingleFile(std::string path, std::string label, std::string var, double** x, int l)
{
    std::string filename = path+"/"+label+"_averaged_"+var;
    std::ofstream ficOut(filename.c_str());
    
    ficOut	<< std::setw(WIDTH) << "iter \t" 
		<< std::setw(WIDTH) << "xA \t" 	    
		<< std::setw(WIDTH) << "yA \t" 	
		<< std::setw(WIDTH) << "zA \t" 	    
		<< std::setw(WIDTH) << "norm \t" 	
		<< std::setw(WIDTH) << "xStd \t" 	    
		<< std::setw(WIDTH) << "yStd \t" 	
		<< std::setw(WIDTH) << "zStd \t" 	    
		<< std::setw(WIDTH) << "normStd \t" 	
		<< std::setw(WIDTH) << "xMin \t" 	    
		<< std::setw(WIDTH) << "yMin \t"
		<< std::setw(WIDTH) << "zMin \t" 	    
		<< std::setw(WIDTH) << "normMin \t" 	
		<< std::setw(WIDTH) << "xMax \t" 	    
		<< std::setw(WIDTH) << "yMax \t" 	
		<< std::setw(WIDTH) << "zMax \t" 	    
		<< std::setw(WIDTH) << "normMax \t" 	
		<< std::setw(WIDTH) << "x99Min \t" 	    
		<< std::setw(WIDTH) << "y99Min \t"
		<< std::setw(WIDTH) << "z99Min \t" 
		<< std::setw(WIDTH) << "Norm99Min \t" 
		<< std::setw(WIDTH) << "x99Max \t"
		<< std::setw(WIDTH) << "y99Max \t" 	    
		<< std::setw(WIDTH) << "z99Max \t" 	
		<< std::setw(WIDTH) << "norm99Max \t" 	    
		<< std::endl;


    for (int i=0 ; i<n_ ; i++)
    {
	ficOut << std::setw(WIDTH);
	ficOut << std::setprecision(PRES);
	ficOut	<< nIter_[i] << " " ;  
	//	<< std::setw(WIDTH) << std::setprecision(PRES) << t_[i] << " ";
	for (int j=0 ; j<l ; j++) ficOut << std::setw(WIDTH) << std::setprecision(PRES) << x[i][j] << " ";
	ficOut << std::endl;
    }
    ficOut.close();
}
