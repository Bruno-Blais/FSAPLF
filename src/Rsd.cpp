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

Rsd::Rsd(int argc, char* argv[], int nSteps) 
{
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
                
                    std::cout << std::setw(WIDTH2) << "Origin: " << origin_[0] << " " << origin_[1] << " " << origin_[2] << std::endl;
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
    std::ifstream ficIn; // input file identifier
    ficIn.open(fname.c_str()); // Conversion of string to char so file may be opened
    
    //Declarations
    std::string buffer;
    std::vector<std::string> tokens;
    std::vector<double> point;

    if (ficIn.fail())
    {
	std::cout << "!!! File : " << fname << " could not be opened correctly " << std::endl;
    }
    else
    {
	std::cout << std::setw(WIDTH2) <<  "Opening probes file: " << fname << std::endl;

        //Get the lines
        std::getline(ficIn,buffer);
        boost::algorithm::split(tokens, buffer, boost::algorithm::is_any_of(" "));	

        // Load a single point
        for (int i =0; i < 3 ; i ++)
        {
            point.push_back(atof(tokens[i].c_str()));
        }
        // Push back the point
        probes_.push_back(point);

        cout << probes_[0][0] << probes_[0][1] << probes_[0][2] << std::endl;
        //Read timestep
	//fic_in >> nit_;
	//getline(fic_in,buffer); //closing the line

	//std::getline(fic_in,buffer);
	//fic_in >> np_;

	//for (int i=0 ; i< 5 ; i++)
	//{
	//    std::getline(fic_in,buffer);
	//}
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

