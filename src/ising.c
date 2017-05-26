#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"


int main(int argc, char **argv) {
  
  float prob = 0.5;
  int niter;
  int n;
  float T;
  float J,B; //Only positive values

  if (argc==6){
    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&T);
    sscanf(argv[3],"%f",&J);
    sscanf(argv[4],"%f",&B);
    sscanf(argv[5],"%d",&niter);
  }else{
    n = 16;
    T = 1.0;
    J = 1.0;
    B = 1.0;
    niter = 2000;
  }
  if(T<0 || B<0 || n<0 || niter<0 || J<0){
     printf("ERROR: Ingresar n, T , J, B, niter mayores a 0\n");
     exit(EXIT_FAILURE);
  }
  
  int *lattice = malloc(n * n * sizeof(int));

  //Table of energies initialization
  int energy_levels = 10;
  double mc_list[energy_levels];
  mc_table(mc_list,energy_levels,T,J,B);

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  //Initial energy and magnetization
  double initial_energy = energy_lattice(lattice,n,J,B);
  int initial_magnet = magnet_lattice(lattice,n);
  //printf("\n Initial E: %f\n",initial_energy);
  //printf("\n Initial M: %d\n",initial_magnet);

  double energy = initial_energy;
  int magnet = initial_magnet;

  //Thermalization
  for (int i = 0; i < 50000; i++) {
    metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
  }
  
  
  FILE *fp = fopen("../results/data.txt","w");
  fprintf(fp,"n\t%d\tT\t%f\tJ\t%f\tB\t%f\tniter\t%d\n",n,T,J,B,niter);
  fprintf(fp,"Step\t\t\tEnergy\t\t\tMagnetization\n");
  
  //print_lattice(lattice, n);
  for (int i = 0; i < niter; i++) {
    metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
    fprintf(fp,"%d\t\t\t%f\t\t\t%d\n",i,energy,magnet);
  }
  fclose(fp);
  //printf("\n\n\n");
  //print_lattice(lattice, n);

  double final_energy = energy_lattice(lattice,n,J,B);
  int final_magnet = magnet_lattice(lattice,n);

  //printf("\n Finals M:%d, E:%f\n",final_magnet,final_energy);
  
  //printf("\n Final M: %d\n",magnet);
  //printf("\n Final E: %f\n",energy);
 
  free(lattice);
  return 0;
}
