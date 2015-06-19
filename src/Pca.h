/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : pca.h
*
*   Description :   Container class for principal component analysis
*                   PCA types are available:
*                       - Cartesian (x,y,z)
*                       - Cylindrical (r,theta,z)
*
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

#ifndef PCA_H
#define PCA_H 

class Pca
{
private :
    bool enabled_;                      // If it0 has been reached or not
    std::string type_;  	    	// Type of PCA analysis, most likely will only be one
    int	np0_;				// Initial number of particles
    int	np_;				// Number of particles 
    int it0_;                           // Reference iteration number
    int it_;                            // Current iteration number
    int nIter_;                         // Number of iterations
    int nSample_;                       // Number of particles to consider in PCA analysis
    string label_;                      // Label for the outname of the PCA
    string path_;                       // Path of the outputs
    double** x0_;  			// Original position stored in reversed format
    double** x0t_;                      // Zeroth position with id order of current positions
    double** x_;                        // Current position stored in reversed format
    int* link_;                         // List linking an ID to the x0 table
    int* id_;                           // List of the particle ids

public :
    Pca(int, char**);
    ~Pca();

    void print();				        // Print content of the class
    void analyse(double**);		                // Carry the analysis
    void manage(int,int,int*,double**);                 // API for the whole pca analysis
    void initialise();                                  // Initialise the data to know which iteration is zeroth
    void setZeroth(double **);                          // Set zeroth values
    void write(VecDoub, MatDoub);	        // Write the results to a file
    void enable();                                      // Start PCA analysis
    void setParticlePositions(double**,double**);       // Transform particle position to 3xnp array format

    //Accessors functions
    int getType();
    bool isEnabled() {return enabled_;} ;
};
#endif
