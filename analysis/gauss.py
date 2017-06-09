import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import scipy.stats as stats 
from scipy.special import gamma as Gamma

data_dir = os.path.dirname(__file__) #<-- Absolute directory
#rel_path = "../results/bimodal1e12.txt"
rel_path = "../results/bimodal/gauss.txt"
dire = os.path.join(data_dir, rel_path)
g = open(dire,'r')
N = 64
T = []
muM = []
sgM = []
muE = []
sgE = []
next(g)
for line in g:
	inter = [x for x in line.split('\t')]
	T.append(float(inter[0]))
	muM.append(float(inter[2])/(N**2))
	sgM.append(float(inter[3])/(N**2))
	muE.append(float(inter[4])/(N**2))
	sgE.append(float(inter[5])/(N**2))

chi = []
for i,s in enumerate(sgM):
	chi.append((s**2)/T[i])

cv = []
for i,s in enumerate(sgE):
	cv.append((s**2)/(T[i]**2))

f, axarr = plt.subplots(2, sharex=True)
axarr[0].plot(T,muM,'ro')
axarr[0].plot(T,muM,'r')
axarr[0].set_ylabel('Magnetizacion')

axarr[1].plot(T,chi,'go')
axarr[1].plot(T,chi,'g')
axarr[1].set_ylabel('Susceptibilidad')
axarr[1].set_xlabel('Temperatura')

plt.show()

f, axarr = plt.subplots(2, sharex=True)
axarr[0].plot(T,muE,'bo')
axarr[0].plot(T,muE,'b')
axarr[0].set_ylabel('Energia')

axarr[1].plot(T,cv,'go')
axarr[1].plot(T,cv,'g')
axarr[1].set_ylabel('Calor especifico')
axarr[1].set_xlabel('Temperatura')

plt.show()
'''
plt.plot(T,sgM,'ro')
plt.show()
plt.plot(T,chi,'go')
plt.show()
plt.plot(T,muM,'bo')
plt.show()

plt.plot(T,sgE,'ro')
plt.show()
plt.plot(T,cv,'go')
plt.show()
plt.plot(T,muE,'bo')
plt.show()
'''


