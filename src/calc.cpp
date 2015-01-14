/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : calc.cpp
*
*   Description :   Container for calculation tools
*
*******************************************************************************************/

//*******************
//  GENERAL INCLUDES
//*******************
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

/********************
* HEADER INCLUDES
********************/

#define PI 3.14159265359
#define WIDTH 12
#define PRES 7

void calcCyl(double* p1, double* p2)
{
    // calculates r theta z from x y z
    p1[0] = sqrt(p2[0]*p2[0] + p2[1]*p2[1]);
    p1[1] = atan2(p2[1],p2[0]);
    p1[2] = p2[2];
}


inline double calcMean(int n, double* x)
{
    double sum=0;
    for (int i=0 ; i <n ; i++) sum += x[i];
    return sum/n;
}

inline double calcStdDev(int n, double* x)
{
    double s=0;
    double xMean=calcMean(n,x);
    
    for (int i=0 ; i <n ; i++)
    {   
        s += (x[i] - xMean) * (x[i] - xMean);
    }

    s = s/(n-1);
    return sqrt(s);
}

double calcCij(int n,double* x,double* y)
{
    double reDev[n];
    double xStd=calcStdDev(n,x);
    double yStd=calcStdDev(n,y);
    double xMean=calcMean(n,x);
    double yMean=calcMean(n,y);
    
    for(int i=0 ; i < n ; i++)
    {
        reDev[i] =  1./xStd * (x[i]-xMean) * 1./yStd * (y[i]-yMean);
    }


    return calcMean(n,reDev);
}
