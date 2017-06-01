#!/bin/bash
#Script for Energy and Magnetization for different Temperatures
LANG=en_US
n=128
J=1.0
B=0.0
niter=2000000
Tini=0.1
Tfin=2.0
paso=0.1
dir=`pwd`

cd ../results
rm temps.txt
touch temps.txt
cd $dir

for T in $(seq $Tini $paso $Tfin);
do
	cd ../bin
	./ising.e $n $T $J $B $niter
	cd ../results
	mv data.txt data${T}.txt
	echo $T
	echo $T >> temps.txt 
done

Tini=2.5
Tfin=6
paso=0.5
for T in $(seq $Tini $paso $Tfin);
do
	cd ../bin
	./ising.e $n $T $J $B $niter
	cd ../results
	mv data.txt data${T}.txt
	echo $T
	echo $T >> temps.txt 
done


