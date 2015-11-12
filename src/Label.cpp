/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : Label.cpp
*
*   Description :   Container class for the labelling of the particles
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
#include "Label.h"
#include "util.h"

#define PI 3.14159265359
#define DEBUG 0
#define WIDTHOUT 16
#define WIDTH   30
#define WIDTH2  36
#define PRES 7

Label::Label(int argc, char* argv[]) 
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
        if ("-Label"==arg)
        {
            if (i+1>argc-1)
            {
                cout << std::endl << std::endl;
                cout << "!!! Label requires at least an argument" << std::endl;
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
                std::cout << std::setw(WIDTH)  << "RSD" << ": enabled" << std::endl;
                type_=string(argv[i+1]);
                type_=utilLowerStr(type_);
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

                    arg=string(argv[i+1]);
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

Label::~Label()
{
}

void Label::manage(int iter, int np, int* id, double** x)
{
    if (enabled_)
    {
        id_=id; //attribute array;
        np_=np;
        x_=x;
        iter_.push_back(iter);

        // If zeroth iteration has already been set, normal analysis
        if (!initiated_)
        {
            if (DEBUG) std::cout << "Initializating labels" << std::endl;
            initiated_=true;
            labelParticles();
            analyze();
        }
        else
        {
            if (DEBUG) std::cout << "Analyzing" << std::endl;
            analyze();
        }
    }
}

void Label::analyze()
{
}


void Label::labelParticles()
{
    label_.resize(np_);
    if (type_ == "cartesian")
    {
        labelParticlesCartesian();
    }
    if (type_ == "cylindrical")
    {
        labelParticlesCylindrical();
    }
}

void Label::labelParticlesCartesian()
{
    for (int i=0; i <np_ ; i++)
    {
        if(x_[i][axis_] >= origin_[axis_])
        {
            label_[id_[i]]=1;
            if(DEBUG) std::cout << " Label being apposed x : " << x_[i][axis_] << "\tid is : " << id_[i] << std::endl;
        }
        else
        {
            label_[id_[i]]=0;
        }
    }
}

void Label::labelParticlesCylindrical()
{
    double r;
    double xc, yc;
    
    for (int i=0; i <np_ ; i++)
    {
        xc = x_[i][0] - origin_[0];
        yc = x_[i][1] - origin_[1];
        r = sqrt(xc*xc+yc*yc);
        if(r>=length_)
        {
            label_[id_[i]]=1;
        }
        else
        {
            label_[id_[i]]=0;
        }
    }
}

void Label::printMan()
{
    std::cout << std::endl << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(WIDTH)  << "MANUAL FOR LABELING OF PARTICLES" << std::endl;
    std::cout << std::setw(WIDTH2) << "Types available: Cartesian, Cylindrical " << std::endl;
    std::cout << std::setw(WIDTH2) << "Arguments Cartesian : Origin (x0,y0,z0) and Axis of seperation " << std::endl;
    std::cout << std::setw(WIDTH2) << "Arguments Cylindrical : Origin (x0,y0,z0) and radius " << std::endl;
    std::cout << std::setw(WIDTH2) << "NOTE : cylindrical modes is based on a sub-division into two radial zone " << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl << std::endl;
}

void Label::rewrite(std::string path, std::string label)
{
    cout << path << label ;
}
