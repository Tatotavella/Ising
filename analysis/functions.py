import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import scipy.stats as stats 
from scipy.special import gamma as Gamma
import scipy

def autocorr(y,tau):
    mean = np.mean(y)
    var = np.var(y)
    partsum = 0.0
    for t in range(len(y)-tau):
        partsum += (y[t] - mean)*(y[t+tau] - mean)
    corr = partsum/(len(y)-tau)
    return corr/var

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

def poisson( x, lmbd, mu):
    y = (np.exp(-lmbd)*lmbd**(x - mu))/scipy.misc.factorial(x-mu)
    return y 
