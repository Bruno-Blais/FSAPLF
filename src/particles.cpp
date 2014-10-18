// Last Modified: Sat 18 Oct 2014 05:47:21 PM CEST
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

#define PI 3.14159265359
#define verbose 0

particles::particles() : vAvg_(24), xAvg_(24), fAvg_(24), uAvg_(24) 
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
	delete u_[i];
    }
    delete x_;
    delete v_;
    delete f_;
    delete u_;
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
    u_ = new double*[n];

    for (int i = 0 ; i < np_ ; i++)
    {
	v_[i] = new double[4];
	x_[i] = new double[4];
	f_[i] = new double[4];
	u_[i] = new double[4];
    }
}

void particles::load(std::ifstream *ficIn)
{
    int inputType=0;
    bool isPresentU=false;

    //Declaration
    std::string buffer;
    std::vector<std::string> tokens;

    //Get the lines
    std::getline((*ficIn),buffer);

    //Parse the header of the files
    boost::algorithm::split(tokens, buffer, boost::algorithm::is_any_of(" "));	

    // Depending on the header type, finally parse the data into the particles_ structure
    // Some default LAMMPS input are already present, however this is not generic. The code does not
    // interpret the data structure per se, it just detects which one among a set list of data structures
    // Adding further data will eventually make it generic (I guess?)
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

    if (
	tokens[2]=="id"		&&
	tokens[3]=="type"	&&
	tokens[5]=="x"		&&
	tokens[8]=="vx"		&&
	tokens[11]=="fx"	&&
	tokens[14]=="omegax"	&&
	tokens[17]=="radius"
	) inputType=3;
    
    if (
	tokens[2]=="id"		&&
	tokens[3]=="type"	&&
	tokens[5]=="x"		&&
	tokens[11]=="vx"	&&
	tokens[14]=="fx"	&&
	tokens[17]=="f_uf[1]"	&&
	tokens[20]=="radius"
	) inputType=4;

     if (
	tokens[2]=="id"		&&
	tokens[3]=="type"	&&
	tokens[5]=="x"		&&
	tokens[11]=="vx"	&&
	tokens[14]=="fx"	&&
	tokens[18]=="f_uf[1]"	&&
	tokens[21]=="radius"
	) inputType=5;

     if (
        tokens[2]=="id"		&&
        tokens[3]=="type"	&&
	tokens[5]=="x"		&&
	tokens[8]=="vx"		&&
	tokens[11]=="fx"	&&
	tokens[14]=="f_uf[1]"   &&
        tokens[18]=="radius"    
	) inputType=6;


   
    if (inputType==0) 
	std::cout << "A valid LAMMPS input type has not been detected, please correct this..." << std::endl;

    else
    {	
	if (inputType==1)
	{
	    if(verbose) std::cout << "Input format : " << inputType << std::endl ;
	    for(int i=0 ; i<np_ ; i++)
	    {
		(*ficIn) >> ids_[i]; 
		for (int j=0 ; j<2 ; j++) (*ficIn) >> buffer;
		for (int j=0 ; j<3 ; j++) (*ficIn) >> x_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> buffer;
	    	for (int j=0 ; j<3 ; j++) (*ficIn) >> v_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> f_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> buffer;
		(*ficIn) >> r_[i]; 
	
		//Read a line
		std::getline((*ficIn),buffer);
	    }
	}
	
	if (inputType==2)
	{
	    if(verbose) std::cout << "Input format : " << inputType << std::endl; 
	     for(int i=0 ; i<np_ ; i++)
	    {
		//Cast into the right variable
		(*ficIn) >> ids_[i]; 
		(*ficIn) >> buffer;
		(*ficIn) >> buffer;
		for (int j=0 ; j<3 ; j++) (*ficIn) >> x_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> v_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> f_[i][j];
		(*ficIn) >> r_[i]; 

		//Read a line
		std::getline((*ficIn),buffer);
	    }
	}

	if (inputType==3)
	{
	    if(verbose) std::cout << "Input format : " << inputType << std::endl; 
	     for(int i=0 ; i<np_ ; i++)
	    {
		(*ficIn) >> ids_[i]; 
		for (int j=0 ; j<2 ; j++) (*ficIn) >> buffer;
		for (int j=0 ; j<3 ; j++) (*ficIn) >> x_[i][j];
	    	for (int j=0 ; j<3 ; j++) (*ficIn) >> v_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> f_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> buffer;
		(*ficIn) >> r_[i]; 

		//Read a line
		std::getline((*ficIn),buffer);
	    }
	}

	if (inputType==4)
	{
	    if(verbose) std::cout << "Input format : " << inputType << std::endl; 
	     for(int i=0 ; i<np_ ; i++)
	    {
		(*ficIn) >> ids_[i]; 
		for (int j=0 ; j<2 ; j++) (*ficIn) >> buffer;
		for (int j=0 ; j<3 ; j++) (*ficIn) >> x_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> buffer;
	    	for (int j=0 ; j<3 ; j++) (*ficIn) >> v_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> f_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> buffer;
		(*ficIn) >> r_[i]; 

		//Read a line
		std::getline((*ficIn),buffer);
	    }
	}

	if (inputType==5)
	{
	    if(verbose) std::cout << "Input format : " << inputType << std::endl; 
	     for(int i=0 ; i<np_ ; i++)
	    {
		(*ficIn) >> ids_[i]; 
		for (int j=0 ; j<2 ; j++) (*ficIn) >> buffer;
		for (int j=0 ; j<3 ; j++) (*ficIn) >> x_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> buffer;
	    	for (int j=0 ; j<3 ; j++) (*ficIn) >> v_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> f_[i][j];
		for (int j=0 ; j<4 ; j++) (*ficIn) >> buffer;
		(*ficIn) >> r_[i]; 

		//Read a line
		std::getline((*ficIn),buffer);
	    }
	}
        
        if (inputType==6)
	{
	    if(verbose) std::cout << "Input format : " << inputType << std::endl; 
	     for(int i=0 ; i<np_ ; i++)
	    {
		//Cast into the right variable
		(*ficIn) >> ids_[i]; 
		(*ficIn) >> buffer;
		(*ficIn) >> buffer;
		for (int j=0 ; j<3 ; j++) (*ficIn) >> x_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> v_[i][j];
		for (int j=0 ; j<3 ; j++) (*ficIn) >> f_[i][j];
		(*ficIn) >> r_[i]; 

		//Read a line
		std::getline((*ficIn),buffer);
	    }
	}

	// Variables that are not present in the input file are zeroed
	if (isPresentU == false)
	{
	    for (int i=0 ; i<np_ ; i++)
	    {
		for (int j=0 ; j<3 ; j++) u_[i][j]=0.;
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
    std::cout << "uAvg : " << uAvg_[0] << " " << uAvg_[1] << " " << uAvg_[2] << " " << uAvg_[3] << "\n" ;
}

void particles::calcNorm()
{
    // Calculate the norm of each per-particle quantities
    for (int i=0 ; i<np_ ; i++)
    {
	v_[i][3]= sqrt(v_[i][0]*v_[i][0] + v_[i][1]*v_[i][1] + v_[i][2]*v_[i][2]);
	x_[i][3]= sqrt(x_[i][0]*x_[i][0] + x_[i][1]*x_[i][1] + x_[i][2]*x_[i][2]);
	f_[i][3]= sqrt(f_[i][0]*f_[i][0] + f_[i][1]*f_[i][1] + f_[i][2]*f_[i][2]);
	u_[i][3]= sqrt(u_[i][0]*u_[i][0] + u_[i][1]*u_[i][1] + u_[i][2]*u_[i][2]);
    }
}

void particles::calcAverage()
{
    int skip=0;
    double perc=0.99;
    std::vector<double> tempVec(2);


    //Flush everything back to 0
    std::fill(vAvg_.begin(), vAvg_.end(), 0);
    std::fill(xAvg_.begin(), xAvg_.end(), 0);
    std::fill(fAvg_.begin(), fAvg_.end(), 0);
    std::fill(uAvg_.begin(), uAvg_.end(), 0);

    //Initiate the maximums to -99999 and the Minimums to 99999
    for (int j=8 ; j<12; j++)
    {
	vAvg_[j]=9999.;
	vAvg_[j+4]=-9999.;
	xAvg_[j]=9999.;
	xAvg_[j+4]=-9999.;
	fAvg_[j]=9999.;
	fAvg_[j+4]=-9999.;
	uAvg_[j]=9999.;
	uAvg_[j+4]=-9999.;
    }

    // Calculate the average of each variable and store them in a vector array
    for (int i=0 ; i< np_ ; i++)
    {
	for (int j=0; j< 4 ; j++)
	{
	    vAvg_[j] += v_[i][j];
	    xAvg_[j] += x_[i][j];
	    fAvg_[j] += f_[i][j];
	    uAvg_[j] += u_[i][j];
	}

	// Calculate the maximum
	skip=12;
	for (int j=0 ; j< 4 ; j++)
	{
	    if (v_[i][j] > vAvg_[skip+j]) vAvg_[skip+j]=v_[i][j];
	    if (x_[i][j] > xAvg_[skip+j]) xAvg_[skip+j]=x_[i][j];		
	    if (f_[i][j] > fAvg_[skip+j]) fAvg_[skip+j]=f_[i][j];
	    if (u_[i][j] > uAvg_[skip+j]) uAvg_[skip+j]=u_[i][j];
	}

	// Calculate the minimum
	skip=8;
	for (int j=0 ; j< 4 ; j++)
	{
	    if (v_[i][j] < vAvg_[skip+j]) vAvg_[skip+j]=v_[i][j];
	    if (x_[i][j] < xAvg_[skip+j]) xAvg_[skip+j]=x_[i][j];		
	    if (f_[i][j] < fAvg_[skip+j]) fAvg_[skip+j]=f_[i][j];
	    if (u_[i][j] < uAvg_[skip+j]) uAvg_[skip+j]=u_[i][j];
	}
    }

    // Reduce the sums to get the average value
    for (int j=0 ; j<4 ; j++)
    {
	vAvg_[j] = vAvg_[j]/np_;
	xAvg_[j] = xAvg_[j]/np_;
	fAvg_[j] = fAvg_[j]/np_;
	uAvg_[j] = uAvg_[j]/np_;
    }

    // Calculate the standard deviation
    // sqrt( 1/N sum (x^2) - xbar^2 ) 
    skip=4;
    for (int i=0; i<np_ ; i++)
    {
	// Calculate squared sum for standard deviation
	for (int j=0 ; j< 4 ;j++)
	{
	    vAvg_[j+skip] += pow(v_[i][j]-vAvg_[j], 2);
	    xAvg_[j+skip] += pow(x_[i][j]-xAvg_[j], 2);
	    fAvg_[j+skip] += pow(f_[i][j]-fAvg_[j], 2);
	    uAvg_[j+skip] += pow(u_[i][j]-uAvg_[j], 2);
	}
    }

    for (int j=0 ; j < 4 ; j++)
    {
	vAvg_[j+skip] = sqrt(vAvg_[j+skip]/np_);
	xAvg_[j+skip] = sqrt(xAvg_[j+skip]/np_);
	fAvg_[j+skip] = sqrt(fAvg_[j+skip]/np_);
	uAvg_[j+skip] = sqrt(uAvg_[j+skip]/np_);
    }

    skip=16;
    // Calculate the 99% max and min
   for (int j=0 ; j < 4 ; j++)
   {
	tempVec=calcPercentageMax(x_, j, perc);
	xAvg_[j+skip]=tempVec[0];
	xAvg_[j+skip+4]=tempVec[1];

	tempVec=calcPercentageMax(v_, j, perc);
	vAvg_[j+skip]=tempVec[0];
	vAvg_[j+skip+4]=tempVec[1];

	tempVec=calcPercentageMax(f_, j, perc);
	fAvg_[j+skip]=tempVec[0];
	fAvg_[j+skip+4]=tempVec[1];

	tempVec=calcPercentageMax(u_, j, perc);
    	uAvg_[j+skip]=tempVec[0];
	uAvg_[j+skip+4]=tempVec[1];
   }
}



std::vector<double> particles::calcPercentageMax(double** x, int dim, double perc)
{
    // This function extracts the maximal and minimal percentage amount. For instance, if you have 100 data point
    // and your specify perc is 0.99, it will go and grab the 99 maximal and the 99 minimal data point of each thing
    // and output them as a vector
    int index;
    std::vector<double> percMax(2);
    
    // Create vector->double array of sufficient size
    std::vector<double> tempArray(np_);

    // Dump double array into the vector
    for (int i=0 ; i < np_ ; i++)
    {
	tempArray[i] = x[i][dim];
    }

    // Sort the baby
    std::sort (tempArray.begin(), tempArray.end());   	

    // Find the index correspondant to max perc
    index = int(perc*np_);
    
    // Output
    percMax[1]=tempArray[index];

    // Find index corresponding the min perc
    index = int((1.-perc) * np_);

    // Output
    percMax[0]=tempArray[index];

    return percMax;
}

//*************
// Accessors
//*************

int particles::getNumber() {return np_;}

double* particles::getV(int id)	{return v_[id];}

double* particles::getX(int id) {return x_[id];}

double* particles::getRArray() {return r_;}

double** particles::getXArray() {return x_;}

double** particles::getVArray() {return v_;}

std::vector<int> particles::getIds()
{
    std::vector<int> ids(np_);
    
    for (int i=0 ; i<np_ ; i++)
    {
	ids[i]=ids_[i];
    }

    return ids;
}

std::vector<double> particles::getAverageV(){return vAvg_;}

std::vector<double> particles::getAverageX(){return xAvg_;}

std::vector<double> particles::getAverageF(){return fAvg_;}

std::vector<double> particles::getAverageU(){return uAvg_;}

