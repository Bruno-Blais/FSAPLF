/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : MixingIndex.cpp
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
#include "MixingIndex.h"
#include "nr3.h"
#include "eigen_sym.h"
#include "calc.h"
#include "writing.h"

#define PI 3.14159265359
#define WIDTHOUT 16
#define WIDTH   30
#define WIDTH2  32
#define PRES 7
#define DEBUG 0

MixingIndex::MixingIndex(int argc, char* argv[], int nSteps) 
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
        if ("-mixingIndex" ==arg)
        {
            type_=string(argv[i+1]);
            it0_=atoi(argv[i+2]);
	    std::cout << std::setw(WIDTH)  << "Mixing index analysis" << ": enabled" << std::endl;
	    std::cout << std::setw(WIDTH2) << "Type: " << type_ << std::endl;
            i+=3;
        }
        else
        {
            i++;
        }
    }
    allocate(nSteps);
}

MixingIndex::~MixingIndex()
{
}

void MixingIndex::allocate(int n)
{
    //Allocate local memory for the information about the averages
    nIter_ = 0;
    iter_.resize(n);
    eigv_.resize(n,9);
    eig_.resize(n,3);
}


void MixingIndex::manage(int iter, int np, int* id, double** x)
{
    id_=id; //attribute array;
    np_=np;

    // If zeroth iteration has already been set, normal analysis
    if (enabled_ && iter>it0_)
    {
            if (DEBUG) std::cout << "Beggining analysis" << std::endl;
            iter_[nIter_]=iter;
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

void MixingIndex::setZeroth(double **x)
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

void MixingIndex::setParticlePositions(double** x, double** xp)
{
    double temp[3];


    if(type_==string("fullCylindrical") || type_==string("FullCylindrical"))
    {
        for (int i=0 ; i< np0_ ; i++)
        {
            calcCyl(temp,x[i]);
            for (int j=0 ; j<3 ; j++) xp[j][i] = temp[j]; 
        }
    }
    
    else if(type_==string("cylindrical") || type_==string("Cylindrical"))
    {
        for (int i=0 ; i< np0_ ; i++)
        {
            calcCyl(temp,x[i]);
            xp[0][i]=temp[0];
            xp[1][i]=temp[2];
            xp[2][i]=temp[1];
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

void MixingIndex::analyse(double** x)
{
    setParticlePositions(x,x_);

    if (DEBUG) std::cout << "Current number of particles is : " << np_ << " Initial number was : " << np0_ << std::endl;

    //Reallign array with current one in terms of particle Ids
    for (int i=0 ; i < np0_ ; i++)
    {
        x0t_[0][i] = x0_[0][link_[id_[i]]];
        x0t_[1][i] = x0_[1][link_[id_[i]]];
        x0t_[2][i] = x0_[2][link_[id_[i]]];
    }

    if (DEBUG) std::cout << "Reallignment success" << std::endl;
    if (np_ != np0_) std::cerr << "Invalid data file, number of particles was not kept constant preventing PCA" << endl;
    MatDoub c;
    MatDoub cT;
    MatDoub m;



    // --- Cylindrical coordinates
    // projection of the mixing index in the r and z subsspace
    // Actually this seems like the generic 2D case in a way
    if(type_==string("cylindrical") || type_==string("Cylindrical"))
    {
        c.resize(2,2);
        cT.resize(2,2);
        m.resize(2,2);

        for (int i=0 ; i < 2; i++)
        {
            for (int j=0 ; j < 2; j++)
            {
                c[i][j] = calcCij(np_,x0t_[j],x_[i]);
            }
        }

        cT=calcMatTranspose(c);
        m=calcMatMult(c,cT); 

        //Instantiate Jacobi method to solve eigenvalues problem
        Jacobi jac(m);

        // extract eigen values and eigenvectors
        VecDoub eig=jac.d;
        MatDoub eigv=jac.v;

        for (int i =0 ; i <eig.size() ; i++)
        {
            eig_[nIter_][i] = eig[i];
        }
        eig_[nIter_][2]=0;

        for (int i =0 ; i <eigv.ncols() ; i++)
        {
            for (int j =0 ; j <eigv.nrows() ; j++) 
            {
                eigv_[nIter_][3*i+j] = eigv[j][i];
            }
            eigv_[nIter_][3*i+2]=0.;
        }
    }

    // --- Cartesian coordinates or full cylindrical coordinates
    // --- Actually this is just the general 3D case...
    // Solution in x y z plane
    else if(type_==string("cartesian")       || type_==string("Cartesian") ||
            type_==string("fullCylindrical") || type_==string("FullCylindrical")  )
    {
        c.resize(3,3);
        cT.resize(3,3);
        m.resize(3,3);

        for (int i=0 ; i < 3; i++)
        {
            for (int j=0 ; j < 3; j++)
            {
                c[i][j] = calcCij(np_,x0t_[j],x_[i]);
            }
        }

        cT=calcMatTranspose(c);
        m=calcMatMult(c,cT); 

        if(DEBUG)
        {
            calcPrintMat(c,"C");
            calcPrintMat(cT,"CT");
            calcPrintMat(m,"M");
            debugStatistic();
        }

        //Instantiate Jacobi method to solve eigenvalues problem
        Jacobi jac(m);


        // extract eigen values and eigenvectors
        VecDoub eig=jac.d;
        MatDoub eigv=jac.v;

        for (int i =0 ; i <eig.size() ; i++)
        {
            eig_[nIter_][i] = eig[i];
        }

        for (int i =0 ; i <eigv.ncols() ; i++)
        {
            for (int j =0 ; j <eigv.nrows() ; j++) 
            {
                eigv_[nIter_][eigv.nrows()*i+j] = eigv[j][i];
            }
        }
    }
    
    //Increment number of stored iterations
    nIter_++;
}

void MixingIndex::debugStatistic()
{
    std::cout<< "x0 Mean: " << calcMean(np_,x0t_[0])<<std::endl; 
    std::cout<< "x0 Mean: " << calcMean(np_,x0_[0])<<std::endl;
    std::cout<< "x0 Mean: " << calcMean(np_,x_[0])<<std::endl;
    std::cout<< "y0 Mean: " << calcMean(np_,x0t_[1])<<std::endl; 
    std::cout<< "y0 Mean: " << calcMean(np_,x0_[1])<<std::endl;
    std::cout<< "y0 Mean: " << calcMean(np_,x_[1])<<std::endl;
    std::cout<< "z0 Mean: " << calcMean(np_,x0t_[2])<<std::endl; 
    std::cout<< "z0 Mean: " << calcMean(np_,x0_[2])<<std::endl;
    std::cout<< "z0 Mean: " << calcMean(np_,x_[2])<<std::endl;

    std::cout<< "x0 StdDev: " << calcStdDev(np_,x0t_[0])<<std::endl; 
    std::cout<< "x0 StdDev: " << calcStdDev(np_,x0_[0])<<std::endl;
    std::cout<< "x0 StdDev: " << calcStdDev(np_,x_[0])<<std::endl;
    std::cout<< "y0 StdDev: " << calcStdDev(np_,x0t_[1])<<std::endl; 
    std::cout<< "y0 StdDev: " << calcStdDev(np_,x0_[1])<<std::endl;
    std::cout<< "y0 StdDev: " << calcStdDev(np_,x_[1])<<std::endl;
    std::cout<< "z0 StdDev: " << calcStdDev(np_,x0t_[2])<<std::endl; 
    std::cout<< "z0 StdDev: " << calcStdDev(np_,x0_[2])<<std::endl;
    std::cout<< "z0 StdDev: " << calcStdDev(np_,x_[2])<<std::endl;
        
}

void MixingIndex::write(std::string path, std::string label)
{
    std::string filename = path+"/"+label+"_mixingIndex";
    std::ofstream ficOut(filename.c_str());

    ficOut	<< std::setw(WIDTHOUT) << "iter " 
        << std::setw(WIDTHOUT) << "L1 " 	    
        << std::setw(WIDTHOUT) << "L2 " 	
        << std::setw(WIDTHOUT) << "L3 " 	    
        << std::setw(WIDTHOUT) << "V1-1 " 	
        << std::setw(WIDTHOUT) << "V1-2 " 	    
        << std::setw(WIDTHOUT) << "V1-3 " 	
        << std::setw(WIDTHOUT) << "V2-1 " 	
        << std::setw(WIDTHOUT) << "V2-2 " 	    
        << std::setw(WIDTHOUT) << "V2-3 " 	
        << std::setw(WIDTHOUT) << "V3-1 " 	
        << std::setw(WIDTHOUT) << "V3-2 " 	    
        << std::setw(WIDTHOUT) << "V3-3 " 	
        << std::endl;

    for (int i=0 ; i<nIter_ ; i++)
    {
        ficOut << std::setw(WIDTHOUT);
	ficOut << std::setprecision(PRES);
	ficOut	<< iter_[i] << " " ;  
	for (int j=0 ; j<3 ; j++) ficOut << std::setw(WIDTHOUT) << std::setprecision(PRES) << eig_[i][j]  ;
        for (int j=0 ; j<9 ; j++) ficOut << std::setw(WIDTHOUT) << std::setprecision(PRES) << eigv_[i][j]  ;
	ficOut << std::endl;
    }
    ficOut.close();
}
