#include "metropolis.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int metropolis(int *lattice, int n, float T) {
  //Pick a site to change
  
  float rnd;
  int place;
  
  rnd = (float)rand()/(float)RAND_MAX; 
  place = floor(n*n*rnd); 

  //Get neighbours

  int neigh[4];// 0 left | 1 right | 2 up | 3 down
  //Border spin
  if(place < n){ //First row 
    if(place == 0){
      neigh[0] = *(lattice + n-1);//Periodic
      neigh[1] = *(lattice + place + 1);
      neigh[2] = *(lattice + place + n*(n-1));//Periodic
      neigh[3] = *(lattice + place + n);
    }else if(place == n-1){
      neigh[0] = *(lattice + place - 1);
      neigh[1] = *(lattice);//Periodic
      neigh[2] = *(lattice + place + n*(n-1));//Periodic
      neigh[3] = *(lattice + place + n);
    }else{
      neigh[0] = *(lattice + place - 1);
      neigh[1] = *(lattice + place + 1);
      neigh[2] = *(lattice + place + n*(n-1));//Periodic
      neigh[3] = *(lattice + place + n);
    }
  }else if(place >= (n-1)*n){ //Last row
    if(place == n*(n-1)){
      neigh[0] = *(lattice + n*n-1);//Periodic
      neigh[1] = *(lattice + place + 1);
      neigh[2] = *(lattice + place - n);
      neigh[3] = *(lattice);//Periodic
    }else if(place == n*n-1){
      neigh[0] = *(lattice + place - 1);
      neigh[1] = *(lattice + n*(n-1));//Periodic
      neigh[2] = *(lattice + place - n);
      neigh[3] = *(lattice + n-1);//Periodic
    }else{
      neigh[0] = *(lattice + place - 1);
      neigh[1] = *(lattice + place + 1);
      neigh[2] = *(lattice + place - n);
      neigh[3] = *(lattice + place - n*(n-1));//Periodic
    }
  }else if(place % n == 0){ //First column
     if(place == 0){
      neigh[0] = *(lattice + n-1);//Periodic
      neigh[1] = *(lattice + place + 1);
      neigh[2] = *(lattice + place + n*(n-1));//Periodic
      neigh[3] = *(lattice + place + n);
    }else if(place == n*(n-1)){
      neigh[0] = *(lattice + n*n-1);//Periodic
      neigh[1] = *(lattice + place + 1);
      neigh[2] = *(lattice + place - n);
      neigh[3] = *(lattice);//Periodic
    }else{
      neigh[0] = *(lattice + place + n-1);//Periodic
      neigh[1] = *(lattice + place + 1);
      neigh[2] = *(lattice + place - n);
      neigh[3] = *(lattice + place + n);
    }
  }else if((place+1) % n == 0){ //Last column
     if(place == n-1){
      neigh[0] = *(lattice + place - 1);
      neigh[1] = *(lattice);//Periodic
      neigh[2] = *(lattice + place + n*(n-1));//Periodic
      neigh[3] = *(lattice + place + n);
    }else if(place == n*n-1){
      neigh[0] = *(lattice + place - 1);
      neigh[1] = *(lattice + n*(n-1));//Periodic
      neigh[2] = *(lattice + place - n);
      neigh[3] = *(lattice + n-1);//Periodic
    }else{
      neigh[0] = *(lattice + place - 1);
      neigh[1] = *(lattice + place - (n-1));//Periodic
      neigh[2] = *(lattice + place - n);
      neigh[3] = *(lattice + place + n);
    }
  }else{ //Inner spin
    neigh[0] = *(lattice + place - 1);
    neigh[1] = *(lattice + place + 1);
    neigh[2] = *(lattice + place - n);
    neigh[3] = *(lattice + place + n);
  }
  int place_i,place_j;
  place_i = floor(place/n);
  place_j = place - place_i*n;
  printf("Change place\n");
  printf("Spin: %d, i:%d, j:%d\n",*(lattice+place),place_i,place_j);
  printf("Neighbours\n");
  printf("Left: %d, Right: %d, Up: %d, Down: %d\n",neigh[0],neigh[1],neigh[2],neigh[3]);
  //Calcute energy difference


  //Flip a coin and evaluate probability

  //Make the final change


  return 0;
}

int pick_site(int *lattice, int n) {
  
  return 0;
}

int flip(int *lattice, int n, float T) {
  
  return 0;
}
