#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "dataRead.h"

int main(int argc, char **argv){
  /*
  if (argc==2){
    sscanf(argv[1],"%d",&n);
  }else{
    n = 16;
  }
  if(n<0){
     printf("ERROR\n");
     exit(EXIT_FAILURE);
  }
  */

  //Read temperatures
  FILE *temps = fopen("../results/Tbajadirecto1/temps.txt","r");
  float T = 0.0;

  while (fscanf(temps,"%f", &T) == 1) // Expects 1 successful conversions
    {
      char filename[100];
      sprintf(filename,"../results/Tbajadirecto1/data%.1f.txt",T);
      printf("%s\n",filename);
    
      FILE *fp = fopen(filename,"r");


      char ignore[1024];
      fgets(ignore, sizeof(ignore), fp);
      fgets(ignore, sizeof(ignore), fp);
      
      int freqPROM = 1;
      int stepIni = 200000;
      int stepFin = 2000000;
      double Eprom = 0.0;
      int Mprom = 0;
  
      decorrelatedMean(fp,freqPROM,stepIni,stepFin,&Eprom,&Mprom);

      printf("Eprom: %f, Mprom: %d\n",Eprom,Mprom);

    }
  if (feof(temps)) 
    {
      //End of the file
    }
  else
    {
      // Some other error interrupted the read
      printf("\nERROR\n");
    }
    
}

int decorrelatedMean(FILE *fp, int freqPROM, int stepIni, int stepFin, double *Eprom, int *Mprom){

  int step = 0;
  float energ = 0.0;
  int magnet = 0;
  int n = 0;

  while (fscanf(fp,"%d %f %d", &step, &energ, &magnet) == 3) // Expects 3 successful conversions
    {
      if(step>stepIni && step<stepFin){
	if(n%freqPROM == 0){
	  *(Eprom) = *(Eprom) + energ;
	  *(Mprom) = *(Mprom) + magnet;
	  n++;
	}
      }
    }
  if (feof(fp)) 
    {
      //End of the file
      *(Eprom) = *(Eprom)/n;
      *(Mprom) = *(Mprom)/n;
    }
  else
    {
      // Some other error interrupted the read
      printf("\nERROR\n");
    }
  return 0;
}
