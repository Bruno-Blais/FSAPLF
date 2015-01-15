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

#include "nr3.h" 

#ifndef CALC_H
#define CALC_H 

void calcCyl(double*,double*);                                  // Transforms from cartesian to cylindrical coordinates
inline double calcReDev(int n,double* x,double *y);             // Calculate reduced deviation array
double calcMean(int n,double* x);                        // Calculate mean
double calcStdDev(int n,double* x);
double calcCij(int n,double* x,double* y);
MatDoub calcMatMult(MatDoub A, MatDoub B);                      // Matrix multiplication
MatDoub calcMatTranspose(MatDoub A);                            // Matrix transpose
void calcPrintMat(MatDoub,std::string);                         // Print a Matrix
#endif
