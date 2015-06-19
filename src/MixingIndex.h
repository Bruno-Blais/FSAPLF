/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : MixingIndex.h
*
*   Description :   Container class for mixing index analysis
*                   Types are available:
*                       - Cartesian (x,y,z)
*                       - fullCylindrical (r,theta,z)
*                       - Cylindrical (r,z) -> not very useful
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

#ifndef MIXINGINDEX_H
#define MIXINGINDEX_H 

class MixingIndex
{
private :
    bool enabled_;                      // If it0 has been reached or not
    std::string type_;  	    	// Type of MixingIndex
    int	np0_;				// Initial number of particles
    int	np_;				// Number of particles - allows to loop over the arrays
    int it0_;                           // Reference iteration number
    int it_;                            // Current iteration number
    double** x0_;  			// Original position stored in reversed format
    double** x0t_;                      // Zeroth position with id order of current positions
    double** x_;                        // Current position storede in reversed format
    int* link_;                         // List linking an ID to the x0 table
    int* id_;                           // List of the particle ids
    MatDoub eigv_;                      // EigvenVectors
    MatDoub eig_;                       // Eigenvalues
    VecDoub iter_;                      // Label of iterations
    int  nIter_;                        // Number of iterations

public :
    MixingIndex(int, char**,int);
    ~MixingIndex();

    void print();				        // Print content of the class
    void analyse(double**);		                // Carry the analysis
    void manage(int,int,int*,double**);                 // API for the whole pca analysis
    void initialise();                                  // Initialise the data to know which iteration is zeroth
    void setZeroth(double **);                          // Set zeroth values
    void write(std::string, std::string);	        // Write the results to a file
    void enable();                                      // Start PCA analysis
    void setParticlePositions(double**,double**);       // Transform particle position to 3xnp array format
    void allocate(int);                                 // Allocate memory to store the eigenvalues and vectors
    void debugStatistic();                              // Print information about statistic if debugging

    //Accessors functions
    int getType();
    bool isEnabled() {return enabled_;} ;
};
#endif
