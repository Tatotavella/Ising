#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "metropolis.h"
#include "lattice.h"


int main(int argc, char **argv) {

  /*
    Makes a ramp temperature from Tini to Tfin saves the data in
    "../results/EMT/MEvsTN"SIZE".txt Data is mean magnetization and
    energy and its variances. The decorrelation step is set to
    10*N*N. First thermalization is set to 3000000 steps.
   */
  
  float prob = 0.5;
  int niter;
  int n;
  float Tini, Tfin;
  float J,B;
  int nOfTemps;

  if (argc==8){
    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&Tini);
    sscanf(argv[3],"%f",&Tfin);
    sscanf(argv[4],"%f",&J);
    sscanf(argv[5],"%f",&B);
    sscanf(argv[6],"%d",&niter);
    sscanf(argv[7],"%d",&nOfTemps);
  }else{
    printf("\nInput form: ./temp_ramp N InitialTemp FinalTemp J B NumberOfSteps NumberOfTemperatures\n\n");
    printf("Makes a ramp of temperature from Tini to Tfin and saves the data in ../results/EMT/MEvsTN\"SIZE\".txt\nThe data is mean magnetization, energy and its variances.\nThe decorrelation step is set to 10*N*N. First thermalization is set to 3000000 steps.\n\n");
    printf("The data is analyzed with the script ../analysis/MET.py \n\n");
    exit(EXIT_FAILURE);
  }
  if(Tini<0 || Tfin <0 || n<0 || niter<0 || nOfTemps<0){
     printf("ERROR: Positive n, T, niter, nOfTemps\n");
     exit(EXIT_FAILURE);
  }
  
  int *lattice = malloc(n * n * sizeof(int));

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  //Initial energy and magnetization
  double energy = energy_lattice(lattice,n,J,B);
  int magnet = magnet_lattice(lattice,n);

  //Data writing
  char filename[100];
  sprintf(filename,"../results/EMT/MEvsTN%d.txt",n);
  FILE *fp;
  fp = fopen(filename,"w");
  fprintf(fp,"Sim Data: Program: %s , Size: %d , Tini: %f , Tfin: %f , J: %f , B: %f , niter: %d , nOfTemps: %d\n",argv[0],n,Tini,Tfin,J,B,niter,nOfTemps);
  fprintf(fp,"T\t\t\t<E>\t\t\t<M>\t\t\tV(E)\t\t\tV(M)\n");

  //Temperature Loop
  int k;

  double Eprom;
  double Mprom;

  double Esqr;
  double Msqr;

  float T;

  //Table of energies initialization
  int energy_levels = 10;
  double mc_list[energy_levels];
  mc_table(mc_list,Tini,J,B);

  //First thermalization
  for (int i = 0; i < 3000000; i++) {
    metropolis(lattice, n, Tini, J, B, mc_list, &energy, &magnet);
  }


  int decorr = 10*n*n;
  int dataPoints;

  printf("Actual temperature: %.2f,  0%% of simulation\n",T);
  
  for(k=0; k<nOfTemps; k++){
    T = ((Tfin - Tini)*k)/(nOfTemps-1) + Tini;
    printf("\033[A\33[2K\rActual temperature: %.2f, %d%% of simulation\n",T,(int)((float)k*100)/(nOfTemps-1));
    mc_table(mc_list,T,J,B);
  
    Eprom = 0.0; //Means
    Mprom = 0.0;

    Esqr = 0.0; //Means of E^2 and M^2
    Msqr = 0.0;

    dataPoints = 0;

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
  printf("Data Points per temperature: %d\n",dataPoints);
  fclose(fp);
  free(lattice);
  return 0;
}
