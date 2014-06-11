// Last Modified: Wed 11 Jun 2014 04:36:15 PM EDT
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
*			- Plane porosity profiles
*			- Cylidnrical porosity profiles
*
********************************************************************************************/

#include <string>
#include <boost/filesystem.hpp>

#ifndef OPTIONS_H
#define OPTIONS_H 

namespace fs = boost::filesystem;

typedef std::vector<fs::path> vecPath; 

class options
{
private :
    bool averaging_;			// Enables per iteration averaging
    bool trajectories_;			// Enables storage of the particle trajectories
    bool vPlane_;			// Enables planes of porosity
    bool cPlane_;			// Enables radial planes of porosity
    std::string informat_;		// Input format form
    std::string path_;			// Path of the folder to post-process
    std::string extension_;		// Extension that is considered in the dump file analysis
    vecPath filesPath_;			// Individual paths to each files

public :
    options();
    void getFilesIdentification();
    void setMode(int argc , char* argv[]);
};

void listdir(char *);
#endif
