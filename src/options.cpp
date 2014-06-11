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

//General Includes
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/filesystem.hpp>
#include <iterator>
#include <vector>
#include <algorithm>


#include "options.h"

namespace fs = boost::filesystem;
using namespace std;

options::options()
{
    averaging_=false;
    trajectories_=false;
    vPlane_=false;
    cPlane_=false;
    path_="./";		    // Default path is directory of the executable
    extension_=".dump";
    informat_="LIGGGHTS";
}


void options::setMode(int argc , char* argv[])
{
    std::string arg;
    int i=1;

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
	else if("-ext" == arg)
	{
	    extension_ = argv[i+1];
	    std::cout << "Extensions considered : " << extension_ << std::endl; 
	    i+=2;
	}
	else if ("-informat" == arg)
	{
	    informat_ = argv[i+1];
	    std::cout << "Input format : " << informat_ << std::endl; 
	    i+=2;
	}
	else
	{
	    std::cout << "Option " << arg << " is not available" << std::endl;
	    i++;
	}
    }
}

void options::getFilesIdentification()
{
   
    // Find the number of pertinent file in the directory in order to take care of memory allocation
    // This was noticeably simpler in python. Here we use the Boost library in order to simplify
    // interactions with the OS
    int ending;
    bool erase = false;
    string local;
    fs::path p (path_);
    
    if (fs::exists(p))    // does p actually exist?
    {
	if (fs::is_directory(p))      
	{
	    std::cout << p << " is a directory containing:\n";

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
	    }
	}
	else
	std::cout << p << " is not a directory" << std::endl;
    }
    else
	std::cout << p << " does not even exit ??? what is wrong with you anyway?" << std::endl;

}

