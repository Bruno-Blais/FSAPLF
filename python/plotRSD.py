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
it0=3020000

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
t = (N-it0) * dt
ncol=numpy.size(parts,1)

for i in range(0,ncol,2):
    print "Plotting probe : ", i/2
    frac=parts[:,i]/(parts[:,i+1]+1e-10)
    for j,f in enumerate(parts[:,i]):
        if (f<5): frac[j]=-1
    rsd= (frac-0.5)**2. /( parts[:,i]+parts[:,i+1]+0.1)
    plt.plot(t,frac,'-',label="Probe #%i" %(i/2))
    plt.ylabel('Fraction of colored particles')
    plt.xlabel('time [s]')
    plt.ylim([0,1])
    #plt.title('Averaged parameter over time')
    plt.legend(loc=9,ncol=4)
plt.show()

