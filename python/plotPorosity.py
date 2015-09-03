#   This script plots N porosity results from FSAPLF
#
#
#   Author : Bruno Blais

#Python imports
#----------------
import os
import sys
import numpy 
import math
import matplotlib.pyplot as plt
import glob
import re
#----------------

#********************************
#   OPTIONS AND USER PARAMETERS
#********************************

#-------------------------------
# MAIN
#-------------------------------

if (len(sys.argv)<2):
    raise Exception('At least one file argument needs to be specified')

fig = plt.figure("Void Fraction in time")
ax = fig.add_subplot(111)#, autoscale_on=False, xlim=(min(x)-0.001,max(x)+0.001), ylim=(0.1, 1.05))
ax.grid()
ax.set_ylabel("Fraction of fluid")
ax.set_xlabel("Distance along axis")

for i in range(1,len(sys.argv)):
    fname=sys.argv[i]
    x,phi = numpy.loadtxt(fname, unpack=True) # Load data from text file
    ax.plot(x,phi)
plt.show()

