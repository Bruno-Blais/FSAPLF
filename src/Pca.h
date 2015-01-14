/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : pca.h
*
*   Description :   Container class for principal component analysis
*                   PCA options are available:
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

#ifndef PCA_H
#define PCA_H 

class Pca
{
private :
    bool enabled_;                      // If it0 has been reached or not
    std::string type_;  	    	// Type of PCA
    int	np0_;				// Initial number of particles
    int	np_;				// Number of particles - allows to loop over the arrays
    int it0_;                           // Reference iteration number
    int it_;                            // Current iteration number
    double** x0_;  			// Original position stored in reversed format
    double** x0t_;                      // Zeroth position with id order of current positions
    double** x_;                        // Current position storede in reversed format
    int* link_;                         // List linking an ID to the x0 table
    int* ids_;                          // List of the particle ids

public :
    Pca();
    ~Pca();

    void print();				        // Print content of the class
    void analyse(int, double**);		        // Carry the analysis
    void manage(int,int,int*,double**);                 // API for the whole pca analysis
    void initialise();                                  // Initialise the data to know which iteration is zeroth
    void setZeroth(int,int*, double **);                // Set zeroth values
    void write(std::string, std::string, int);	        // Write the results to a file
    void enable();                                      // Start PCA analysis
    void setParticlePositions(int,double**,double**);    // Transform particle position to 3xnp array format

    //Accessors functions
    int getType();
    bool isEnabled() {return enabled_;} ;
};
#endif
