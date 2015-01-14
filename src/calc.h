/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : calc.h
*
*   Description : Container for calculation tools   
*
*******************************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#ifndef CALC_H
#define CALC_H 

void calcCyl(double*,double*);                          // Transforms from cartesian to cylindrical coordinates
inline double calcReDev(int n,double* x,double *y);            // Calculate reduced deviation array
inline double calcMean(int n,double* x);                       // Calculate mean
inline double calcStdDev(int n,double* x);
double calcCij(int n,double* x,double* y);
#endif
