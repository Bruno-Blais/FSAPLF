#====
#This program makes the plot for the PCA analysis from FSAPLF

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
uvw = data[:,1:4]
std = data[:,5:8]
Min = data[:,9:12]
Max = data[:,13:16]
pMin = data[:,17:20]
pMax = data[:,21:24]

#Sort arrays
indices= N.argsort()
N=N[indices]
uvw=uvw[indices,:]
std=std[indices,:]
Min=Min[indices,:]
Max=Max[indices,:]
pMin=pMin[indices,:]
pMax=pMax[indices,:]

t = N * dt
fig, axes = plt.subplots(nrows=3, ncols=1)
for i in range(0,3,1):
    plt.subplot(3,1,i+1)
    plt.errorbar(t,uvw[:,i],yerr=std[:,i],fmt='-bo', label="Axis")
    plt.plot(t,pMax[:,i],'-g',label="Max")
    plt.plot(t,pMin[:,i],'-g',label="Max")
    plt.ylabel('Parameter')
    plt.xlabel('time [s]')
    #plt.title('Averaged parameter over time')
    #plt.legend(loc=9)
plt.show()

