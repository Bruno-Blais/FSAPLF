// Last Modified: Fri 13 Jun 2014 11:51:00 AM EDT
/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : averaging.cpp
*
*   Description :   Contains the averaged properties for all files
*
*******************************************************************************************/

//*******************
//  GENERAL INCLUDES
//*******************
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

/********************
* HEADER INCLUDES
********************/
#include "boxes.h"

#define LARGE 999999

boxes::boxes() : x_(6)
{
    for (int i =0 ; i <6 ; i=i+2)
    {
	x_[i]=-LARGE;
	x_[i+1]=LARGE;
    }
}
