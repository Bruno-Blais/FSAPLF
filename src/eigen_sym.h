/*******************************************************************************************
*
*   Framework for the Statistical Analysis of Particle-Laden Flows
*   
*   
*   Author  : Bruno Blais
*   File    : eigen_sym.h
*
*   Description :   Routines for calculating the eigenvalues of symmetric matrices
*                   Modified from the numerical recipee handbook
*
********************************************************************************************/

#ifndef EIGEN_SYM_H
#define EIGEN_SYM_H

#include "nr3.h"

void eigsrt(VecDoub_IO, MatDoub_IO);

struct Jacobi {
	const Int n;
	MatDoub a,v;
	VecDoub d;
	Int nrot;
	const Doub EPS;
        Jacobi(MatDoub_I &aa); 
	inline void rot(MatDoub_IO &a, const Doub s, const Doub tau, const Int i,
		const Int j, const Int k, const Int l);
};


struct Symmeig {
	Int n;
	MatDoub z;
	VecDoub d,e;
	Bool yesvecs;
        Symmeig(MatDoub_I &a, Bool yesvec); 
	Symmeig(VecDoub_I &dd, VecDoub_I &ee, Bool yesvec);
	void sort(); 
	void tred2();
	void tqli();
	Doub pythag(const Doub a, const Doub b);
};
#endif
