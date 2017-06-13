import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from functions import *
import sys

#Tes = ['5.00','4.38','3.75','3.12','2.50','2.40','2.38','2.37','2.36','2.35','2.34','2.32','2.31','2.30','2.29','2.28','2.26','2.25','2.24','2.23','2.22','2.20','2.19','2.18','2.17','2.16','2.14','2.13']

'''
Script for the output of histogram.e program.
Shows the state data and then fits the desired temperatures
histogram.
'''

# The data file name can be an input
if len(sys.argv) > 1:
	dir_dat = "/"+sys.argv[1]
else:
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

n_of_bins = 50

Ms=[]

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

	if T[:4]=='2.30' or T[:4]=='2.33' or T[:4]=='2.36' or T[:4]=='2.40':
	
		plt.figure(1)
		hist_E , bin_edges_E = np.histogram(E, bins=n_of_bins,normed=True)
		centres_E = (bin_edges_E[:-1] + bin_edges_E[1:])/2.
		plt.hist(E,bins=n_of_bins,alpha=0.4,label=T[:4],normed=True)
		plt.xlabel('Energia')
	
		plt.figure(2)
		hist_M , bin_edges_M = np.histogram(M, bins=n_of_bins,normed=True)
		centres_M = (bin_edges_M[:-1] + bin_edges_M[1:])/2.
		plt.hist(M,bins=n_of_bins,alpha=0.4,label=T[:4],normed=True)
		plt.xlabel(r'$Magnetizacion$',fontsize=30)
		plt.ylabel(r'$Frecuencia$'+' '+r'$en$'+' '+r'$el$'+' '+r'$ensamble$',fontsize=30)	
		plt.text(-0.72, 1.46, r'$Temperaturas$', fontsize=25, bbox=dict(facecolor='r', alpha=0.2)) 
		plt.text(-0.3, 1.46, r'$J=1.0$, $B=0.0$, $N=32$', fontsize=25, bbox=dict(facecolor='g', alpha=0.2))
		plt.tick_params(axis='both', which='major', labelsize=20)

	Ms.append(M)
	

	errs_M = []
	errs_E = []

	#Errors in histogram
	for idx in range(len(hist_M)):
		errs_M.append(np.sqrt(hist_M[idx])/len(hist_M)) #Error in normalized histogram
		errs_E.append(np.sqrt(hist_E[idx])/len(hist_E))

	Magnets.append([centres_M,hist_M,errs_M])
	Eners.append([centres_E,hist_E,errs_E])

g.close()
plt.legend(loc='upper left',prop={'size':15})

plt.show()

#Data fitting

#Bimodal form and guess
#bimod(x, a, b, mu, sg) =  a * np.exp(-((x - mu)/sg)**2) + b * np.exp(-((x+mu)/sg)**2)
#Guess [ a , b , mu , sg ]

print(len(Magnets))
j = 6

guess = [1.2,1.1,-0.6,0.6]

xdata_M = Magnets[j][0]
ydata_M = Magnets[j][1]
errdata_M = Magnets[j][2] 

popt, pcov = curve_fit(bimod, xdata_M, ydata_M, p0=guess, sigma=errdata_M)

xfit = np.linspace(-1,1,1000)
yfit = bimod(xfit, *popt)

print(popt)

plt.plot(xfit,yfit,'r',linewidth=5)
plt.errorbar(xdata_M,ydata_M,yerr=errdata_M,fmt='bo',label = 'T '+Tes[j][:4], markersize=10)

plt.xlabel(r'$Magnetizacion$',fontsize=30)
plt.ylabel(r'$Frecuencia$'+' '+r'$en$'+' '+r'$el$'+' '+r'$ensamble$',fontsize=30)
plt.tick_params(axis='both', which='major', labelsize=20)	

plt.legend(loc='upper left',prop={'size':25},numpoints=1)
plt.show()


Tem = [2.30,2.31,2.32,2.33,2.34,2.35,2.36,2.37,2.38,2.40]
masM = [0.61,0.53,0.50,0.44,0.42,0.38,0.37,0.32,0.32,0.29]
menM = [-0.61,-0.53,-0.50,-0.44,-0.42,-0.38,-0.37,-0.32,-0.32,-0.29]
sg = [0.258,0.267,0.290,0.310,0.317,0.321,0.320,0.318,0.313,0.311]
chi = []
for i in range(len(sg)):
	chi.append(sg[i]/Tem[i])

plt.plot(Tem,masM,'bo')
plt.plot(Tem,masM,'b')
plt.plot(Tem,menM,'ro')
plt.plot(Tem,menM,'r')
plt.ylabel(r'$Magnetizacion$',fontsize=30)
plt.xlabel(r'$Temperatura$',fontsize=30)
plt.tick_params(axis='both', which='major', labelsize=20)
plt.show()

plt.plot(Tem,chi,'go')
plt.plot(Tem,chi,'g')
plt.ylabel(r'$Susceptibilidad$',fontsize=30)
plt.xlabel(r'$Temperatura$',fontsize=30)
plt.tick_params(axis='both', which='major', labelsize=20)
plt.show()










