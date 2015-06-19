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
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <boost/algorithm/string/classification.hpp>

/********************
* HEADER INCLUDES
********************/
#include "averaging.h"

#define LARGE 99999.
#define WIDTH 30
#define PRES 7
#define DEBUG 0

averaging::averaging(int argc, char* argv[], int nSteps) 
{
    int i=0;
    std::string arg;
    r_=NULL;
    v_=NULL;
    x_=NULL;
    f_=NULL;
    u_=NULL;
    
    rA_=NULL;
    vA_=NULL;
    fA_=NULL;
    uA_=NULL;
    xA_=NULL;

    while (i<argc)
    {
        arg = argv[i];
        if ("-average" ==arg)
        {
            // Get the percentile
            perc_=std::atof(argv[i+1]);
            i+=2;
            allocate(nSteps);
	    std::cout << std::setw(WIDTH) << "Averaging" << ": Enabled"    << std::endl;
	    std::cout << std::setw(WIDTH) << "Percentile" << ": " << perc_ << std::endl;
        }
        else
        {
            i++;
        }
    }

    if (DEBUG) std::cout << "Constructor over" << std::endl;
}

averaging::~averaging()
{
    for (int i =0 ; i<n_ ;i++)
    {
        delete vA_[i];
        delete xA_[i];
        delete fA_[i];
        delete uA_[i];
    }
    delete vA_;
    delete xA_;
    delete fA_;
    delete uA_;
    delete rA_;
}

void averaging::allocate(int n)
{
    //Allocate local memory for the information about the averages
    n_ = n;
    nIter_ = new int[n];
    t_ = new double[n];
    rA_ = new double[n];
    vA_ = new double*[n];
    xA_ = new double*[n];
    fA_ = new double*[n];
    uA_ = new double*[n];

    for (int i = 0 ; i < n ; i++)
    {
	vA_[i] = new double[24];
	xA_[i] = new double[24];
	fA_[i] = new double[24];
	uA_[i] = new double[24];
    }
}

void averaging::particles(int n, double** x, double** v, double** f, double** u)
{
    np_=n;
    x_=x;
    v_=v;
    f_=f;
    u_=u;

    if(DEBUG) std::cout << "Beggining averages" << std::endl;
    calcAverage();
}


void averaging::calcAverage()
{
    int skip=0;
    double perc=perc_;
    std::vector<double> tempVec(2);

    if (DEBUG) std::cout << "Reinit" << std::endl;
    
    // Flush everything to 0
    for (int j=0 ; j<24 ; j++)
    {
	vA_[cIndex_][j]=0.;
	xA_[cIndex_][j]=0.;
	fA_[cIndex_][j]=0.;
	uA_[cIndex_][j]=0.;
    }

    //Initiate the maximums to -99999 and the Minimums to 99999
    for (int j=8 ; j<12; j++)
    {
	vA_[cIndex_][j]=9999.;
	vA_[cIndex_][j+4]=-9999.;
	xA_[cIndex_][j]=9999.;
	xA_[cIndex_][j+4]=-9999.;
	fA_[cIndex_][j]=9999.;
	fA_[cIndex_][j+4]=-9999.;
	uA_[cIndex_][j]=9999.;
	uA_[cIndex_][j+4]=-9999.;
    }

    if (DEBUG) std::cout << "Averages" << std::endl;
    // Calculate the average of each variable and store them in a vector array
    for (int i=0 ; i< np_ ; i++)
    {
	for (int j=0; j< 4 ; j++)
	{
	    vA_[cIndex_][j] += v_[i][j];
	    xA_[cIndex_][j] += x_[i][j];
	    fA_[cIndex_][j] += f_[i][j];
	    uA_[cIndex_][j] += u_[i][j];
	}

	// Calculate the maximum
	skip=12;
	for (int j=0 ; j< 4 ; j++)
	{
	    if (v_[i][j] > vA_[cIndex_][skip+j]) vA_[cIndex_][skip+j]=v_[i][j];
	    if (x_[i][j] > xA_[cIndex_][skip+j]) xA_[cIndex_][skip+j]=x_[i][j];		
	    if (f_[i][j] > fA_[cIndex_][skip+j]) fA_[cIndex_][skip+j]=f_[i][j];
	    if (u_[i][j] > uA_[cIndex_][skip+j]) uA_[cIndex_][skip+j]=u_[i][j];
	}

	// Calculate the minimum
	skip=8;
	for (int j=0 ; j< 4 ; j++)
	{
	    if (v_[i][j] < vA_[cIndex_][skip+j]) vA_[cIndex_][skip+j]=v_[i][j];
	    if (x_[i][j] < xA_[cIndex_][skip+j]) xA_[cIndex_][skip+j]=x_[i][j];		
	    if (f_[i][j] < fA_[cIndex_][skip+j]) fA_[cIndex_][skip+j]=f_[i][j];
	    if (u_[i][j] < uA_[cIndex_][skip+j]) uA_[cIndex_][skip+j]=u_[i][j];
	}
    }


    if (DEBUG) std::cout << "Reduction of averages" << std::endl;
    // Reduce the sums to get the average value
    for (int j=0 ; j<4 ; j++)
    {
	vA_[cIndex_][j] = vA_[cIndex_][j]/np_;
	xA_[cIndex_][j] = xA_[cIndex_][j]/np_;
	fA_[cIndex_][j] = fA_[cIndex_][j]/np_;
	uA_[cIndex_][j] = uA_[cIndex_][j]/np_;
    }

    if (DEBUG) std::cout << "Standard deviations" << std::endl;
    // Calculate the standard deviation
    // sqrt( 1/N sum (x^2) - xbar^2 ) 
    skip=4;
    for (int i=0; i<np_ ; i++)
    {
	// Calculate squared sum for standard deviation
	for (int j=0 ; j< 4 ;j++)
	{
	    vA_[cIndex_][j+skip] += pow(v_[i][j]-vA_[cIndex_][j], 2);
	    xA_[cIndex_][j+skip] += pow(x_[i][j]-xA_[cIndex_][j], 2);
	    fA_[cIndex_][j+skip] += pow(f_[i][j]-fA_[cIndex_][j], 2);
	    uA_[cIndex_][j+skip] += pow(u_[i][j]-uA_[cIndex_][j], 2);
	}
    }

    for (int j=0 ; j < 4 ; j++)
    {
	vA_[cIndex_][j+skip] = sqrt(vA_[cIndex_][j+skip]/np_);
	xA_[cIndex_][j+skip] = sqrt(xA_[cIndex_][j+skip]/np_);
	fA_[cIndex_][j+skip] = sqrt(fA_[cIndex_][j+skip]/np_);
	uA_[cIndex_][j+skip] = sqrt(uA_[cIndex_][j+skip]/np_);
    }

   skip=16;
   // Calculate the 99% max and min
   for (int j=0 ; j < 4 ; j++)
   {
	tempVec=calcPercentageMax(x_, j, perc);
	xA_[cIndex_][j+skip]=tempVec[0];
	xA_[cIndex_][j+skip+4]=tempVec[1];

	tempVec=calcPercentageMax(v_, j, perc);
	vA_[cIndex_][j+skip]=tempVec[0];
	vA_[cIndex_][j+skip+4]=tempVec[1];

	tempVec=calcPercentageMax(f_, j, perc);
	fA_[cIndex_][j+skip]=tempVec[0];
	fA_[cIndex_][j+skip+4]=tempVec[1];

	tempVec=calcPercentageMax(u_, j, perc);
    	uA_[cIndex_][j+skip]=tempVec[0];
	uA_[cIndex_][j+skip+4]=tempVec[1];
   }
}

std::vector<double> averaging::calcPercentageMax(double** x, int dim, double perc)
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

void averaging::setIter(int k, int iter)
{
    nIter_[k]=iter;
    cIndex_=k;
}

void averaging::setV (int k, std::vector<double> v)
{
    for (int i=0 ; i<24 ; i++)
	vA_[k][i] = v[i];
}

void averaging::setX (int k, std::vector<double> v)
{
    for (int i=0 ; i<24 ; i++)
	xA_[k][i] = v[i];
}

void averaging::setF (int k, std::vector<double> v)
{
    for (int i=0 ; i<24 ; i++)
	fA_[k][i] = v[i];
}

void averaging::writeFile(std::string path, std::string label)
{
    writeSingleFile(path,label,"x",xA_,24);
    writeSingleFile(path,label,"v",vA_,24);
    //writeSingleFile(path,label,"f",fA_,24);
    //writeSingleFile(path,label,"u",uA_,24);
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
		<< std::setw(WIDTH) << "xfMin \t" 	    
		<< std::setw(WIDTH) << "yfMin \t"
		<< std::setw(WIDTH) << "zfMin \t" 
		<< std::setw(WIDTH) << "Norm99Min \t" 
		<< std::setw(WIDTH) << "xfMax \t"
		<< std::setw(WIDTH) << "yfMax \t" 	    
		<< std::setw(WIDTH) << "zfMax \t" 	
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
