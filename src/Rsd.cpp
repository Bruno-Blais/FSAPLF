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
#include "util.h"

#define PI 3.14159265359
#define DEBUG 0
#define WIDTHOUT 16
#define WIDTH   30
#define WIDTH2  36
#define PRES 7

Rsd::Rsd(int argc, char* argv[]) 
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

            // Push back the point into the vector of vector
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
void Rsd::analyze()
{
    int nl,n;
    double r;
    std::vector<int> nc,npp; 
    for (unsigned int i=0 ; i<probes_.size(); i++)
    {
        n=0;
        nl=0;

        for (int j=0; j<np_ ; j++)
        {
            r=0;
            for (int k = 0 ; k<3 ; k++)
            {
                r+= (x_[j][k] - probes_[i][k]) * (x_[j][k] - probes_[i][k]) ;
            }
           
            if(DEBUG) std::cout << "Radius is :" << sqrt(r) << " \tx : " << x_[j][0] << " " << x_[j][1] << " " << x_[j][2] << std::endl << "\tProbesR\t"<< probesR_[i];

            if (r<=(probesR_[i]*probesR_[i]))
            {
                n+=1;
                nl+=label_[id_[j]];
                if (DEBUG)
                {
                    std::cout << "Particle detected" << " id " << id_[j] << " label " << label_[id_[j]] <<std::endl;
                    std::cout << "n and nl are worth : " << n << "\t" << nl << std::endl;
                }
            }
        }
        nc.push_back(nl);
        npp.push_back(n);
        if(DEBUG) std::cout << " Probe number " << i << " npp and nc\t" << n << " " << nl << std::endl;
    }

    // Push back into the large vector storage
    nc_.push_back(nc);
    npp_.push_back(npp);
}


void Rsd::labelParticles()
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

void Rsd::labelParticlesCartesian()
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

void Rsd::labelParticlesCylindrical()
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

void Rsd::printMan()
{
    std::cout << std::endl << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(WIDTH)  << "MANUAL FOR RSD" << std::endl;
    std::cout << std::setw(WIDTH2) << "Types available: Cartesian, Cylindrical " << std::endl;
    std::cout << std::setw(WIDTH2) << "Arguments Cartesian : Origin (x0,y0,z0) and Axis of seperation " << std::endl;
    std::cout << std::setw(WIDTH2) << "Arguments Cylindrical : Origin (x0,y0,z0) and radius " << std::endl;
    std::cout << std::setw(WIDTH2) << "Last argument is always the name of the probe file " << std::endl;
    std::cout << std::setw(WIDTH2) << "NOTE : cylindrical modes is based on a sub-division into two radial zone " << std::endl;
    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl << std::endl;
}

void Rsd::write(std::string path, std::string label)
{
    std::string filename = path+"/"+label+"_rsd";
    std::ofstream ficOut(filename.c_str());

    ficOut << std::setw(WIDTHOUT) << "iter ";
    for (unsigned int i=0 ; i <probes_.size(); i++)
    {
       ficOut << std::setw(WIDTHOUT) << "N-" << i << " colored" ;	    
       ficOut << std::setw(WIDTHOUT) << "N-" << i << " particles" ;	
    }
       ficOut << std::endl;

    for (unsigned int i=0 ; i<iter_.size() ; i++)
    {
        ficOut << std::setw(WIDTHOUT);
	ficOut << std::setprecision(PRES);
	ficOut	<< iter_[i] << " " ;  
	for (unsigned int j=0 ; j<probes_.size() ; j++) ficOut << std::setw(WIDTHOUT) << std::setprecision(PRES) << nc_[i][j] << "\t" <<npp_[i][j];
	ficOut << std::endl;
    }
    ficOut.close();
}
