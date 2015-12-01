/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : Suspended.h
*
*   Description :   Container class for Suspended (Zwiettering) analysis
*                   Types of suspended analysis are
*                       - Displacement (x vector)
*                       - Velocity (v vector)
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

#ifndef SUSPENDED_H
#define SUSPENDED_H 

class Suspended
{
private :
    bool enabled_;              // Suspended Analysis is defined
    bool initiated_;            // Suspended Initial step has been found
    int start_;                 // Start iteration
    int end_;                   // Ending iteration
    int axis_;                  // Axis used for the limits
    double limit_;              // Value of the limit 
    double crit_;               // Magnitude of displacement or velocity
    std::string type_;          // Type of Suspended analysis 
    std::vector<int> iter_;     // Number of iterations
    std::vector<int> nSusp_;    // Number of suspended particles
    std::vector<int> nPart_;    // Number of particles

    int np_;
    int np0_;
    int* id_;
    int* susp_;
    int* link_;
    double** x_;
    double** v_;
    double** var_;

    void setZeroth(double**);
    void analyze();
    void analyzeVar(double**);

public :
    Suspended(int, char**);
    ~Suspended();
    void manage(int,int,int*,double**,double**);
    void printMan();
    void write(std::string, std::string);

};
#endif
