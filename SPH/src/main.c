/* ======================================== 
 *  
 * A rudimentary SPH code.
 *
 * Usage: ./sph paramfile.txt datafile.dat
 *  
 * ======================================== */



#include <stdio.h>

#include "io.h"
#include "globals.h"

void check_parameters();


int main(int argc, char* argv[]){

/* TODO: change this */
#ifndef NDIM
#define NDIM 3
printf("You didn't define the number of dimensions in the Makefile. Compiling with NDIM=3\n");
#endif

  globalparams g;
  g.levelmax = 0;
  g.verbose = 0;
  g.nstepmax = 0;
  g.tmax = 0.0;

  read_cmdlineargs(argc, argv, &g);
  read_paramfile(&g);
  check_parameters(&g);

  return(0);

}




void check_parameters(globalparams* g){

  if (g->verbose){
    printf("Am verbose\n");
  }
  else {
    printf("Am quiet\n");
  }

  if (g->levelmax == 0) {
    printf("Got levelmax = 0. Weird, but ok I guess...\n");
  }

  if (g->nstepmax==0 && g->tmax==0) {
    printf("Got no info on when to end. You need to specify either nstepmax or tmax in your parameter file.\n");
  }

}
