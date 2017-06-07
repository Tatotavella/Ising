import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


data_dir = os.path.dirname(__file__) #<-- Absolute directory
rel_path = "../results/bimodal1e12.txt"
#rel_path = "../results/bimodal/data2.31.txt"
dire = os.path.join(data_dir, rel_path)
g = open(dire,'r')
step = []
E = []
M = []
next(g)
for line in g:
	inter = [x for x in line.split('\t\t\t')]
	step.append(float(inter[0]))
	E.append(float(inter[1]))
	M.append(float(inter[2]))

partials = np.logspace(2,6,5)

for p in partials:
	plt.hist(M[:int(p)], bins=50,alpha=0.4,normed=True,label='Partial size: '+str(int(p)))

plt.legend(loc='upper left',prop={'size':8})
plt.show()
