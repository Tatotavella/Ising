#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
  int n = 17;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 0.1;
  int niter = 2000;
  srand(time(NULL));
  fill_lattice(lattice, n, prob);

  double initial_energy = energy_lattice(lattice,n);
  double initial_magnet = magnet_lattice(lattice,n);
  int delta_e=0;
  int aux;

  print_lattice(lattice, n);
  for (int i = 0; i < niter; i++) {
    aux = metropolis(lattice, n, T);
    delta_e = delta_e + aux;
  }
  printf("\n\n\n");
  print_lattice(lattice, n);

  double final_energy = energy_lattice(lattice,n);
  double final_magnet = magnet_lattice(lattice,n);

  printf("\n Initial E: %f, Final E: %f\n",initial_energy,final_energy);
  printf("\n Final E with deltas: %f\n",initial_energy + delta_e);
  
  printf("\n Initial M: %f, Final M: %f\n",initial_magnet,final_magnet);

  /*
  print_lattice(lattice, n);
  metropolis(lattice, n ,T);
  print_lattice(lattice, n);
  */
  
  free(lattice);
  return 0;
}
