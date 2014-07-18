// Last Modified: Wed 02 Jul 2014 11:48:48 AM EDT
/*******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : terminal.h
*
*   Description : Container for all the terminal interaction in the code
*
********************************************************************************************/

#ifndef TERMINAL_H
#define TERMINAL_H 

void terminalInit();
void terminalProgressInit(int);
void terminalProgress(int);
void terminalClose();

#endif

