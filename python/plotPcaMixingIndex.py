####################################################################################
#
#   File    : plotPcaMixingIndex.py
#
#   Run Instructions    : python plotPcaMixingIndex.py PCAFILE
#
#   Author : Bruno Blais
# 
#   Description :   This script plots the results from a PCA analysis
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
dt=1e-5
it1=1700000
pdf=False
cutoff=0.300
fs=5.
filterOrder=3
annotate=True
listAnnotate=[90, 200, 450, 650]

# Figures
plt.rcParams['figure.figsize'] = 10, 7
params = {'backend': 'ps',
             'axes.labelsize': 16,
             'text.fontsize': 16,
             'legend.fontsize': 16,
             'xtick.labelsize': 15,
             'ytick.labelsize': 15,
             'text.usetex': True,
             }

plt.rcParams.update(params)

#=====================
#   MAIN
#=====================

fname=sys.argv[1]

# Read input data from file fname and distribute it to significantly named variables
print "R-> %s" %fname
data= numpy.loadtxt(fname, unpack=False, skiprows=1)
it=data[:,0]
lam = data[:,1:4] # eigenvalues are sorted by default
v=data[:,4:13]

t = (it-it1) * dt
fig, axes = plt.subplots(nrows=3, ncols=1)
for i in range(0,3,1):
    plt.subplot(3,1,i+1)
    plt.plot(t,numpy.sqrt(lam[:,i]/lam[0,i]),'-g',linewidth=2.0,label="Final Eigenvector [ %3.2f %3.2f %3.2f ] " %(v[-1,3*(i)], v[-1,3*(i)+1],v[-1,3*(i)+2]))
    plt.ylabel('Mixing index ' + str(i))
    plt.ylim([-0.1,1.1])
    y=numpy.sqrt(lam[:,i]/lam[0,i])
    if annotate:
        for j in listAnnotate:
            plt.annotate( "[%3.2f, %3.2f, %3.2f,]" %(v[j,3*(i)+0], v[j,3*(i)+1],v[j,3*(i)+2]), 
                    xy=(t[j], y[j]), xytext=(t[j],y[j]+0.1),
                    arrowprops=dict(facecolor='black', shrink=0.05),
                )
    plt.grid(b=True, which='major', color='k', linestyle='--',linewidth=0.25) 

    plt.annotate( "%3.4f" %(numpy.min(y)), xy=(numpy.max(t), numpy.min(y)), xytext=(numpy.max(t)-15, numpy.min(y)+0.1))

    if (i==2): plt.xlabel('time [s]')
    if numpy.min(lam[:,i] > 0.7) : plt.legend(loc=3)
    else: plt.legend(loc=1)
plt.show()

