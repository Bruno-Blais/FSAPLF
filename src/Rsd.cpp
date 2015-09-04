/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : MixingIndex.cpp
*
*   Description :   Container class for the principal component analysis to obtain mixing
*                   index
*
*******************************************************************************************/


/*********************
*  GENERAL INCLUDES
*********************/
#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
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
#include "Rsd.h"

#define PI 3.14159265359
#define DEBUG 1
#define WIDTHOUT 16
#define WIDTH   30
#define WIDTH2  36

Rsd::Rsd(int argc, char* argv[]) 
{
    initiated_=false;
    std::string arg;
    int i=0;
    
    while (i<argc)
    {
        // Cast char* to string to allow for easy comparisons
        arg = argv[i]; 
        
        // Convert argument to lower case
        std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
        
        if ("-rsd"==arg)
        {
            if (i+1>argc-1)
            {
                cout << std::endl << std::endl;
                cout << "!!! Rsd requires at least an argument" << std::endl;
                printMan();
                exit(EXIT_FAILURE);
            }
            arg=argv[i+1];
            std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);

            if ("man"==arg)
            {
                printMan();
            }
            else
            {
                enabled_=true;
                std::cout << std::setw(WIDTH)  << "RSD" << ": enabled" << std::endl;
                type_=string(argv[i+1]);
                std::transform(type_.begin(), type_.end(), type_.begin(), ::tolower);
                std::cout << std::setw(WIDTH2) << "Type: " << type_ << std::endl;
                
                if(type_ == "cartesian" || type_ == "cylindrical")
                {
                    for (int j=0 ; j <3  ; j++)
                    {
                        origin_.push_back(atof(argv[i+2+j]));
                    }
                    i+=4;
                
                    std::cout << std::setw(WIDTH2) << "Origin: " << origin_[0] 
                        << " " << origin_[1] << " " << origin_[2] << std::endl;
                    
                    if (type_ == "cartesian")
                    {
                        axis_=atoi(argv[i+1]);
                        if (axis_ >2) 
                        {
                            std::cout<<  "\n!!! Axis is not available. 0-x, 1-y, 2-z\n" << std::endl;
                            exit(EXIT_FAILURE);
                        }
                        std::cout << std::setw(WIDTH2) << "Axis: "  << axis_ << std::endl;
                    }
                    else if (type_ == "cylindrical")
                    {
                        length_=atof(argv[i+1]);
                        std::cout << std::setw(WIDTH2) << "Length: " << length_ << std::endl;
                    }
                    i++;

                    // TODO
                    // The probing points and their sizes need to be added
                    arg=string(argv[i+1]);
                    Rsd::loadProbes(arg);
                }
                else
                {
                    cout << "!!! Type " << type_ << " is not supported" << std::endl;
                }
            }

            i++;
        }
        else
        {
            i++;
        }
    }
}

Rsd::~Rsd()
{
}


void Rsd::loadProbes(string fname)
{
    std::ifstream ficIn;        // input file identifier
    ficIn.open(fname.c_str());  // Conversion of string to char so file may be opened
    
    // Declarations
    std::string buffer; // buffer for the getline
    std::vector<std::string> tokens; // line will be split into tokens seperator

    if (ficIn.fail())
    {
	std::cout << "!!! File : " << fname << " could not be opened correctly " << std::endl;
    }
    else
    {
	std::cout << std::setw(WIDTH2) <<  "Opening probes file: " << fname << std::endl;
        while (true) 
        {
            //Get the line
            std::getline(ficIn,buffer);
            if( ficIn.eof() ) break;
            boost::algorithm::split(tokens, buffer, boost::algorithm::is_any_of(" "));	
            std::vector<double> point;
            
            // Load a single point
            for (int i =0; i < 3 ; i ++)
            {
                point.push_back(atof(tokens[i].c_str()));
            }

            // Push back the point
            probes_.push_back(point);
            probesR_.push_back(atof(tokens[3].c_str()));
        }

        if (DEBUG)
        {
            for (unsigned int i=0 ; i < probes_.size() ; i++)
            {
                std::cout << "Point " << i << " :" << " " << probes_[i][0] << " " << probes_[i][1] << " " << probes_[i][2] << std::endl;
            }
        }
    }
}
void Rsd::manage(int iter, int np, int* id, double** x)
{
    if (enabled_)
    {
        id_=id; //attribute array;
        np_=np;
        x_=x;

        // If zeroth iteration has already been set, normal analysis
        if (!initiated_)
        {
            if (DEBUG) std::cout << "Initializating labels" << std::endl;
            initiated_=true;
            iters_.push_back(iter);
            labelParticles();
        }
        else
        {
            if (DEBUG) std::cout << "Analyzing" << std::endl;
        }
    }
}

void Rsd::labelParticles()
{
    labels_.resize(np_);
    if (type_ == "cartesian")
    {
        labelParticlesCartesian();
    }
    if (type_ == "cylindrical")
    {
        labelParticlesCylindrical();
    }
}

void Rsd::labelParticlesCartesian()
{
    for (int i=0; i <np_ ; i++)
    {
        if(x_[i][axis_] < origin_[axis_])
        {
            labels_[id_[i]]=1;
        }
        else
        {
            labels_[id_[i]]=0;
        }
    }
}

void Rsd::labelParticlesCylindrical()
{
    double r;
    double xc, yc,c;
    
    for (int i=0; i <np_ ; i++)
    {
        xc = x_[i][0] - origin_[0];
        xc = x_[i][0] - origin_[0];
        r = sqrt(x_[i][0]*x_[i][0]+x_[i][1]*x_[i][1])
        c = sqrt(origin_[0]*origin[0] + origin[1]*origin[1])
        if(])
        {
            labels_[id_[i]]=1;
        }
        else
        {
            labels_[id_[i]]=0;
        }
    }
}

void Rsd::printMan()
{
    std::cout << std::endl << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(WIDTH)  << "MANUAL FOR RSD" << std::endl;
    std::cout << std::setw(WIDTH2) << "Types available: Cartesian, Cylindrical " << std::endl;
    std::cout << std::setw(WIDTH2) << "Arguments Cartesian : Origin (x0,y0,z0) and Axis of seperation " << std::endl;
    std::cout << std::setw(WIDTH2) << "Arguments Cylindrical : Origin (x0,y0,z0) and radius " << std::endl;
    std::cout << std::setw(WIDTH2) << "NOTE : cylindrical modes is based on a sub-division into two radial zone " << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl << std::endl;
}

