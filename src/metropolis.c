#include "metropolis.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int metropolis(int *lattice, int n, float T, float B, double *mc_list, double *p_ener, int *p_magnet) {
  int place = pick_site(lattice,n);
  int delta = flip(lattice,n,place,T,B,mc_list,p_ener,p_magnet);
  return delta;
}

int pick_site(int *lattice, int n) {
  float rnd = (float)rand()/(float)RAND_MAX; 
  int place = (int)(n*n*rnd);
  return place;
}

int flip(int *lattice, int n, int idx, float T, float B, double *mc_list, double *p_ener, int *p_magnet) {

  //Get neighbours
  int neigh[4];// 0 left | 1 right | 2 up | 3 down
  get_neighbours(neigh,4,lattice,n,idx);

  //print_data(lattice, n, neigh, 4, idx);

  //Calcute energy difference and flip
  int spin_place = *(lattice+idx);
  int delta_e = 2*spin_place*(neigh[0]+neigh[1]+neigh[2]+neigh[3]);
  float delta_b = 2*B*spin_place; 
  float delta = delta_e + delta_b;
  
  double prob;

  if(delta<=0){//Flip

    prob = 1.0;
    *(lattice + idx) = -1*(*(lattice + idx));
    //Write energy and magnetization change
    *p_ener = *p_ener + delta;
    *p_magnet = *p_magnet + *(lattice + idx)*2;
    //printf("Delta E: %d, Delta B: %.4f, Prob: %f\n",delta_e,delta_b,prob);

  }else{ //Coin to flip

    float coin = (float)rand()/(float)RAND_MAX;
    int mc_idx = 2*(delta_e + 8)/4 + (delta_b + 2*B)/2*B;
    prob = mc_list[mc_idx];
    if(coin < prob){
      *(lattice + idx) = -1*(*(lattice + idx));
      //Write energy and magnetization change
      *p_ener = *p_ener + delta;
      *p_magnet = *p_magnet + *(lattice + idx)*2;
      //printf("Delta E: %d, Delta B: %.4f, Prob: %f\n",delta_e,delta_b,prob);
    }else{
      //printf("Delta E: %d, Delta B: %.4f, Prob: %f\n",delta_e,delta_b,prob);
      delta = 0;//To not count it in energy change
    }
  }

  //printf("Delta E: %d, Delta B: %4f, Prob: %4f\n",delta_e,delta_b,prob);

  return delta;
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

int mc_table(double *mc_list, int list_length, float T, float B){
  if(list_length==5){
    //MC energy list. Indexes correspond to -8,-4,0,4,8 delta energies
    mc_list[0] = 1.0;
    mc_list[1] = 1.0;
    mc_list[2] = 1.0;
    mc_list[3] = exp(-4/T);
    mc_list[4] = exp(-8/T);
  }else if(list_length==10){
    //MC energy list. Indexes correspond to -8-2B,-8+2B,-4-2B,-4+2B,... delta energies
    mc_list[0] = exp(-(-8-2*B)/T);
    mc_list[1] = exp(-(-8+2*B)/T);
    mc_list[2] = exp(-(-4-2*B)/T);
    mc_list[3] = exp(-(-4+2*B)/T);
    mc_list[4] = exp(-(-2*B)/T);
    mc_list[5] = exp(-2*B/T);
    mc_list[6] = exp(-(4-2*B)/T);
    mc_list[7] = exp(-(4+2*B)/T);
    mc_list[8] = exp(-(8-2*B)/T);
    mc_list[9] = exp(-(8+2*B)/T);
  }
  return 0;
}

int sgn(int x){
  return (x>0)-(x<0);
}

double energy_lattice(int *lattice, int n, float B){
  double energy = 0.0;
  int place,spin_place;
  int neigh[4];
  
  for(place=0;place<n*n;place++){
    spin_place = *(lattice + place);
    get_neighbours(neigh,4,lattice,n,place);
    energy = energy - spin_place*neigh[1] - spin_place*neigh[3] - spin_place*B;
  }
  return energy;
}

int magnet_lattice(int *lattice, int n){
  int magnet = 0.0;
  int place,spin_place;
 
  for(place=0;place<n*n;place++){
    spin_place = *(lattice + place);
    magnet = magnet + spin_place;
  }
  //magnet = magnet/(double)(n*n);
  return magnet;
}
