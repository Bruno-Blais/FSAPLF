// Last Modified: Thu 12 Jun 2014 02:57:00 PM EDT
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
#include "steps.h"

#ifndef OPTIONS_H
#define OPTIONS_H 

namespace fs = boost::filesystem;

typedef std::vector<fs::path> vecPath; 

class options
{
private :
    bool averaging_;		    // Enables per iteration averaging
    bool trajectories_;		    // Enables storage of the particle trajectories
    bool vPlane_;		    // Enables planes of porosity
    bool cPlane_;		    // Enables radial planes of porosity
    bool batch_;		    // Enables a batch treatment of data and flushing out of data
    std::string path_;		    // Path of the folder to post-process
    std::string extension_;	    // Extension that is considered in the dump file analysis
    vecPath filesPath_;		    // Individual paths to each files
    int nFiles_;		    // Number of files
    int batchFreq_;		    // Frequency of memory flushing for batch process

public :
    options(int,char**);
    void getFilesIdentification();
    void setMode(int argc , char* argv[]);
    int getNumberOfFiles();	    // Accessor for the number of files
    void setSteps (steps*);
    bool getAveraging();
};
#endif
