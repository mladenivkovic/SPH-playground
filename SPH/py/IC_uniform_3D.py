#!/usr/bin/python3

errmsg="""
Creates IC files for SPH project:
Uniform 3D grid of (2^levelmax)^3 particles, where
levelmax is given as cmd line arg.
usage:

    ./IC_uniform_3D.py levelmax

"""

from sys import argv
import numpy as np
from matplotlib import pyplot as plt



if len(argv) < 2:
    print("Need levelmax as cmd line arg.")
    print(errmsg)
    quit()

else:
    try:
        levelmax=int(argv[1])
    except ValueError:
        print("Need levelmax as cmd line arg.")
        print(errmsg)
        quit()




boxlen = 1

twotol = 2**levelmax
dx = 1/(twotol)
dxh = dx/2.0



f = open('IC_SPH_uniform_3D.dat', "w+")
f.write("%12.6E \n" % boxlen)    # write boxlen
f.write("%12i \n" % twotol**3) # write nparts


#  x = np.zeros(twotol**3)
#  y = np.zeros(twotol**3)
#  z = np.zeros(twotol**3)
#  ind = 0

for i in range(twotol):
    xx = dxh + i*dx
    for j in range(twotol):
        yy = dxh + j * dx
        for k in range(twotol):
            zz = dxh + k * dx

            f.write("%12.6E, %12.6E, %12.6E, %12.6E, %12.6E, %12.6E, %12.6E\n" % (xx,yy,zz,0.0,0.0,0.0,1))

            #  x[ind] = xx
            #  y[ind] = yy
            #  z[ind] = zz
            #  ind +=1


#  plt.figure()
#  plt.scatter(x,y)
#  plt.xlim([0,boxlen])
#  plt.ylim([0,boxlen])
#  plt.show()

print("Done.")
