import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def autocorr(y,tau):
    mean = np.mean(y)
    var = np.var(y)
    partsum = 0.0
    for t in range(len(y)-tau):
        partsum += (y[t] - mean)*(y[t+tau] - mean)
    corr = partsum/(len(y)-tau)
    return corr/var
        
