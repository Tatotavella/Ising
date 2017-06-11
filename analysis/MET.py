import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import sys

# The data file path can be an input
if len(sys.argv) > 1:
	rel_path = "../results/EMT/"+sys.argv[1]
else:
	rel_path = "../results/EMT/MEvsT.txt"

data_dir = os.path.dirname(__file__) #<-- Absolute directory
dire = os.path.join(data_dir, rel_path)
g = open(dire,'r')
T=[]
E=[]
M=[]
Eerr=[]
Merr=[]
next(g)
for line in g:
	inter = [x for x in line.split('\t\t')]
	T.append(float(inter[0]))
	E.append(float(inter[1]))
	M.append(float(inter[2]))
	Eerr.append(float(inter[3]))
	Merr.append(float(inter[4]))

susc = []
cv = []
for i in range(len(T)):
	susc.append(Merr[i]/T[i])
	cv.append(Eerr[i]/(T[i]**2))

f, axarr = plt.subplots(4, sharex=True)
axarr[0].errorbar(T,M,yerr=Merr,fmt='ro')
axarr[0].set_ylabel('Magnetizacion')

axarr[1].errorbar(T,E,yerr=Eerr,fmt='bo')
axarr[1].set_ylabel('Energia')

axarr[2].plot(T,susc,'go')
axarr[2].set_ylabel('Susceptibilidad')

axarr[3].plot(T,cv,'*')
axarr[3].set_xlabel('Temperatura')
axarr[3].set_ylabel('Calor especifico')

plt.show()





