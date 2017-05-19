#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"


int main(int argc, char **argv) {
  
  float prob;
  int niter;
  int n;
  float T;
  float B; //Only positive values

  if (argc==6){
    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&T);
    sscanf(argv[3],"%f",&B);
    sscanf(argv[4],"%d",&niter);
    sscanf(argv[5],"%f",&prob);
  }else{
    n = 16;
    T = 1.0;
    B = 1.0;
    niter = 2000;
    prob = 0.5;
  }
  if(T<0 || B<0 || n<0 || niter<0){
     printf("ERROR: Ingresar n, T , B , niter, prob mayores a 0\n");
     exit(EXIT_FAILURE);
  }
  
  int *lattice = malloc(n * n * sizeof(int));

  int energy_levels = 10;
  double mc_list[energy_levels];
  mc_table(mc_list,energy_levels,T,B);

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  double initial_energy = energy_lattice(lattice,n,B);
  int initial_magnet = magnet_lattice(lattice,n);

  double energy = initial_energy;
  int magnet = initial_magnet;
  
  int delta=0;
  int aux;

  print_lattice(lattice, n);
  for (int i = 0; i < niter; i++) {
    aux = metropolis(lattice, n, T, B, mc_list, &energy, &magnet);
    delta = delta + aux;
  }
  printf("\n\n\n");
  print_lattice(lattice, n);

  double final_energy = energy_lattice(lattice,n,B);
  int final_magnet = magnet_lattice(lattice,n);

  printf("\n Initial E: %f, Final E: %f\n",initial_energy,final_energy);
  printf("\n Final E with deltas: %f\n",initial_energy + delta);
  
  printf("\n Initial M: %d, Final M: %d\n",initial_magnet,final_magnet);

  printf("\n Final M with data: %d\n",magnet);
  printf("\n Final E with data: %f\n",energy);

  /*
  print_lattice(lattice, n);
  metropolis(lattice, n ,T);
  print_lattice(lattice, n);
  */
  
  free(lattice);
  return 0;
}
