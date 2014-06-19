// Last Modified: Thu 19 Jun 2014 04:13:10 PM EDT
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
    std::cout << "Averaging destructor?" << std::endl;
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
	v_[i] = new double[4];
	x_[i] = new double[4];
	f_[i] = new double[4];
	u_[i] = new double[4];
    }

/*
    box_[0] = -LARGE;
    box_[1] = LARGE;
    box_[2] = -LARGE;
    box_[3] = LARGE;
    box_[4] = -LARGE;
    box_[5] = LARGE;
*/

}

void averaging::setV (int k, std::vector<double> v)
{
    for (int i=0 ; i<4 ; i++)
	v_[k][i] = v[i];
}

void averaging::setX (int k, std::vector<double> v)
{
    for (int i=0 ; i<4 ; i++)
	x_[k][i] = v[i];
}

void averaging::setF (int k, std::vector<double> v)
{
    for (int i=0 ; i<4 ; i++)
	f_[k][i] = v[i];
}

void averaging::writeFile(std::string path, std::string label)
{
    std::string filename = path+label+"_averaged";
    std::ofstream ficOut(filename.c_str());
    for (int i=0 ; i<n_ ; i++)
    {
	ficOut << std::setw(WIDTH);
	ficOut << std::setprecision(PRES);
	ficOut	<< nIter_[i] << " "  
		<< std::setw(WIDTH) << std::setprecision(PRES) << t_[i] << " ";
	for (int j=0 ; j<4 ; j++) ficOut << std::setw(WIDTH) << std::setprecision(PRES) << x_[i][j] << " ";
	for (int j=0 ; j<4 ; j++) ficOut << std::setw(WIDTH) << std::setprecision(PRES) << v_[i][j] << " ";
	for (int j=0 ; j<4 ; j++) ficOut << std::setw(WIDTH) << std::setprecision(PRES) << f_[i][j] << " ";
	for (int j=0 ; j<3 ; j++) ficOut << std::setw(WIDTH) << std::setprecision(PRES) << u_[i][j] << " ";
	ficOut << std::setw(WIDTH) << std::setprecision(PRES) << u_[i][3];
	ficOut << std::endl;
    }
}
