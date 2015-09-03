/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : Rsd.h
*
*   Description :   Container class for Reduced Standard Deviation (RSD) analysis
*                   Types of initial seclusion available
*                       - Cartesian (x,y,z)
*                       - Radial (r)
*                   Types of sampling 
*
*
*******************************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include "nr3.h"

#ifndef RSD_H
#define RSD_H 

class Rsd
{
private :
    string type_;
    std::vector<double> origin_;
    int axis_;
    double length_;                                 
    std::vector<std::vector<double> > probes_;      // Coordinates of all probes
    std::vector<double> probesR_;                   // Radius of all probes

    void printMan();
    void loadProbes(string fname);

public :
    Rsd(int, char**,int);
    ~Rsd();

};
#endif
