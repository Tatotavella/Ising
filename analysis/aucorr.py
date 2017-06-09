import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from functions import *

Tes = ['1.50','2.26','2.50','3.00','5.00']

for a in Tes:
	data_dir = os.path.dirname(__file__) #<-- Absolute directory
	rel_path = "../results/aucorr/data"+a+".txt"
	dire = os.path.join(data_dir, rel_path)
	g = open(dire,'r')
	step=[]
	E=[]
	M=[]
	next(g)
	for line in g:
		inter = [x for x in line.split('\t\t')]
		step.append(float(inter[0]))
		E.append(float(inter[1]))
		M.append(float(inter[2]))

	taus = range(1,20001,1000)
	aucM = []
	aucE = []
	for t in taus:
		aucM.append(autocorr(M,t))
		aucE.append(autocorr(E,t))

	'''
	plt.figure(1)
	plt.plot(step,M,'ro')
	plt.xlabel('Step')
	plt.ylabel('Magnetization')
	plt.figure(2)
	plt.plot(step,E,'bo')
	plt.xlabel('Step')
	plt.ylabel('Energy')

	plt.show()
	'''
	plt.figure(3)
	plt.plot(taus,aucM)
	plt.xlabel('Tau')
	plt.ylabel('Aucorr Magnetization')
	plt.figure(4)
	plt.plot(taus,aucE)
	plt.xlabel('Tau')
	plt.ylabel('Aucorr Energy')

plt.show()



