/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : pca.cpp
*
*   Description :   Container class for the principal component analysis to obtain mixing
*                   index
*
*******************************************************************************************/


/*********************
*  GENERAL INCLUDES
*********************/
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
#define WIDTHOUT 16
#define WIDTH   30
#define WIDTH2  32
#define PRES 7
#define DEBUG 1

Pca::Pca(int argc, char* argv[]) 
{
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
            nSample_=atoi(argv[i+3]); // TODO Right nSample is overwritten with the number of particles 
	    std::cout << std::setw(WIDTH)  <<  "PCA analysis" << ": Enabled" << std::endl;
	    std::cout << std::setw(WIDTH2)  <<  "Type : " << type_ << std::endl;
            i+=4;
        }
	if ("-out" ==arg)
	{
	    path_ = argv[i+1];
	    i ++;
	}
        if ("-label" == arg)
	{
	    label_ = argv[i+1];
	    i++;
	}
        else
        {
            i++;
        }
    }
}

Pca::~Pca()
{
}

void Pca::manage(int iter, int np, int* id, double** x)
{
    id_=id; //attribute array;
    it_=iter;
    np_=np;

    // If zeroth iteration has already been set, normal analysis
    if (enabled_ && iter>it0_)
    {
            if (DEBUG) std::cout << "Beggining analysis" << std::endl;
            analyse(x);
    }
    else
    {
        if (DEBUG) std::cout << " Iter : " << iter << " Required iter : " << it0_ << std::endl;
        if (iter==it0_ )
        {
            if (DEBUG) std::cout << "Setting zeroth iteration" << std::endl;
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
    link_ = new int[2*np0_]; //link table is buffered up to allow for the case where particles changed

    for (int i=0 ; i<3 ; i++)
    {
        x0_[i] = new double[2*np0_];
        x_[i] = new double[2*np0_];
        x0t_[i] = new double[2*np0_];
    }

    //Create link table
    for (int i=0 ; i <np0_ ; i++) 
    {
        link_[id_[i]]=i;
        if (DEBUG && id_[i]>2*np0_) std::cout<< id_[i] << endl;
    }

    setParticlePositions(x,x0_);
}

void Pca::setParticlePositions(double** x, double** xp)
{
    //Cartesian coordinates are stored, this is just a copy operation
    for (int i=0 ; i<np0_ ; i++)
    {
        for (int j=0 ; j<3 ; j++) xp[j][i] = x[i][j];
    }
}

void Pca::analyse(double** x)
{
    int ii;
    int jj;
    
    if (DEBUG) std::cout << "Setting the position of the particles in the right arrangement" << std::endl;

    setParticlePositions(x,x_);

    if (DEBUG) std::cout << "Current number of particles is : " << np_ << " Initial number was : " << np0_ << std::endl;
    
    // Sanity check
    if (np_ != np0_) std::cerr << "Invalid data file, number of particles was not kept constant preventing PCA" << endl;

    //Reallign array with current one in terms of particle Ids
    for (int i=0 ; i < np0_ ; i++)
    {
        x0t_[0][i] = x0_[0][link_[id_[i]]];
        x0t_[1][i] = x0_[1][link_[id_[i]]];
        x0t_[2][i] = x0_[2][link_[id_[i]]];
    }

    if (DEBUG) std::cout << "Reallignment success..." << std::endl;
    MatDoub c;
    MatDoub cT;
    MatDoub m;

    // --- Actually this is just the general 3D case...
    // Solution in x y z plane
    c.resize(np0_*3,np0_*3);
    cT.resize(np0_*3,np0_*3);
    m.resize(np0_*3,np0_*3);

    if (DEBUG) std::cout << "Matrix resizing is over..." << std::endl;

    for (int i=0 ; i<np0_; i++)
    {
        for (int j=0 ; j<np0_; j++)
        {
            for (int k=0 ; k<3 ; k++)
            {
                ii = (i*3)+k;
                jj= (j*3)+k;
                c[ii][jj] = x0t_[k][i]*x_[k][j];
            }
        }
    }

    if (DEBUG) std::cout <<"C matrix has been built..." <<std::endl;

    cT=calcMatTranspose(c);

    if (DEBUG) std::cout <<"C matrix has been transposed..." << std::endl;
    
    m=calcMatMult(c,cT); 

    if (DEBUG) std::cout << "Symmetric matrices built..." << std::endl;

/*
    if(DEBUG)
    {
        calcPrintMat(c,"C");
        calcPrintMat(cT,"CT");
        calcPrintMat(m,"M");
    }
*/

    //Instantiate Jacobi method to solve eigenvalues problem
    Jacobi jac(m);

    if(DEBUG) std::cout <<"Jacobi system has been solved" << std::endl;

    //VecDoub eig(jac.d);
    //MatDoub eigv(jac.v);
    
    write(jac.d,jac.v);
}

void Pca::write(VecDoub eig, MatDoub eigv)
{
    std::string filename = path_+"/"+label_+"_pca_"+std::string(std::to_string(it_));
    std::ofstream ficOut(filename.c_str());

    ficOut	
        << std::setw(WIDTHOUT) << "L" 	    
        << std::setw(WIDTHOUT) << "V" 	
        << std::endl;

    if(DEBUG) std::cout <<"Size of eigv_ is : " << eigv.nrows() << " " << eigv.ncols() << std::endl;
        
    for (int i=0 ; i<eigv.nrows() ; i++)
    {
        ficOut << std::setw(WIDTHOUT) << std::setprecision(PRES) << eig[i]; 
        for (int j=0 ; j<eigv.ncols() ; j++) ficOut << std::setw(WIDTHOUT) << std::setprecision(PRES) << eigv[i][j];
        ficOut << std::endl;
    }
    ficOut.close();
}
