#!/bin/bash
#Script for Energy and Magnetization for different Temperatures
LANG=en_US
n=128
J=1.0
B=0.0
niter=1000000
Tini=0.1
Tfin=6
paso=0.1
dir=`pwd`
for T in $(seq $Tini $paso $Tfin);
do
	cd ../bin
	./ising.e $n $T $J $B $niter
	cd ../results
	mv data.txt data${T}.txt
	echo $T 
done
