#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "metropolis.h"
#include "lattice.h"


int main(int argc, char **argv) {
  
  float prob = 0.5;
  int niter;
  int n;
  float Tini, Tfin;
  float J,B; //Only positive values

  if (argc==7){
    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&Tini);
    sscanf(argv[3],"%f",&Tfin);
    sscanf(argv[4],"%f",&J);
    sscanf(argv[5],"%f",&B);
    sscanf(argv[6],"%d",&niter);
  }else{
    n = 16;
    Tini = 3.0;
    Tfin = 1.0;
    J = 1.0;
    B = 1.0;
    niter = 2000;
  }
  if(Tini<0 || Tfin <0 || B<0 || n<0 || niter<0 || J<0){
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
  char filename[100];
  sprintf(filename,"../results/EMT/MEvsTN%d.txt",n);
  FILE *fp;
  fp = fopen(filename,"w");
  fprintf(fp,"T\t\t\t<E>\t\t\t<M>\t\t\tV(E)\t\t\tV(M)\n");

  //Temperature Loop
  int nOfTemps = 100;
  int k;

  double Eprom;
  double Mprom;

  double Esqr;
  double Msqr;

  float T;

  //Table of energies initialization
  int energy_levels = 10;
  double mc_list[energy_levels];
  mc_table(mc_list,energy_levels,Tini,J,B);

  //First thermalization
  for (int i = 0; i < 3000000; i++) {
    metropolis(lattice, n, Tini, J, B, mc_list, &energy, &magnet);
  }


  int decorr = 10*n*n;
  int dataPoints;

  for(k=0; k<nOfTemps; k++){
    T = ((Tfin - Tini)*k)/(nOfTemps-1) + Tini;
    printf("%.2f\n",T);
    mc_table(mc_list,energy_levels,T,J,B);
  
    Eprom = 0.0; //Means
    Mprom = 0.0;

    Esqr = 0.0; //Means of E^2 and M^2
    Msqr = 0.0;

    dataPoints = 0;

    //Thermalization
    for (int i = 0; i < 1; i++) {
      metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
    }

    for (int i = 0; i < niter; i++) {
      metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
      if(i%decorr==0){
	Eprom = Eprom + energy/(n*n);
	Mprom = Mprom + (double)magnet/(n*n);
	Esqr = Esqr + (energy*energy)/(n*n*n*n);
	Msqr = Msqr + ((double)magnet*magnet)/(n*n*n*n);
	dataPoints = dataPoints + 1;
      }
    }
    
    Eprom = Eprom/dataPoints;
    Mprom = Mprom/dataPoints;

    Esqr = Esqr/dataPoints;
    Msqr = Msqr/dataPoints;
 
    double Evar = Esqr - Eprom*Eprom;
    double Mvar = Msqr - Mprom*Mprom;
    fprintf(fp,"%f\t\t%f\t\t%f\t\t%f\t\t%f\n",T,Eprom,Mprom,Evar,Mvar);

  }
  printf("Data Points: %d\n",dataPoints);
  fclose(fp);
  free(lattice);
  return 0;
}
