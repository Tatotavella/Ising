import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from functions import *

#Tes = ['5.00','4.38','3.75','3.12','2.50','2.40','2.38','2.37','2.36','2.35','2.34','2.32','2.31','2.30','2.29','2.28','2.26','2.25','2.24','2.23','2.22','2.20','2.19','2.18','2.17','2.16','2.14','2.13']

'''
Script for the output of histogram.e program.
Shows the state data and then fits the desired temperatures
histogram.
'''

dir_dat = '/run_N32'
N = 32

data_dir = os.path.dirname(__file__) #<-- Absolute directory
rel_path = "../results/HISTOGRAM"+dir_dat+"/MEvsT.txt"
dire = os.path.join(data_dir, rel_path)
f = open(dire,'r')
Tes = []
next(f)
next(f)
for line in f:
	inter = [x for x in line.split('\t\t')]
	Tes.append(inter[0])
f.close()

Magnets = []
Eners = []

n_of_bins = 100

for T in Tes:
	data_dir = os.path.dirname(__file__) #<-- Absolute directory
	rel_path = "../results/HISTOGRAM"+dir_dat+"/data"
	dire = os.path.join(data_dir, rel_path)
	dire = dire + T + '.txt'
	g = open(dire,'r')
	step = []
	E = []
	M = []
	next(g)
	next(g)
	for line in g:
		inter = [x for x in line.split('\t\t\t')]
		step.append(float(inter[0]))
		E.append(float(inter[1])/(N*N))
		M.append(float(inter[2])/(N*N))
	
	plt.figure(1)
	hist_M , bin_edges_M = np.histogram(M, bins=n_of_bins,normed=True)
	centres_M = (bin_edges_M[:-1] + bin_edges_M[1:])/2.
	plt.hist(M,bins=n_of_bins,alpha=0.5,label='Temp'+T,normed=True)
	plt.xlabel('Magnetizacion')

	plt.figure(2)	
	hist_E , bin_edges_E = np.histogram(E, bins=n_of_bins,normed=True)
	centres_E = (bin_edges_E[:-1] + bin_edges_E[1:])/2.
	plt.hist(E,bins=n_of_bins,alpha=0.5,label='Temp'+T,normed=True)
	plt.xlabel('Energia')

	errs_M = []
	errs_E = []

	#Errors in histogram
	for idx in range(len(hist_M)):
		errs_M.append(np.sqrt(hist_M[idx])/len(hist_M)) #Error in normalized histogram
		errs_E.append(np.sqrt(hist_E[idx])/len(hist_E))

	Magnets.append([centres_M,hist_M,errs_M])
	Eners.append([centres_E,hist_E,errs_E])

g.close()
plt.legend(loc='upper left',prop={'size':8})
plt.show()


#Data fitting

#Bimodal form and guess
#bimod(x, a, b, mu, sg) =  a * np.exp(-((x - mu)/sg)**2) + b * np.exp(-((x+mu)/sg)**2)
#Guess [ a , b , mu , sg ]

j = 0

guess = [2.0,2.0,-1.0,0.1]

xdata_M = Magnets[j][0]
ydata_M = Magnets[j][1]
errdata_M = Magnets[j][2] 

popt, pcov = curve_fit(bimod, xdata_M, ydata_M, p0=guess, sigma=errdata_M)

xfit = np.linspace(-1,1,1000)
yfit = bimod(xfit, *popt)

print(popt)

plt.plot(xfit,yfit,'r')
plt.errorbar(xdata_M,ydata_M,yerr=errdata_M,fmt='bo',label = 'Temp' + Tes[j])

plt.legend(loc='upper left',prop={'size':8})
plt.show()










