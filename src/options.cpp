/*******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : options.cpp
*
*   Description :   Routines for parsing the various options related to post-processing
*		    Available options :
*
*
********************************************************************************************/

/******************
* General Includes
*******************/
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/filesystem.hpp>
#include <iterator>
#include <vector>
#include <algorithm>

/********************
* HEADER INCLUDES
********************/
#include "options.h"
#include "steps.h"

namespace fs = boost::filesystem;
using namespace std;

options::options(int argc , char* argv[])
{
    std::string arg;
    int i=1;

    //Default constructor
    averaging_=false;
    trajectories_=false;
    vPlane_=false;
    cPlane_=false;
    batch_=false;	    
    batchFreq_=999999;  
    path_="./";		    // Default path is directory of the executable
    extension_=".dump";	    // Default extension name
    

    //Parse the options from the terminal to know which mode to enable
    while (i<argc)
    {
	arg = argv[i];
	if ("-average" == arg)
	{
	    std::cout << "Averaging enabled" << std::endl;
	    averaging_=true;
	    i++;
	}
	else if ("-trajectory" == arg )
	{
	    std::cout << "Trajectories enabled" << std::endl;
	    trajectories_=true;
	    i++;
	}
	else if ("-cplane" ==arg)
	{
	    std::cout << "Cylindrical porosity analysis enabled" << std::endl;
	    cPlane_=true;
	    i++;
	}
	else if ("-zplane" ==arg)
	{
	    std::cout << "Vertical porosity analysis enabled" << std::endl;
	    vPlane_=true;
	    i++;
	}
	else if ("-path" == arg)
	{
	    path_ = argv[i+1];
	    std::cout << "Dumps path : " << path_ << std::endl; 
	    i+=2;
	}
	else if ("-ext" == arg)
	{
	    extension_ = argv[i+1];
	    std::cout << "Extensions considered : " << extension_ << std::endl; 
	    i+=2;
	}
	else if ("-batch" == arg)
	{
	    batchFreq_ = atoi(argv[i+1]);
	    std::cout << "Extensions considered : " << extension_ << std::endl; 
	    i+=2;
	}
	else
	{
	    std::cout << "Option " << arg << " is not available" << std::endl;
	    i++;
	}
    }
}

options::~options()
{
    std::cout << "Trying to destroy the options ? " << std::endl;
    filesPath_.clear();
}

void options::getFilesIdentification()
{
   
    // Find the number of pertinent file in the directory in order to take care of memory allocation
    // This was noticeably simpler in python. Here we use the Boost library in order to simplify
    // interactions with the OS
    string local;
    fs::path p (path_);
    nFiles_=0;
    
    if (fs::exists(p))    // does p actually exist?
    {
	// Test the validity of the path
	if (fs::is_directory(p))      
	{
	    std::cout << p << " is a valid directory\n";

	    copy(fs::directory_iterator(p), fs::directory_iterator(), back_inserter(filesPath_));

	    sort(filesPath_.begin(), filesPath_.end());             // sort, since directory iteration is not ordered

	    //Loop trough the vector to remove files that do not end in EXTENSION 
	    vecPath::iterator it(filesPath_.begin());
	    vecPath::iterator prev;
	    while (it<filesPath_.end())
	    {	
		local = it->string();
		if (local.compare(local.size()-extension_.size(),extension_.size(),extension_) != 0)  
		{
		    //Incrementing here will cause us to skip the next file, no incrementation
		    filesPath_.erase(it);
		}
		else 
		{
		    it++;
		}
	    }

	    it=filesPath_.begin();
	    std::cout << "Files taken into account are : " << std::endl;
	    while (it<filesPath_.end())
	    {
		cout << it->string() << std::endl;
		it++;
		nFiles_++;
	    }
	}
	else
	std::cout << p << " is not a directory" << std::endl;
    }
    else
	std::cout << p << " does not even exit ??? what is wrong with you anyway?" << std::endl;

}

int options::getNumberOfFiles()
{
    return nFiles_;
}

bool options::getAveraging()
{
    return averaging_;
}

void options::setSteps(steps* stp)
{
    //This function sets the individual information for each time step in the steps object
    for (int i = 0 ; i < nFiles_ ; i++)
    {
	stp[i].setPath(filesPath_[i].string());
	stp[i].setNumber(i);
    }
}

