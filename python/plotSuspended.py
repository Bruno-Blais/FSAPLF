#This program makes the plot for the degree of suspension calculated via FSAPLF

# Author : Bruno Blais

#Python imports
import os
import math
import numpy
import matplotlib.pyplot as plt
import sys

#**********************
#   OPTIONS
#**********************

dt = 5e-6 # time step of the simulation

#=====================
#   MAIN
#=====================

fname=sys.argv[1]

# Read input data from file fname and distribute it to significantly named variables
print "R-> %s" %fname
data= numpy.loadtxt(fname, unpack=False, skiprows=1)
it = data[:,0]
Nsusp=data[:,1]
Ntot=data[:,2]

#Sort arrays
indices= it.argsort()
it=it[indices]
Nsusp=Nsusp[indices]
Ntot=Ntot[indices]
t = it * dt

frac=Nsusp[:]/Ntot[:]
plt.plot(t,1.-frac,'s-',label="Fraction of suspended particles")
plt.ylabel('Unsuspended fraction')
plt.xlabel('time [s]')
#plt.title('Averaged parameter over time')
#plt.legend(loc=9)
plt.show()

