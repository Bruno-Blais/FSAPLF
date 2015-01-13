# This script animates the porosity results from FSAPLF
#
# A folder must be given as argument?
#
# Author : Bruno Blais
# Last modified : 24-02-2014

#Python imports
#----------------
import os
import sys
import numpy 
import math
import matplotlib.pyplot as plt
import matplotlib.animation as animation
#----------------

#********************************
#   OPTIONS AND USER PARAMETERS
#********************************

#Initial time of simulation, final time and time increment must be specified by user
t0=int(sys.argv[2])
tf=int(sys.argv[4])
dT=int(sys.argv[3])
nt=int((tf-t0)/dT)
t=t0

folder=sys.argv[1]

#Load first file to acquire the axis
print "Acquiring time : ", t0
fname=folder + str(t0)
x,phi = numpy.loadtxt(fname, unpack=True) # Load data from text file
print "Time acquired"

fig = plt.figure("Void Fraction in time")
ax = fig.add_subplot(111, autoscale_on=False, xlim=(min(x)-0.001,max(x)+0.001), ylim=(0.1, 1.05))
ax.grid()
ax.set_ylabel("Fraction of fluid")
ax.set_xlabel("Distance along axis")
line, = ax.plot([], [], '-', lw=2)
time_template = 'Iteration = %i'
time_text = ax.text(0.05, 0.1, '', transform=ax.transAxes)

#plt.legend(loc=9)

def init():
    line.set_data([], [])
    time_text.set_text('')
    return line, time_text

def onClick(event):
    global pause
    pause ^= True

def animate(t):
    print "Plotting time : ", t
    fname=folder + str(t)
    x,phi = numpy.loadtxt(fname, unpack=True) # Load data from text file
    line.set_data(x,phi) # Update the data
    time_text.set_text(time_template%(t))
    return line,time_text

ani = animation.FuncAnimation(fig, animate,range(t0,tf,dT), blit=True, init_func=init)

plt.show()

