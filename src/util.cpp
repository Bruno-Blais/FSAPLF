/******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : util.cpp
*
*   Description :   Container for some utilities re-used within classes
*
*******************************************************************************************/

//*******************
//  GENERAL INCLUDES
//*******************
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

/********************
* HEADER INCLUDES
********************/
#include "util.h"

std::string utilLowerStr(string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
