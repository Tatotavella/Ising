import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

data_dir = os.path.dirname(__file__) #<-- Absolute directory
rel_path = "../results/data.txt"
dire = os.path.join(data_dir, rel_path)
g = open(dire,'r')
step = []
E = []
M = []
next(g)
for line in g:
	inter = [x for x in line.split('\t\t\t')]
	step.append(int(inter[0]))
	E.append(float(inter[1]))
	M.append(float(inter[2]))

#plt.figure(1)
#plt.plot(step,E,'bo')
#plt.xlabel('MC step')
#plt.ylabel('Energy')
#plt.figure(2)
plt.plot(step,M,'bo')
plt.xlabel('MC step')
plt.ylabel('Magnetization')

plt.show()

plt.hist(M, bins=200)

plt.show()
