import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

lista = ['Tbajadirecto1','Tbajadirecto2','Tbajadirecto3','Tbajadirecto4','Tbajadirecto5']
temperature = []
magnet = []
errmagnet = []
energy = []
errenergy = []

for place in lista:

	data_dir = os.path.dirname(__file__) #<-- Absolute directory
	rel_path = "../results/"+place+"/temps.txt"
	dire = os.path.join(data_dir, rel_path)
	g = open(dire,'r')
	temps=[]
	for line in g:
		temps.append(line[:len(line)-1])

	stepini = 1000000
	stepfin = 2000000

	for T in temps:
		print(T)
		step = []
		E = []
		M = []
		data_dir = os.path.dirname(__file__) #<-- Absolute directory
		rel_path = "../results/"+place+"/data"
		direc = os.path.join(data_dir, rel_path)
		direc = direc + T + '.txt'
		f = open(direc, 'r')
		next(f) #Headers
		next(f)
		for line in f:
			inter = [x for x in line.split('\t\t\t')]
			a = inter[0]
			if a>=stepini:
			 step.append(int(inter[0]))
			 E.append(float(inter[1]))
			 M.append(float(inter[2]))

		temperature.append(float(T))
		aux = M
		magnet.append(np.abs(np.mean(aux)))#Absolute value
		errmagnet.append(np.sqrt(np.var(aux)))

		aux = E
		energy.append(np.mean(aux))
		errenergy.append(np.sqrt(np.var(aux)))

		'''
		plt.figure(1)
		plt.plot(step,E,'*',label=T)
		plt.xlabel('Step')
		plt.ylabel('Energy')
		plt.figure(2)
		plt.plot(step,M,'*',label=T)
		plt.xlabel('Step')
		plt.ylabel('Magnetization')
		'''

#plt.legend()
plt.errorbar(temperature,magnet,yerr=errmagnet,fmt='ro')
plt.xlabel('Temperature')
plt.ylabel('Magnetization')
plt.show()
plt.errorbar(temperature,energy,yerr=errenergy,fmt='bo')
plt.xlabel('Temperature')
plt.ylabel('Energy')
plt.show()
