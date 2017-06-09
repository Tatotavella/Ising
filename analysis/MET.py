import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

data_dir = os.path.dirname(__file__) #<-- Absolute directory
rel_path = "../results/EMT/MEvsTN64.txt"
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
'''
plt.figure(1)
#plt.plot(T,M,'ro')
plt.errorbar(T,M,yerr=Merr,fmt='ro')
plt.xlabel('Temperatura')
plt.ylabel('Magnetizacion')
plt.figure(2)
#plt.plot(T,E,'bo')
plt.errorbar(T,E,yerr=Eerr,fmt='bo')
plt.xlabel('Temperatura')
plt.ylabel('Energia')

plt.show()

plt.plot(T,susc,'*')
plt.xlabel('Temperatura')
plt.ylabel('Susceptibilidad')
plt.show()

plt.plot(T,cv,'*')
plt.xlabel('Temperatura')
plt.ylabel('Calor especifico')
'''
plt.show()





