// Last Modified: Tue 24 Jun 2014 03:38:19 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : averaging.h
*
*   Description : Container class for all the averaged properties of all files
*
*******************************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

#ifndef AVERAGING_H
#define AVERAGING_H 

class averaging
{
private :
    int	     n_;	    // Number of averages stored
    int*     nIter_;	    // Iteration number
    double*  t_;	    // Time for each iteration
    double** v_;	    // Velocity vector
    double** x_;	    // Positions vector
    double** f_;	    // Fluid-Solid interaction forces (fdrag)
    double** u_;	    // Velocity of the fluid
    double*  r_;	    // radiuses

public :
    averaging();
    ~averaging();
    void allocate(int);
    void setIter(int, int);
    void setV(int, std::vector<double>);
    void setX(int, std::vector<double>);
    void setF(int, std::vector<double>);
    void writeFile(std::string, std::string);
};
#endif
