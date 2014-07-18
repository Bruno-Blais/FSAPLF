// Last Modified: Wed 02 Jul 2014 05:10:40 PM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : trajectories.h
*
*   Description :   Container class to establish trajectories for individual particles
*
*		    Type of trajectories:
*			1- Trajectories are stored for all particles
*			2- 
*
*******************************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

#ifndef TRAJECTORIES_H
#define TRAJECTORIES_H 

class trajectories
{
private :
    int			type_;	    // Type of trajectory storage    
    int			ntrj_;	    // Number of trajectories
    int			nit_;	    // Number of iterations
    int*		nIter_;	    // Number of EACH iteration
    std::vector<int>    ids_;	    // Ids of the tracked particles
    double**		x_;	    // Positions vector
    double**		y_;	
    double**		z_;	

public :
    trajectories();
    ~trajectories();
    void allocate(int,int,int, std::vector<int>);
    void setStep(int,int,std::vector<int>,double**);
    void writeFile(std::string, std::string, std::string);

    // Accessors
    int getNumberTrajectories();
    std::vector<int> getIds();

};
#endif
