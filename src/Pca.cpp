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
#include "writing.h"

#define PI 3.14159265359
#define WIDTH   30
#define WIDTH2  31
#define PRES 7

Pca::Pca(int argc, char* argv[], int nSteps) 
{
    //Default values
    std::string arg;
    int i=0;
    x0_  =NULL;
    x_   =NULL;
    link_=NULL;
    id_ =NULL;
    np0_=0;
    np_=0;
    it_=0;
    enabled_=false;
    type_="";
    it0_=0;
    
    while (i<argc)
    {
        arg = argv[i];
        if ("-pca" ==arg)
        {
            type_=string(argv[i+1]);
            it0_=atoi(argv[i+2]);
	    std::cout << std::setw(WIDTH)  <<  "PCA analysis" << ": Enabled" << std::endl;
	    std::cout << std::setw(WIDTH2)  <<  "Types :\t" << "Cylindrical\t" << "Cartesian" << std::endl;
            i+=3;
        }
        else
        {
            i++;
        }
    }
    allocate(nSteps);
}

Pca::~Pca()
{
}

void Pca::allocate(int n)
{
    //Allocate local memory for the information about the averages
    nIter_ = 0;
    iter_.resize(n);
    eigv_.resize(n,9);
    eig_.resize(n,3);
}


void Pca::manage(int iter, int np, int* id, double** x)
{
    id_=id; //attribute array;
    np_=np;

    // If zeroth iteration has already been set, normal analysis
    if (enabled_ && iter>it0_)
    {
            analyse(x);
    }
    else
    {
        if (iter==it0_ )
        {
            setZeroth(x);
        }
    }
}

void Pca::setZeroth(double **x)
{
    enabled_=true;
    np0_=np_;
    
    //Allocate memory for x0_ and x_
    x0_ = new double*[3];
    x_ = new double*[3];
    x0t_ = new double*[3];
    link_ = new int[2*np0_]; //link table is buffered up to allow for the case where particle were lost

    for (int i=0 ; i<3 ; i++)
    {
        x0_[i] = new double[np0_];
        x_[i] = new double[np0_];
        x0t_[i] = new double[np0_];
    }

    //Create link table
    for (int i=0 ; i <np0_ ; i++) 
    {
        link_[id_[i]]=i;
        if (id_[i]>2*np0_) std::cout<< id_[i] << endl;
    }

    setParticlePositions(x,x0_);
}

void Pca::setParticlePositions(double** x, double** xp)
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

void Pca::analyse(double** x)
{
    setParticlePositions(x,x_);

    //Reallign array with current one in terms of particle Ids
    for (int i=0 ; i < np0_ ; i++)
    {
        x0t_[0][i] = x0_[0][link_[id_[i]]];
        x0t_[1][i] = x0_[1][link_[id_[i]]];
        x0t_[2][i] = x0_[2][link_[id_[i]]];
    }

    MatDoub c(3,3);
    MatDoub cT(3,3);
    MatDoub m(3,3);

    if (np_ != np0_) std::cerr << "Invalid data file, number of particles was not kept constant preventing PCA" << endl;

    for (int i=0 ; i < 3; i++)
    {
        for (int j=0 ; j < 3; j++)
        {
            c[i][j] = calcCij(np_,x0t_[i],x_[j]);
        }
    }

    cT=calcMatTranspose(c);
    m=calcMatMult(c,cT); 


    //Instantiate Jacobi method to solve eigenvalues problem
    Jacobi jac(m);

    VecDoub eig=jac.d;
    MatDoub eigv=jac.v;



    //Increment number of stored iterations
    nIter_++;
}

void Pca::write(std::string path, std::string label, int nit)
{
    std::string filename = path+"/"+label+"_plane_"+writingIntToString(nit);
    std::ofstream ficOut(filename.c_str());
    /*
    for (int i=0 ; i<planeNumber_ ; i++)
    {
	ficOut	<< std::setw(WIDTH) << std::setprecision(PRES) << pos_[i] << " "  
		<< std::setw(WIDTH) << std::setprecision(PRES) << voidfraction_[i] << " "
		<< std::endl;
    }
    */
    ficOut.close();
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



//Accesssors
int plane::getType(){return planeType_;}
int plane::getAxis(){return planeAxis_;}
int plane::getNumber(){return planeNumber_;}
*/
