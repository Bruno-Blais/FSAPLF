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
#include "nr3.h"


#define PI 3.14159265359
#define WIDTH 12
#define PRES 7
#define DEBUG 0

void calcCyl(double* p1, double* p2)
{
    // calculates r theta z from x y z
    p1[0] = sqrt(p2[0]*p2[0] + p2[1]*p2[1]);
    p1[1] = atan2(p2[1],p2[0]);
    p1[2] = p2[2];

    if(DEBUG) std::cout <<" Before coordinates :" << p2[0] << " " << p2[1] << " " << p2[2] << std::endl;
    if(DEBUG) std::cout <<" After coordinates :" << p1[0] << " " << p1[1] << " " << p1[2] << std::endl;
}

double calcMean(int n, double* x)
{
    double sum=0;
    for (int i=0 ; i <n ; i++) sum += x[i];
    return sum/n;
}

double calcStdDev(int n, double* x)
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

MatDoub calcMatMult(MatDoub A, MatDoub B)
{
    MatDoub M(A.nrows(),B.ncols());
    
    if (A.ncols() != B.ncols()) std::cerr << "Matrix dimension do not agree!" << endl;

    #pragma omp parallel for
    for (int i=0 ; i < A.nrows() ; i++)
    {
        for (int j=0 ; j < B.ncols() ; j++)
        {
            M[i][j]=0;
            for (int k =0 ; k < A.ncols() ; k++)
            {
                M[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return M;
}

MatDoub calcMatTranspose(MatDoub A)
{
    MatDoub M(A.ncols(),A.nrows());

    for (int i=0 ; i<A.nrows() ; i++)
    {
        for (int j=0 ; j<A.ncols() ; j++)
        {
            M[j][i]=A[i][j];
        }
    }

    return M;
}


void calcPrintMat(MatDoub A,string name)
{
    std::cout << "Matrix :" << name << std::endl;
    for (int i=0 ; i<A.nrows() ; i++)
    {
        for (int j=0 ; j<A.ncols() ; j++)
        {
            std::cout << std::setw(WIDTH) << A[i][j] << " " ;
        }
        std::cout<<std::endl;
    }
}
