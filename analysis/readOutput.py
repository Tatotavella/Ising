import os
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

from functions import *

data_dir = os.path.dirname(__file__) #<-- Absolute path
rel_path = "../results/data.txt"
direc = os.path.join(data_dir, rel_path)

step=[]
ener=[]
magnet=[]

f = open(direc, 'r')
next(f) #Jump header
for line in f:
        inter = [x for x in line.split('\t\t')]
        step.append(int(inter[0]))
        ener.append(float(inter[1]))
        magnet.append(int(inter[2]))

taus = range(1,2000)
enercorrs = []
magnetcorrs = []
for tau in taus:
    enercorr = autocorr(ener,tau)
    enercorrs.append(enercorr)
    magnetcorr = autocorr(magnet,tau)
    magnetcorrs.append(magnetcorr)
    
plt.figure(1)
plt.subplot(211)
plt.xlabel("Step")
plt.ylabel("Magnetization")
plt.plot(step,magnet,'*')
plt.subplot(212)    
plt.xlabel("Step")
plt.ylabel("Energy")
plt.plot(step,ener,'*')
plt.show()

plt.figure(2)
plt.subplot(211)
plt.xlabel("Step")
plt.ylabel("Energy")
plt.plot(step,ener,'*')
plt.subplot(212)
plt.xlabel(r"$\tau$")
plt.ylabel("Autocorrelation")
plt.plot(taus,enercorrs,'b*')
plt.show()

plt.figure(3)
plt.subplot(211)
plt.xlabel("Step")
plt.ylabel("Magnetization")
plt.plot(step,magnet,'*')
plt.subplot(212)
plt.xlabel(r"$\tau$")
plt.ylabel("Autocorrelation")
plt.plot(taus,magnetcorrs,'r*')
plt.show()
