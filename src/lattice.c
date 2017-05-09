#include "lattice.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fill_lattice(int *lattice, int n, float p) {
  int i;
  float numrand;
  for(i = 0; i<n*n; i++){
    numrand = (float)rand()/(float)RAND_MAX;  
    if(numrand < p){
      *(lattice+i) = 1;
    }else{
      *(lattice+i) = -1;
    }
  }
  return 0;
}

int print_lattice(int *lattice, int n) {
  int i,j;
  for(i = 0; i<n; i++){
    for(j = 0; j<n; j++){
      printf("%3d",*(lattice+i*n+j));
    printf("\n");
  }
  return 0;
}
