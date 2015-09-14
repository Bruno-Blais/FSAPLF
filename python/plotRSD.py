#This program makes the plot for an averaged variable from FSAPLF

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
N = data[:,0]
parts=data[:,1:]

#Sort arrays
indices= N.argsort()
N=N[indices]
parts=parts[indices,:]
t = N * dt
ncol=numpy.size(parts,1)

for i in range(0,ncol,2):
    print "Plotting probe : ", i
    frac=parts[:,i]/parts[:,i+1]
    plt.plot(t,frac,'-',label="Probe #%i" %(i))
    plt.ylabel('RSD fraction')
    plt.xlabel('time [s]')
    #plt.title('Averaged parameter over time')
    #plt.legend(loc=9)
plt.show()

