// Last Modified: Tue 10 Jun 2014 11:56:33 AM EDT
/*******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : options.h
*
*   Description :   Routines for parsing the various options related to post-processing
*		    Available options :
*
*		    In developement :
*			- Per iteration averaging
*			- Individual particles trajectories with deterministic or random sampling
*
*
********************************************************************************************/

#include <string>

#ifndef OPTIONS_H
#define OPTIONS_H 

class options
{
private :
    bool averaging_;		    // Enables per iteration averaging
    std::string* quantitiesAveraged_;    // String container for the different quantities read from the files
    bool trajectories_;		    // Enables storage of the particle trajectories
    bool vPlane_;		    // Enables planes of porosity
    bool cPlane_;		    // Enables radial planes of porosity
public :
    void setMode(int argc , char* argv[]);
};
#endif
