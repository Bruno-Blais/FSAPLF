####################################################################################
#
#   File    : plotPcaHistogram.py
#
#   Run Instructions    : python plotPcaMixingIndex.py PCAFILE
#
#   Author : Bruno Blais
# 
#   Description :   This script plots the eigenvalues from the PCA analysis
#
#
####################################################################################

#Python imports
#----------------
import os
import sys
import numpy
import time
import matplotlib.pyplot as plt
#----------------

#********************************
#   OPTIONS AND USER PARAMETERS
#********************************
pdf=False
annotate=True

#********************************
#   Anotation options
#********************************
lastAnnotationShift=0.075

#********************************
#   Figures options
#********************************

plt.rcParams['figure.figsize'] = 10, 7
params = {'backend': 'ps',
             'axes.labelsize': 20,
             'text.fontsize': 20,
             'legend.fontsize': 18,
             'xtick.labelsize': 18,
             'ytick.labelsize': 18,
             'text.usetex': True,
             }

plt.rcParams.update(params)

#=====================
#   MAIN
#=====================

fig = plt.figure()

for i,fname in enumerate(sys.argv):
    if (i>0):
        # Read input data from file fname and distribute it to significantly named variables
        print "R-> %s" %fname
        data= numpy.loadtxt(fname, unpack=False, skiprows=1)

        eig=data[:,0]


        ax = fig.add_subplot(111) # Create plot object
        ax.plot(range(1,len(eig)+1),eig,'-o')



ax.set_yscale('log')
ax.set_xscale('log')
xlim=[-0.1,len(eig)+10]

plt.show()

