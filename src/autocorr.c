#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"


int main(int argc, char **argv) {
  
  float prob = 0.5;
  long int niter;
  int n;
  float Tini,Tfin;
  float J,B; //Only positive values

  if (argc==7){
    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&Tini);
    sscanf(argv[3],"%f",&Tfin);
    sscanf(argv[4],"%f",&J);
    sscanf(argv[5],"%f",&B);
    sscanf(argv[6],"%ld",&niter);
  }else{
    n = 16;
    Tini = 2.6;
    Tfin = 2.6;
    J = 1.0;
    B = 1.0;
    niter = 2000;
  }
  if(Tini<0 || Tfin<0 || B<0 || n<0 || niter<0 || J<0){
     printf("ERROR: Ingresar n, T , J, B, niter mayores a 0\n");
     exit(EXIT_FAILURE);
  }
  
  int *lattice = malloc(n * n * sizeof(int));

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  //Initial energy and magnetization
  double *energy = malloc(sizeof(double)*niter);
  energy[0] = energy_lattice(lattice,n,J,B);
  int *magnet = malloc(sizeof(int)*niter);
  magnet[0] = magnet_lattice(lattice,n);


  //Data writing
  FILE *fp = fopen("../results/bimodal/MEvsT.txt","w");
  fprintf(fp,"T\t\t\t<E>\t\t\t<M>\t\t\tV(E)\t\t\tV(M)\n");


  //Temperature Loop
  int nOfTemps = 5;
  int k;

  double Eprom;
  double Mprom;

  double Esqr;
  double Msqr;

  long int i;
  
  //Table of energies initialization
  int energy_levels = 10;
  double mc_list[energy_levels];
  mc_table(mc_list,energy_levels,Tini,J,B);

  //First thermalization
  for (i = 0; i < 3000000; i++) {
    metropolis(lattice, n, Tini, J, B, mc_list, &energy, &magnet);
  }

  long int freqOUT = 1e4;
  long int screenOUT = niter/5;
  int dataPoints;
  float T;

  FILE *dt;  

  for(k=0; k<nOfTemps; k++){
    T = ((Tfin - Tini)*k)/(nOfTemps-1) + Tini;
    
    mc_table(mc_list,energy_levels,T,J,B);

    //Data writing
    char filename[100];
    sprintf(filename,"../results/bimodal/data%.2f.txt",T);
    dt = fopen(filename,"w");
    fprintf(dt,"Step\t\t\tEnergy\t\t\tMagnetization\n");
    printf("%.2f\n",T);
  
    Eprom = 0.0; //Means
    Mprom = 0.0;

    Esqr = 0.0; //Means of E^2 and M^2
    Msqr = 0.0;

    dataPoints = 0;
    
    //Thermalization
    for (i = 0; i < 10000; i++) {
      metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
    }
    
    for (i = 0; i < niter; i++) {
      metropolis(lattice, n, T, J, B, mc_list, &energy, &magnet);
      if(i%freqOUT==0){
	fprintf(dt,"%e\t\t\t%f\t\t\t%d\n",(float)i,energy/(n*n),magnet);
	Eprom = Eprom + energy/(n*n);
	Mprom = Mprom + (double)magnet/(n*n);
	Esqr = Esqr + (energy*energy)/(n*n*n*n);
	Msqr = Msqr + ((double)magnet*magnet)/(n*n*n*n);
	dataPoints = dataPoints + 1;
      }
      if(i%screenOUT==0){
	printf("Step - %.2e\n",(float)i);
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
  fclose(dt);
  fclose(fp);
  free(lattice);
  free(energy);
  free(magnet);
  return 0;
}
