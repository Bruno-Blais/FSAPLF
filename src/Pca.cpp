/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : pca.cpp
*
*   Description :   Container class for the principal component analysis
*
*******************************************************************************************/


//*******************
//  GENERAL INCLUDES
//*******************
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

/********************
* HEADER INCLUDES
********************/
#include "Pca.h"
#include "nr3.h"
#include "eigen_sym.h"
#include "calc.h"

#define PI 3.14159265359
#define WIDTH 12
#define PRES 7

Pca::Pca() 
{
    //Default values
    x0_  =NULL;
    x_   =NULL;
    link_=NULL;
    ids_ =NULL;
    np0_=0;
    np_=0;
    it_=0;
    enabled_=false;
    type_="";
    it0_=0;
}

Pca::~Pca()
{
}


void Pca::initialise()
{



}


void Pca::manage(int iter, int np, int* id, double** x)
{
    // If zeroth iteration has already been set, normal analysis
    if (enabled_)
    {
            analyse(np,x);
    }
    else
    {
        if (iter==it0_ )
        {
            setZeroth(np,id,x);
        }
    }
}

void Pca::setZeroth(int np,int* id, double **x)
{
    enabled_=true;
    np_=np;
    np0_=np;
    
    //Allocate memory for x0_ and x_
    x0_ = new double*[3];
    x_ = new double*[3];
    x0t_ = new double*[3];
    link_ = new int[np0_];

    for (int i=0 ; i<3 ; i++)
    {
        x0_[i] = new double[np0_];
        x_[i] = new double[np0_];
        x0t_[i] = new double[np0_];
    }
    setParticlePositions(np,x,x0_);

    //Create link table

}

void Pca::setParticlePositions(int np, double** x, double** xp)
{
    double temp[3];

    if(type_==string("cylindrical") || type_==string("Cylindrical"))
    {
        for (int i=0 ; i< np0_ ; i++)
        {
            calcCyl(temp,x[i]);
            for (int j=0 ; j<3 ; j++) xp[j][i] = temp[j]; 
        }
    }
    else if(type_==string("cartesian") || type_==string("Cartesian"))
    {
        //Cartesian coordinates are stored, this is just a copy operation
        for (int i=0 ; i<np0_ ; i++)
        {
            for (int j=0 ; j<3 ; j++) xp[j][i] = x[i][j];
        }
    }
}


void Pca::analyse(int np, double** x)
{
    MatDoub c(3,3);
/*
    if (np != np0_) std::cerr << "Invalid data file, number of particles was not kept constant preventing PCA" << endl;

    for (int i=0 ; i < 3; i++)
    {
        for (int j=0 ; j < 3; j++)
        {
        }
    }

    c[0][0] = calcCij(np,x0[0],x[0]);
    c[0][1] = calcCij(np,x0[0],x[1]);
*/


   /*
    m[0][0]=1;
    m[0][1]=2;
    m[0][2]=3;
    m[1][0]=2;
    m[1][1]=3;
    m[1][2]=2;
    m[2][0]=3;
    m[2][1]=2;
    m[2][2]=5;

    Jacobi jac(m);


    VecDoub eigi=jac.d;

    for (int i=0; i<eigi.size() ; i++)
    {
        std::cout << jac.d[i] <<std::endl;
    }

    std::cout<<"eigen vectors:" << std::endl;
    MatDoub eigv=jac.v;

    for (int i=0; i<eigv.nrows() ; i++)
    {
        for (int j=0; j<eigv.ncols() ; j++)
        {
            std::cout<<eigv[i][j] << " " ;
        }
        std::cout<<endl;
    }
    */
}




/*
   void plane::set(int planeType, int planeAxis, int planeNumber)
   {
   x_=NULL;
   r_=NULL;
   planeType_ = planeType;
   planeAxis_ = planeAxis;
   planeNumber_ = planeNumber;
   voidfraction_ = new double[planeNumber_];
   pos_ = new double[planeNumber_];
   }

   void plane::setParticles(double* r, double** x)
   {
   r_=r;
   x_=x;
   }

   void plane::setDimensions(double l)
   {
   dimensions_[0]=l;
   }

   void plane::setDimensions(double l, double w)
   {
    dimensions_[0]=l;
    dimensions_[1]=w;
}

void plane::setLength(double bottom, double top)
{
    length_[0]=bottom;
    length_[1]=top;
}

void plane::setNumber(int np)
{
    np_=np;
}

void plane::print()
{
}

double plane::planeVoidFraction(int axis, double h)
{
    // Calculate the void fraction on a given plane
    // axis is the vector normal to the plane, it can either be : 0-x 1-y 2-z
    // h is the position on axis of the plane
    // function returns the Area of sphere on that plane
    double x=0;
    double r=0;
    double r2s=0;
    double area=0;

    for (int i=0 ; i< np_ ; i++)
    {
	x = x_[i][axis];
	r = r_[i];
	if (((( x+r > h ) && ( x-r > h)) || ((x+r<h) && (x-r<h))) == false)
	{
	    //Particle crosses the plane
	    r2s = r*r-(x-h)*(x-h);
	    area += PI *r2s;
	}
    }

    return area;
}

void plane::write(std::string path, std::string label, int nit)
{
    std::string filename = path+"/"+label+"_plane_"+writingIntToString(nit);
    std::ofstream ficOut(filename.c_str());
    for (int i=0 ; i<planeNumber_ ; i++)
    {
	ficOut	<< std::setw(WIDTH) << std::setprecision(PRES) << pos_[i] << " "  
		<< std::setw(WIDTH) << std::setprecision(PRES) << voidfraction_[i] << " "
		<< std::endl;
    }
    ficOut.close();
}

//Accesssors
int plane::getType(){return planeType_;}
int plane::getAxis(){return planeAxis_;}
int plane::getNumber(){return planeNumber_;}
*/
