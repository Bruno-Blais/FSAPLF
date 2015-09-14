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
    bool enabled_;
    bool initiated_;
    string type_;
    std::vector<double> origin_;
    int axis_;
    double length_;                                 
    std::vector<std::vector<double> > probes_;      // Coordinates of all probes
    std::vector<double> probesR_;                   // Radius of all probes
    std::vector<int> iter_;                        // Number of iterations
    std::vector<int> label_;                       // Labels of the particles

    // The idea right now is just to count the particles and to calculate the RSD a posteriori in python...
    // Maybe this is not the right idea, but this is easier to interpret
    std::vector<std::vector<int> > nc_;             // number of colored (label=1) particles
    std::vector<std::vector<int> > npp_;            // number of particles in a probe

    int* id_;
    int np_;
    double** x_;


    void printMan();
    void loadProbes(string fname);
    void labelParticles();
    void labelParticlesCartesian();
    void labelParticlesCylindrical();
    void analyze();

public :
    Rsd(int, char**);
    ~Rsd();
    void manage(int,int,int*,double**);
    void write(std::string,std::string);

};
#endif
