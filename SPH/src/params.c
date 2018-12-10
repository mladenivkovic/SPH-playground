#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "params.h"



/*============================================
 * This function checks the parameters
 * that have been read in and makes sure that
 * the simulation can be run with the given
 * parameters, or stops the run otherwise.
 *============================================*/

void check_params(params* p){

  int error = 0;


  if (p->verbose){
    printf("Am verbose\n");
  }
  else {
    printf("Am quiet\n");
  }

  if (p->levelmax == 0) {
    printf("Got levelmax = 0. Weird, but ok I guess...\n");
  }

  if (p->nstepmax==0 && p->tmax==0) {
    printf("Got no info on when to end. You need to specify either nstepmax or tmax in your parameter file.\n");
    error = 1;
  }


  if (p->unit_m==0){
    printf("unit_m can't be zero.");
    error=1;
  }
  if (p->unit_l==0){
    printf("unit_l can't be zero.");
    error=1;
  }
  if (p->unit_t==0){
    printf("unit_t can't be zero.");
    error=1;
  }


  if (error){
    exit(602);
  }

}








/*==========================================
 * Initialize parameters to default values
 *==========================================*/

void init_params(params * p){

  p->nstepmax = 0;
  p->step=0;
  p->tmax = 0.0;
  p->t=0.0;
  p->dt_max=1e10;
  p->boxlen=1.0;
  p->npart=0;
  p->levelmax = 0;
  p->verbose = 0;
  p->debug = 0;

  strcpy(p->paramfilename, "");
  strcpy(p->datafilename,  "");

  p->unit_m = 1.0;
  p->unit_l = 1.0;
  p->unit_t = 1.0;

}



/*==============================================
 * Print parameters in use.
 *==============================================*/

void print_params(params * p){
  printf("==================================================\n");
  printf("Starting simulation. Parameters are:\n");

  printf("Verbose?              ");
  if (p->verbose) {
    printf("True\n");
  } else {
    printf("False\n");
  }
  printf("Printing debug info?  ");
  if (p->verbose) {
    printf("True\n");
  } else {
    printf("False\n");
  }

  printf("levelmax:             %d\n", p->levelmax);
  printf("nstepmax:             %d\n", p->nstepmax);
  printf("tmax:                 %g\n", p->tmax);
  printf("boxlen:               %g\n", p->boxlen);
  printf("npart:                %d\n", p->npart);


  printf("\n");
  printf("Units:\n");
  printf("unit_m:               %g\n", p->unit_m);
  printf("unit_l:               %g\n", p->unit_l);
  printf("unit_t:               %g\n", p->unit_t);
  printf("==================================================\n");

}
