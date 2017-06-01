import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

data_dir = os.path.dirname(__file__) #<-- Absolute directory
rel_path = "../results/MEvsT.txt"
dire = os.path.join(data_dir, rel_path)
g = open(dire,'r')
T=[]
E=[]
M=[]
next(g)
for line in g:
	inter = [x for x in line.split('\t\t\t')]
	T.append(float(inter[0]))
	E.append(float(inter[1]))
	M.append(float(inter[2]))


plt.figure(1)
plt.plot(T,M,'ro')
plt.xlabel('Temperature')
plt.ylabel('Magnetization')
plt.figure(2)
plt.plot(T,E,'bo')
plt.xlabel('Temperature')
plt.ylabel('Energy')

plt.show()

