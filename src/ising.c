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

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  //Initial energy and magnetization
  double energy = energy_lattice(lattice,n,J,B);
  int magnet = magnet_lattice(lattice,n);


  //print_lattice(lattice, n);

  //Data writing
  FILE *fp = fopen("../results/MEvsT.txt","w");
  fprintf(fp,"Temp\t\t\tMeanEnergy\t\t\tMeanMagnetization\n");

  //Data writing
  
  FILE *dt = fopen("../results/data.txt","w");
  fprintf(dt,"Step\t\t\tEnergy\t\t\tMagnetization\n");
  


  //Temperature Loop
  float Tini = 2.26;
  float Tfin = 2.26;
  int nOfTemps = 1;
  int k;

  float Eprom;
  float Mprom;

  T = Tini;

  //Table of energies initialization
  int energy_levels = 10;
  double mc_list[energy_levels];
  mc_table(mc_list,energy_levels,T,J,B);

  //First thermalization
  for (int i = 0; i < 3000000; i++) {
    metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
  }

  int freqOUT = 1000000;

  for(k=0; k<nOfTemps; k++){
    //T = ((Tfin - Tini)*k)/(nOfTemps-1) + Tini;
    T = 2.26;
    
    mc_table(mc_list,energy_levels,T,J,B);
  
    Eprom = 0.0;
    Mprom = 0.0;
    
    //Thermalization
    for (int i = 0; i < 50000; i++) {
      metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
    }

    for (int i = 0; i < niter; i++) {
      metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
      Eprom = Eprom + energy;
      Mprom = Mprom + magnet;
      if(i%freqOUT==0){
	fprintf(dt,"%d\t\t\t%f\t\t\t%d\n",i,energy/(n*n),magnet);
      }
    }
 
    Eprom = Eprom/(n*n*niter);
    Mprom = Mprom/(n*n*niter);
    fprintf(fp,"%f\t\t\t%f\t\t\t%f\n",T,Eprom,Mprom);

  }
  fclose(dt);
  fclose(fp);
  free(lattice);
  return 0;
}
