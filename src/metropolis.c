#include "metropolis.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int sgn(int x){
  return (x>0)-(x<0);
}

int metropolis(int *lattice, int n, float T) {

  //MC energy list. Indexes correspond to -8,-4,0,4,8 delta energies
  double mc_list[5];
  mc_list[0] = 1.0;
  mc_list[1] = 1.0;
  mc_list[2] = 1.0;
  mc_list[3] = exp(-4/T);
  mc_list[4] = exp(-8/T);

  //Pick a site to change
  float rnd;
  int place;
  rnd = (float)rand()/(float)RAND_MAX; 
  place = floor(n*n*rnd); 

  //Get neighbours
  int neigh[4];// 0 left | 1 right | 2 up | 3 down
  int place_i,place_j;
  place_i = floor(place/n);
  place_j = place - place_i*n;
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

  //Data
  printf("Change place: %d\n",place);
  printf("Spin: %d, i:%d, j:%d\n",*(lattice+place),place_i,place_j);
  printf("Neighbours\n");
  printf("Left: %d, Right: %d, Up: %d, Down: %d\n",neigh[0],neigh[1],neigh[2],neigh[3]);

  //Calcute energy difference
  int spin_place = *(lattice+place);
  int delta_e = 2*spin_place*(neigh[0]+neigh[1]+neigh[2]+neigh[3]); 
  double prob = mc_list[(delta_e+8)/4];
  printf("Delta E: %d, Prob: %4f\n",delta_e,prob);

  //Flip a coin, evaluate probability and change or not
  float coin = (float)rand()/(float)RAND_MAX;
  if(coin < prob){
    *(lattice + place) = -1*(*(lattice + place));
    printf("Change Accepted!\n");
  }else{
    printf("Change Rejected!\n");
  }

  return 0;
}

int pick_site(int *lattice, int n) {
  
  return 0;
}

int flip(int *lattice, int n, float T) {
  
  return 0;
}
