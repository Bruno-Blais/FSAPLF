#   This script animates the porosity results from FSAPLF
#
#
#   Needs to be restructured to take the data automatically
#
#   Author : Bruno Blais

#Python imports
#----------------
import os
import sys
import numpy 
import math
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import glob
import re
#----------------

#********************************
#   OPTIONS AND USER PARAMETERS
#********************************

label="plane"
folder="./"

#--------------------------------
# Functions
#--------------------------------

def naturalSort(l): 
    convert = lambda text: int(text) if text.isdigit() else text.lower() 
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ] 
    return sorted(l, key = alphanum_key)


#-------------------------------
# MAIN
#-------------------------------

if (len(sys.argv)<2):
    raise Exception('A folder argument needs to be specified')

if (len(sys.argv)==3):
    label=sys.argv[2]

folder=sys.argv[1]

# Acquire all the files from the folder and sort them in a coherent manner
files=glob.glob(folder+"/*"+label+"*")
files=naturalSort(files)

#Load first file to acquire the axis
print "Acquiring time : ", files[0]
fname= files[0]
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
    print "Plotting time : ", files[t]
    fname=files[t]
    x,phi = numpy.loadtxt(fname, unpack=True) # Load data from text file
    line.set_data(x,phi) # Update the data
    #time_text.set_text(time_template%(t))
    time_text.set_text(files[t])
    return line,time_text

ani = animation.FuncAnimation(fig, animate,range(0,len(files)), blit=True, init_func=init)

plt.show()

