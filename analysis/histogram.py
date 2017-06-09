import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

#Tes = ['5.00','4.38','3.75','3.12','2.50','2.40','2.38','2.37','2.36','2.35','2.34','2.32','2.31','2.30','2.29','2.28','2.26','2.25','2.24','2.23','2.22','2.20','2.19','2.18','2.17','2.16','2.14','2.13']

#Tes = ['2.26','2.25','2.24','2.23','2.22','2.20']

Tes = ['2.33']
for T in Tes[::-1]:
	data_dir = os.path.dirname(__file__) #<-- Absolute directory
	rel_path = "../results/bimodal/data"
	dire = os.path.join(data_dir, rel_path)
	dire = dire + T + '.txt'
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
	
	#plt.figure(1)
	#plt.plot(step,E,'bo')
	#plt.xlabel('MC step')
	#plt.ylabel('Energy')
	#plt.figure(2)
		
	plt.plot(step,M,'o')
	plt.xlabel('MC step')
	plt.ylabel('Magnetization')
	
	plt.show()
	
	hist , bin_edges = np.histogram(M, bins=100,normed=True)
	centres = (bin_edges[:-1] + bin_edges[1:])/2.
	plt.plot(centres,hist,'o',label='Temp'+T)
	
plt.legend(loc='upper left',prop={'size':8})
plt.show()
