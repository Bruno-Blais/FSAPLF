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
dt=0.000005
pdf=False
png=True
annotate=True

#********************************
#   Anotation options
#********************************
lastAnnotationShift=-0.050

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

fname=sys.argv[1]

# Read input data from file fname and distribute it to significantly named variables
print "R-> %s" %fname
data= numpy.loadtxt(fname, unpack=False, skiprows=1)
it=data[:,0]
lam = data[:,1:4] # eigenvalues are sorted by default
v=data[:,4:13]

listAnnotate=[len(it)/4.5, 2*len(it)/4., 3.*len(it)/4]


t = (it-it[0]) * dt
fig, axes = plt.subplots(nrows=3, ncols=1)
for i in range(0,3,1):
    plt.subplot(3,1,i+1)
    plt.plot(t,numpy.sqrt(lam[:,i]),'-g',linewidth=2.0,label="Final eigenvector [ %3.2f %3.2f %3.2f ] " %(v[-1,3*(i)], v[-1,3*(i)+1],v[-1,3*(i)+2]))
    plt.ylabel('Mixing index ' + str(i))
    plt.ylim([-0.1,1.6])
    y=numpy.sqrt(lam[:,i])
    if annotate:
        for j in listAnnotate:
            plt.annotate( "[%3.2f, %3.2f, %3.2f,]" %(v[j,3*(i)+0], v[j,3*(i)+1],v[j,3*(i)+2]), 
                    xy=(t[j], y[j]), xytext=(t[j],y[j]+0.3),
                    arrowprops=dict(facecolor='black', shrink=0.05),
                )
    plt.grid(b=True, which='major', color='k', linestyle='--',linewidth=0.25) 

    plt.annotate( "%3.4f" %(y[-1]), xy=(numpy.max(t), numpy.min(y)), xytext=(numpy.max(t)-lastAnnotationShift*max(t), numpy.min(y)+0.1))

    if (i==2): plt.xlabel('time [s]')
    if numpy.min(lam[:,i] > 0.1) : plt.legend(loc=3)
    else: plt.legend(loc="best")

if (pdf): plt.savefig("./pca.pdf")
if (png): plt.savefig("./pca.png",dpi=300)
plt.show()

