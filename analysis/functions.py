import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def autocorr(y,tau):
    mean = np.mean(y)
    var = np.var(y)
    partsum = 0.0
    for t in range(len(y)/tau):
        #print(t)
        #print(t+tau)
        partsum += (y[t] - mean)*(y[t+tau-1] - mean)
    corr = tau*partsum/len(y)
    return corr/var
        
