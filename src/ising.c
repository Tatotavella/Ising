#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"


int main(int argc, char **argv) {
  
  float prob = 0.5;
  long int niter;
  int n;
  float T;
  float J,B;

  if (argc==6){
    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&T);
    sscanf(argv[3],"%f",&J);
    sscanf(argv[4],"%f",&B);
    sscanf(argv[5],"%ld",&niter);
  }else{
    n = 16;
    T = 1.0;
    J = 1.0;
    B = 1.0;
    niter = 2000;
  }
  if(T<0 || n<0 || niter<0){
     printf("ERROR: Ingresar n, T , niter mayores a 0\n");
     exit(EXIT_FAILURE);
  }
  
  int *lattice = malloc(n * n * sizeof(int));

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  //Initial energy and magnetization
  double energy = energy_lattice(lattice,n,J,B);
  int magnet = magnet_lattice(lattice,n);


  print_lattice(lattice, n);

  //Table of energies initialization
  int energy_levels = 10;
  double mc_list[energy_levels];
  mc_table(mc_list,energy_levels,T,J,B);

  int i;

  for (i = 0; i < niter; i++) {
      metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
  }

  printf("\n\n\n");
  print_lattice(lattice,n);
  printf("\n\n\n");
  printf("Final Energy: %f, Final Magnet %d\n",energy,magnet);
  printf("Final Energy: %f, Final Magnet %d\n",energy_lattice(lattice,n,J,B),magnet_lattice(lattice,n));


  free(lattice);
  return 0;
}
