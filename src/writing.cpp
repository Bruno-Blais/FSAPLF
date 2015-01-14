/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : writingTools.cpp
*
*   Description :   Contains numerous functions to help such as conversion in writing.
*
*******************************************************************************************/


//*******************
//  GENERAL INCLUDES
//*******************
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

/********************
* HEADER INCLUDES
********************/

#define PI 3.14159265359
#define WIDTH 12
#define PRES 7

std::string writingIntToString(int number)
{
   std::stringstream ss;    //create a stringstream
   ss << number;	    //add number to the stream
   return ss.str();	    //return a string with the contents of the stream
}

std::string writingDoubleToString(double number)
{
   std::stringstream ss;    //create a stringstream
   ss << number;	    //add number to the stream
   return ss.str();	    //return a string with the contents of the stream
}
