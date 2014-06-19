// Last Modified: Fri 13 Jun 2014 11:49:13 AM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : averaging.h
*
*   Description : Container class for all the averaged properties of all files
*
*******************************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

#ifndef BOXES_H
#define BOXES_H 

class boxes
{
private :
    int	type_;			// 0. Carthesian 1. Cylindrical
    std::vector<double> x_;	// Dimension container

public :
    boxes();
    ~boxes();
};
#endif
