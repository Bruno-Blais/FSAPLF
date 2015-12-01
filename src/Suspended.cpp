/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : Suspended.cpp
*
*   Description :   Suspended criteria analysis class
*
*******************************************************************************************/

/*********************
*  GENERAL INCLUDES
*********************/
#include <iostream>
#include <stdlib.h>     
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

/********************
* HEADER INCLUDES
********************/
#include "Suspended.h"
#include "util.h"

#define PI 3.14159265359
#define DEBUG 0
#define WIDTHOUT 16
#define WIDTH   30
#define WIDTH2  36
#define PRES 7

Suspended::Suspended(int argc, char* argv[]) 
{
    initiated_=false;
    enabled_=false;
    std::string arg;
    int i=0;
    while (i<argc)
    {
        // Cast char* to string to allow for easy comparisons
        arg = argv[i]; 
        
        // Convert argument to lower case
        arg = utilLowerStr(arg);
        if ("-suspended"==arg)
        {
            if (i+1>argc-1)
            {
                cout << std::endl << std::endl;
                cout << "!!! Suspended requires at least an argument" << std::endl;
                printMan();
                exit(EXIT_FAILURE);
            }
            arg=argv[i+1];
            arg=utilLowerStr(arg);

            if ("man"==arg)
            {
                printMan();
            }
            else
            {
                enabled_=true;
                std::cout << std::setw(WIDTH)  << "Suspended" << ": enabled" << std::endl;
                start_=atoi(argv[i+1]);
                end_=atoi(argv[i+2]);
                limit_=atof(argv[i+3]);
                axis_= atoi(argv[i+4]);
                type_=string(argv[i+5]);
                type_=utilLowerStr(type_);
                if(type_ != "displacement" && type_ != "velocity" && type_ != "zdisplacement")
                {
                    cout << "!!! Type " << type_ << " is not supported" << std::endl;
                    printMan();
                    exit(EXIT_FAILURE);
                }
                crit_= atof(argv[i+6]);
                std::cout << std::setw(WIDTH2) << "Start: " << start_ << std::endl;
                std::cout << std::setw(WIDTH2) << "End: " << end_ << std::endl;
                std::cout << std::setw(WIDTH2) << "Limit: " << limit_ << std::endl;
                std::cout << std::setw(WIDTH2) << "Axis: "  << axis_ << std::endl;
                std::cout << std::setw(WIDTH2) << "Type: "  << type_ << std::endl;
                std::cout << std::setw(WIDTH2) << "Value: "  << crit_ << std::endl;
            }

            i++;
        }
        else
        {
            i++;
        }
    }
}

Suspended::~Suspended()
{
}

void Suspended::manage(int iter, int np, int* id, double** x, double** v)
{
    if (enabled_)
    {
        id_=id; //attribute array;
        np_=np;
        x_=x;
        v_=v;

        // If zeroth iteration has already been set, normal analysis
        if (!initiated_)
        {
            if (iter>=start_ && iter <=end_) 
            {
                initiated_=true;
                if (type_=="displacement" || type_=="zdisplacement")  setZeroth(x_);
                else if (type_=="velocity") setZeroth(v_);
                iter_.push_back(iter);
                nSusp_.push_back(0);
                nPart_.push_back(np_);
            }
        }
        else
        {
            iter_.push_back(iter);
            if (DEBUG) std::cout << "Analyzing" << std::endl;
            analyze();
        }
    }
}

void Suspended::setZeroth(double** var)
{
    enabled_=true;
    np0_=np_;
    
    //Allocate memory for var_ and linking table
    var_ = new double*[np0_];
    link_ = new int[2*np0_];     //link table is buffered up to allow for the case where particles changed
    susp_= new int[np0_];

    // Allocate the local arrays and copy the data
    for (int i=0 ; i<np0_ ; i++)
    {
        var_[i] = new double[3];
        for (int j=0 ; j<3 ; j++)
        {
            var_[i][j]=var[i][j];
        }
    
        susp_[i]=0;
    }

    //Create link table
    for (int i=0 ; i <np0_ ; i++) 
    {
        link_[id_[i]]=i;
        if (DEBUG && id_[i]>2*np0_) std::cout<< id_[i] << endl;
    }
}

void Suspended::analyze()
{
    if (type_=="velocity") 
    {
        analyzeVar(v_);
    }
    else if (type_=="displacement" || type_=="zdisplacement")
    {
        analyzeVar(x_);
    }
    int nSusp=0;
    for (int i=0 ; i < np_ ; i++)
    {
        nSusp+=susp_[link_[id_[i]]];
    }
    nSusp_.push_back(nSusp);
    nPart_.push_back(np_);
}


void Suspended::analyzeVar(double **var)
{
    for (int i=0 ; i < np_ ; i++)
    {
        double dist=0;
        if (x_[i][axis_] < limit_)
        {   
            int initj=0;
            if (type_=="zdisplacement") initj=2;
            for (int j=initj ; j< 3 ; j++)
            {
                dist+=(var_[link_[id_[i]]][j]- var[i][j]) * (var_[link_[id_[i]]][j]- var[i][j]);
            }
            if (dist > crit_*crit_)
            {
                susp_[link_[id_[i]]]=1;
            }
        }
        else
        {
            susp_[link_[id_[i]]]=1;
        }
    }
}

void Suspended::printMan()
{
    std::cout << std::endl << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(WIDTH)  << "MANUAL FOR SUSPENDED ANALYSIS OF PARTICLES" << std::endl;
    std::cout << std::setw(WIDTH2) << "start end limit axis Type argType" << std::endl;
    std::cout << std::setw(WIDTH2) << "Types available: Displacement, Velocity, zDisplacement " << std::endl;
    std::cout << std::setw(WIDTH2) << "Arguments Displacement : Displacement " << std::endl;
    std::cout << std::setw(WIDTH2) << "Arguments Velocity : VelocityMagnitude " << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl << std::endl;
}

void Suspended::write(std::string path, std::string label)
{
    std::string filename = path+"/"+label+"_suspended";
    std::ofstream ficOut(filename.c_str());

    ficOut << "iter ";
    ficOut << "\tN-" << " suspended" ;	    
    ficOut << "\tN-" << " particles" ;	
    ficOut << std::endl;

    for (unsigned int i=1 ; i<iter_.size() ; i++)
    {
	ficOut << std::setprecision(PRES);
	ficOut << iter_[i] << " " << nSusp_[i] << " "<< nPart_[i]  ;  
	ficOut << std::endl;
    }
    ficOut.close();
}
