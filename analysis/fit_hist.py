import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import scipy.stats as stats 
from scipy.special import gamma as Gamma

data_dir = os.path.dirname(__file__) #<-- Absolute directory
#rel_path = "../results/bimodal1e12.txt"
rel_path = "../results/bimodal/data2.50.txt"
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
'''
plt.hist(M,bins=100,alpha=0.5,normed=True)
plt.xlabel('Magnetizacion por sitio')
plt.show()
'''
hist , bin_edges = np.histogram(E, bins=100)
centres = (bin_edges[:-1] + bin_edges[1:])/2.
errs = np.sqrt(hist)

def bimod(x, a, b, mu, sg):
    y = a * np.exp(-((x - mu)/sg)**2) + b * np.exp(-((x+mu)/sg)**2)
    return y
def mod(x, a, mu, sg):
	y = a * np.exp(-((x - mu)/sg)**2)
	return y

def lognorm(x, a, b, mu, sg):
    y = a * np.exp(-((np.log(x)-mu)/sg)**2)/x + b * np.exp(-((np.log(x)+mu)/sg)**2)/x
    return y
def gamma( x, lmbd, k):
    y = lmbd * np.exp(-lmbd*x)*((lmbd*x)**(k-1))/Gamma(k)
    return y 

guess = [40000.0,-1.1,0.05]
#guess = [80000.0,80000.0,-2000.0,100.0]
popt, pcov = curve_fit(mod, centres, hist, p0=guess)#, sigma=errs)
x = np.linspace(-2,2,1000)
fitb = mod(x, *popt)
plt.plot(x,fitb,'r')

print(popt)

#popt, pcov = curve_fit(gamma, centres, hist, sigma=errs)
#x = np.linspace(-4000,4000,1000)
#fitg = gamma(x, *popt)
#plt.plot(x,fitg,'g')

plt.errorbar(centres,hist,yerr=errs,fmt='bo')
plt.show()
