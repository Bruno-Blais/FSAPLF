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
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include "Steps.h"
#include "plane.h"

#ifndef OPTIONS_H
#define OPTIONS_H


namespace fs = boost::filesystem;

typedef std::vector<fs::path> vecPath; 

class options
{
private :
    bool averaging_;		    // Enables per iteration averaging
    bool trajectories_;		    // Enables storage of the particle trajectories
    bool planeOn_;		    // Enables planes of porosity
    bool batch_;		    // Enables a batch treatment of data and flushing out of data
    bool pca_;                      // Enables principal component analysis
    bool mixingIndex_;              // Enables Mixing Index analysis (Doucet et al. 2008)
    
    double dt_;			    // Timestep

    std::string caseLabel_;	    // Label to give to the post-processing of the information
    std::string path_;		    // Path of the folder to post-process
    std::string optionsPath_;	    // Path of the option files
    std::string outputPath_;	    // Path of the folder where to put the output files
    std::string extension_;	    // Extension that is considered in the dump file analysis
    vecPath filesPath_;		    // Individual paths to each files
    int nFiles_;		    // Number of files
    int batchFreq_;		    // Frequency of memory flushing for batch process
    std::string pcaType_;           // Type of PCA analysis
    int    pcaIt0_;                 // Initial iteration of PCA
    
    // Informations about planes
    plane plane_;

    // Information about trajectories
    int trajectoriesType_;

public :
    options(int,char**);
    ~options();
    void getFilesIdentification();
    void setMode(int argc , char* argv[]);
    void setSteps (Steps*);

    //Accessors
    bool getAveraging();
    bool getPlaneOn();
    bool getTrajectories();
    bool getPca();
    bool getMixingIndex();
    int getTrajectoriesType();
    int getNumberOfFiles();	    // Accessor for the number of files
    int getBatchFreq();
    double getDt();
    std::string getLabel();
    std::string getPath();
    std::string getOutputPath();

    plane getPlane();




};
#endif
