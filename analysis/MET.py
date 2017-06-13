import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import sys

'''
Script for the output of temp_ramp.e program.
Shows the data and calculates specific heat and 
susceptibility.
'''
'''
# The data file name can be an input
if len(sys.argv) > 1:
	rel_path = sys.argv[1]
else:
	rel_path = "../results/EMT/MEvsT.txt"
'''
sizes = ['128','64','16','10']

f, axarr = plt.subplots(2, sharex=True)
g, bxarr = plt.subplots(2, sharex=True)

for s in sizes:
	rel_path = "../results/EMT/MEvsTN"+s+".txt"

	data_dir = os.path.dirname(__file__) #<-- Absolute directory
	dire = os.path.join(data_dir, rel_path)
	g = open(dire,'r')
	T=[]
	E=[]
	M=[]
	Eerr=[]
	Merr=[]
	next(g)
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


	#f, axarr = plt.subplots(2, sharex=True)
	axarr[0].errorbar(T,M,yerr=Merr,fmt='o')
	#axarr[0].plot(T,M,'r')
	#axarr[0].set_ylabel('Magnetizacion')
	axarr[0].tick_params(axis='both', which='major', labelsize=20)
	axarr[0].text(1.08, 0.0, r'$Magnetizacion$', fontsize=25, bbox=dict(facecolor='r', alpha=0.2))
 

	axarr[1].errorbar(T,E,yerr=Eerr,fmt='o',label='N '+s)
	#axarr[1].plot(T,E,'b')
	#axarr[1].set_ylabel('Energia')
	axarr[1].set_xlabel(r'$Temperatura$',fontsize=30)
	axarr[1].tick_params(axis='both', which='major', labelsize=20)
	axarr[1].text(1.08, -1.0, r'$Energia$', fontsize=25, bbox=dict(facecolor='b', alpha=0.2)) 
	axarr[1].legend(loc='lower right',prop={'size':15}, numpoints=1)

	
	plt.figure(1)
	#g, bxarr = plt.subplots(2, sharex=True)
	bxarr[0].plot(T,susc,'o',label='N '+s)
	#bxarr[0].plot(T,susc,'g',label='N '+s)
	#bxarr[0].set_ylabel('Susceptibilidad')
	bxarr[0].text(1.03, 0.42, r'$Susceptibilidad$', fontsize=25, bbox=dict(facecolor='g', alpha=0.2)) 
	bxarr[0].legend(loc='lower right',prop={'size':15}, numpoints=1)
	bxarr[0].set_yscale('log')
	bxarr[0].tick_params(axis='both', which='major', labelsize=20)

	bxarr[1].plot(T,cv,'o')
	#bxarr[1].plot(T,cv,'b')
	bxarr[1].text(1.03, 0.012, r'$Calor$'+' '+ r'$especifico$', fontsize=25, bbox=dict(facecolor='r', alpha=0.2)) 
	bxarr[1].set_xlabel(r'$Temperatura$',fontsize=30)
	#bxarr[1].set_ylabel('Calor especifico')
	bxarr[1].tick_params(axis='both', which='major', labelsize=20)
	bxarr[1].set_yscale('log')
	
#plt.legend()
plt.show()





