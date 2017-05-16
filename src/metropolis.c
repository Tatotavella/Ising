#include "metropolis.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int metropolis(int *lattice, int n, float T) {
  int place = pick_site(lattice,n);
  flip(lattice,n,place,T);
  return 0;
}

int pick_site(int *lattice, int n) {
  float rnd = (float)rand()/(float)RAND_MAX; 
  int place = (int)(n*n*rnd);
  return place;
}

int flip(int *lattice, int n, int idx, float T) {
  /*
  //MC energy list. Indexes correspond to -8,-4,0,4,8 delta energies
  double mc_list[5];
  mc_list[0] = 1.0;
  mc_list[1] = 1.0;
  mc_list[2] = 1.0;
  mc_list[3] = exp(-4/T);
  mc_list[4] = exp(-8/T);
  //*/
  double mc_list[5];
  mc_table(mc_list, 5, T);

  
  //Get neighbours
  int neigh[4];// 0 left | 1 right | 2 up | 3 down
  get_neighbours(neigh,4,lattice,n,idx);

  print_data(lattice, n, neigh, 4, idx);

  //Calcute energy difference and flip
  int spin_place = *(lattice+idx);
  int delta_e = 2*spin_place*(neigh[0]+neigh[1]+neigh[2]+neigh[3]); 
  double prob;

  if(delta_e<=0){//Flip

    prob = 1.0;
    *(lattice + idx) = -1*(*(lattice + idx));

  }else{ //Coin to flip

    float coin = (float)rand()/(float)RAND_MAX;
    prob = mc_list[(delta_e+8)/4];
    if(coin < prob){
      *(lattice + idx) = -1*(*(lattice + idx));
    }    
  }

  printf("Delta E: %d, Prob: %4f\n",delta_e,prob);

  return 0;
}

int get_neighbours(int *neigh, int n_neigh, int *lattice, int n, int idx){

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

int mc_table(double *mc_list, int list_lenght, float T){
  //MC energy list. Indexes correspond to -8,-4,0,4,8 delta energies
  mc_list[0] = 1.0;
  mc_list[1] = 1.0;
  mc_list[2] = 1.0;
  mc_list[3] = exp(-4/T);
  mc_list[4] = exp(-8/T);
  return 0;
}

int sgn(int x){
  return (x>0)-(x<0);
}
