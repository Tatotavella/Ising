#include "metropolis.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int metropolis(int *lattice, int n, float T, float J, float B, double *mc_list, double *p_ener, int *p_magnet) {
  int place = pick_site(lattice,n);
  flip(lattice,n,place,T,J,B,mc_list,p_ener,p_magnet);
  return 0;
}

int pick_site(int *lattice, int n) {
  /*
    Picks a random site of a size n lattice
   */
  float rnd = 1.0;
  while(rnd==1.0){ //Avoids place equal to n*n
    rnd = (float)rand()/(float)RAND_MAX;
  }
  int place = (int)(n*n*rnd);
  return place;
}

int flip(int *lattice, int n, int idx, float T, float J, float B, double *mc_list, double *p_ener, int *p_magnet) {
  /*
    Makes a Monte Carlo flip evaluation in idx place and writes changes in energy and magnetization
   */
  
  //Get neighbours
  int neigh[4];// 0 left | 1 right | 2 up | 3 down
  get_neighbours(neigh,4,lattice,n,idx);

  //print_data(lattice, n, neigh, 4, idx);

  //Calcute energy difference and flip
  int spin_place = *(lattice+idx);
  int neigh_sum = neigh[0]+neigh[1]+neigh[2]+neigh[3];
  float delta_e = 2*J*spin_place*neigh_sum;
  float delta_b = 2*B*spin_place; 
  float delta = delta_e + delta_b;
   
  double prob;

  if(delta<=0){
    //Flip directly
    *(lattice + idx) = -1*(*(lattice + idx));
    //Write energy and magnetization change
    *p_ener = *p_ener + delta;
    *p_magnet = *p_magnet + *(lattice + idx)*2;
    //printf("Delta E: %.4f, Delta B: %.4f, Prob: %f\n",delta_e,delta_b,prob);
    //printf("Change Accepted\n");

  }else{ //Throw a coin to flip or not
    float coin = (float)rand()/(float)RAND_MAX;
    int mc_idx;
    //Indexing corresponds to 2(delta_e + 8J)/4J + (delta_b + 2B)/4B
    mc_idx = spin_place*neigh_sum + 4 + (spin_place + 1)/2;
    prob = mc_list[mc_idx];
    //printf("Delta E: %.4f, Delta B: %.4f, Prob: %f\n",delta_e,delta_b,prob);
    if(coin < prob){
      *(lattice + idx) = -1*(*(lattice + idx));
      //Write energy and magnetization change
      *p_ener = *p_ener + delta;
      *p_magnet = *p_magnet + *(lattice + idx)*2;
      //printf("Change Accepted\n");
    }else{
      //printf("Change Rejected\n");
    }
  }
  return 0;
}


int get_neighbours(int *neigh, int n_neigh, int *lattice, int n, int idx){
  /*
    Gets vertical and horizontal nearest neighbours and writes them in neigh
    0 left | 1 right | 2 up | 3 down
  */
  int place_i,place_j;
  place_i = floor(idx/n);
  place_j = idx - place_i*n;
  int m;  

  //Neighbours
  m = (place_j-1+n)%n + n*place_i;
  neigh[0] = *(lattice + m);
  m = (place_j+1+n)%n + place_i*n;
  neigh[1] = *(lattice + m);  
  m = place_j + n*((place_i-1+n)%n);
  neigh[2] = *(lattice + m);
  m = place_j +  n*((place_i+1+n)%n);;
  neigh[3] = *(lattice + m);

  return 0;
}
int print_data(int *lattice, int n, int *neigh, int n_neigh, int idx){
  /*
    Prints specific data of a selected site in idx and its neighbours
   */
  int place_i,place_j;
  place_i = floor(idx/n);
  place_j = idx - place_i*n;
  int m;  
  //Data
  printf("Change place: %d\n",idx);
  printf("Spin: %d, i:%d, j:%d\n",*(lattice+idx),place_i,place_j);
  printf("Neighbours\n");
  printf("Left: %d, Right: %d, Up: %d, Down: %d\n",neigh[0],neigh[1],neigh[2],neigh[3]);
  return 0;
}

int mc_table(double *mc_list, float T, float J, float B){
  /*
    Makes the list of possible delta energies in a system with interaction
    J and external magnetic field B. Writes it in mc_list.
   */
  mc_list[0] = exp(-(-8*J-2*B)/T);
  mc_list[1] = exp(-(-8*J+2*B)/T);
  mc_list[2] = exp(-(-4*J-2*B)/T);
  mc_list[3] = exp(-(-4*J+2*B)/T);
  mc_list[4] = exp(-(-2*B)/T);
  mc_list[5] = exp(-2*B/T);
  mc_list[6] = exp(-(4*J-2*B)/T);
  mc_list[7] = exp(-(4*J+2*B)/T);
  mc_list[8] = exp(-(8*J-2*B)/T);
  mc_list[9] = exp(-(8*J+2*B)/T);
  return 0;
}

int sgn(int x){
  /*
    Returns the sign of an int
   */
  return (x>0)-(x<0);
}

double energy_lattice(int *lattice, int n, float J, float B){
  /*
    Returns the energy of a lattice of size n with J and B 
    parameters of interaction and external magnetic field
  */
  double energy = 0.0;
  int place,spin_place;
  int neigh[4];
  
  for(place=0;place<n*n;place++){
    spin_place = *(lattice + place);
    get_neighbours(neigh,4,lattice,n,place);
    energy = energy - J*spin_place*neigh[1] - J*spin_place*neigh[3] - spin_place*B;
  }
  return energy;
}

int magnet_lattice(int *lattice, int n){
  /*
    Returns the magnetization of a lattice
    of size n
   */
  int magnet = 0.0;
  int place,spin_place;
 
  for(place=0;place<n*n;place++){
    spin_place = *(lattice + place);
    magnet = magnet + spin_place;
  }
  return magnet;
}
double mean(double *array,int arraysize){
  /*
    Returns the mean value of an array of doubles
   */
	int i;
	double prom = 0;
	for(i=0;i<arraysize;i++){
		prom=prom+array[i];	
	}
	prom=prom/arraysize;
	return prom;	
}
double disp(double *array,int arraysize){
  /*
    Returns the dispersion of an array of doubles
   */
	int i;
	double di = 0;
	double prom = mean(array,arraysize);
	
	for(i=0;i<arraysize;i++){
		di=di+(array[i]-prom)*(array[i]-prom);	
	}
	di=sqrt(di/arraysize);
	return di;
}
double autocorr(double *arr, int len_arr, int tau){
  /*
    Returns the autocorrelation value of a distance tau 
    of an array of doubles
   */
        double prom = mean(arr,len_arr);
	double di = disp(arr,len_arr);
	double partsum;
	int k;
	int end = len_arr - tau;
	for(k=0; k < end; k++){
	  partsum = partsum + (arr[k] - prom)*(arr[k+tau] - prom);
	}
	double corr = partsum/(len_arr - tau);
	corr = corr/(di*di);

	return corr;  
}
