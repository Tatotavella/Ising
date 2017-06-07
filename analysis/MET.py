import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

data_dir = os.path.dirname(__file__) #<-- Absolute directory
rel_path = "../results/EMT/MEvsT.txt"
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


plt.figure(1)
#plt.plot(T,M,'ro')
plt.errorbar(T,M,yerr=Merr,fmt='ro')
plt.xlabel('Temperature')
plt.ylabel('Magnetization')
plt.figure(2)
#plt.plot(T,E,'bo')
plt.errorbar(T,E,yerr=Eerr,fmt='bo')
plt.xlabel('Temperature')
plt.ylabel('Energy')

plt.show()

plt.plot(T,susc,'*')
plt.xlabel('Temperature')
plt.ylabel('Susceptibility')
plt.show()

plt.plot(T,cv,'*')
plt.xlabel('Temperature')
plt.ylabel('Specific Heat')
plt.show()





