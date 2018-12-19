/*==============*/
/* IO routines. */
/*==============*/

#include "params.h"
#include "part.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 200



/* ====================================================================== */
/* This function reads in the command line arguments and stores them in   */
/* the globalparams struct                                                */
/* ====================================================================== */
void read_cmdlineargs(int argc, char* argv[], params* p){

  if (argc < 3){
    printf("Too few arguments given. Run this program with ./sph paramfile datafile\n");
    exit(600);
  }
  else {

    strcpy(p->paramfilename, argv[1]);
    strcpy(p->datafilename, argv[2]);
  };

}




/* ====================================================================== */
/* Read in parameter file, store read in global parameters.               */
/* ====================================================================== */
void read_paramfile(params* p){

  //open file
  FILE *par = fopen(p->paramfilename, "r");

  // check if file exists
  if (par == NULL) { 
    printf("Error: file '%s' not found.\n", p->paramfilename);
    exit(603);
  }

  char varname[MAX_LINE_SIZE] ;
  char varvalue[MAX_LINE_SIZE] ;
  char tempbuff[MAX_LINE_SIZE] ;

  
  while (fgets(tempbuff,MAX_LINE_SIZE,par))
  // fgets(str_buff, n,filepointer) :
  // gets n characters from file in filepointer and stores them
  // in str_buff.
  // returns 0 if EoF is reached.
  
  {

    // check whether tempbuff is empty line
    int isempty = 0;
    for (int i = 0; i<MAX_LINE_SIZE; i++){
      if (tempbuff[i] != ' '){
        if (tempbuff[i] == '\n'){
          isempty = 1;
        }
        break;
      }
    }

    if (isempty) continue;


    sscanf(tempbuff, "%20s = %56[^\n]\n", varname, varvalue);
    // reads formatted input from a string, writes it in
    // the variables given after the format string.
    // The format used is <string> separator <=> <string> ends with <;>
  
    if (strcmp(varname,"verbose") == 0) {
      p->verbose = atoi(varvalue);
    } 
    else if (strcmp(varname, "debug") == 0){
      p->debug = atoi(varvalue);
    }
    else if (strcmp(varname, "nx") == 0){
      p->nx = atoi(varvalue);
    }
    else if (strcmp(varname, "nneigh") == 0){
      p->nneigh = atoi(varvalue);
    }
    else if (strcmp(varname, "nstepmax") == 0){
      p->nstepmax = atoi(varvalue);
    }
    else if (strcmp(varname, "tmax")==0){
      p->tmax = atof(varvalue);
    }
    else if (strcmp(varname, "unit_m")==0){
      p->unit_m = atof(varvalue);
    }
    else if (strcmp(varname, "unit_l")==0){
      p->unit_l = atof(varvalue);
    }
    else if (strcmp(varname, "unit_t")==0){
      p->unit_t = atof(varvalue);
    }
    else if (strcmp(varname, "//")==0) {
      // ignore comments
      continue;
    }
    else if (strcmp(varname, "/*")==0) {
      // ignore comments
      continue;
    }
    else if (strcmp(varname, "")==0) {
      // ignore comments
      continue;
    }
    else{
      printf("Unrecongized parameter : \"%s\"\n", varname);
    }
  }

  fclose(par);

}








/* ====================================================================== */
/* Read in initial condition file                                         */
/* ====================================================================== */
void read_datafile(params* p, part* parts){

  //open file
  FILE *dat = fopen(p->datafilename, "r");

  // check if file exists
  if (dat == NULL) { 
    printf("Error: file '%s' not found.\n", p->datafilename);
    exit(604);
  }

  char tempbuff[MAX_LINE_SIZE];

  
  if (p->debug) printf("Reading data file.\n");

  
  if (!fgets(tempbuff, MAX_LINE_SIZE, dat)){
    printf("Error reading IC: couldn't read boxlen\n");
    exit(606);
  };
  sscanf(tempbuff, "%le", &(p->boxlen));

  if (!fgets(tempbuff, MAX_LINE_SIZE, dat)){
    printf("Error reading IC: couldn't read npart\n");
    exit(607);
  };
  sscanf(tempbuff, "%d", &(p->npart));


  /* check that you have enough particles to work with */
  if (p->npart < p->nneigh){
    printf("Error: Can't run with %d particles while demanding %d neighbours. Quitting.\n", p->npart, p->nneigh);
    exit(1);
  }




  /* Allocate particle arrays. */
  if (p->debug) printf("Allocating particle arrays.\n");
  parts->x        = malloc(p->npart*sizeof(double));
  parts->y        = malloc(p->npart*sizeof(double));
  parts->z        = malloc(p->npart*sizeof(double));
  parts->vx       = malloc(p->npart*sizeof(double));
  parts->vy       = malloc(p->npart*sizeof(double));
  parts->vz       = malloc(p->npart*sizeof(double));
  parts->m        = malloc(p->npart*sizeof(double));
  parts->h        = malloc(p->npart*sizeof(double));
  parts->P        = malloc(p->npart*sizeof(double));
  parts->rho      = malloc(p->npart*sizeof(double));
  parts->cellind  = malloc(p->npart*sizeof(int));


  /* read in particles, initialize unread properties */
  for (int i=0; i<p->npart; i++){
    if (!fgets(tempbuff, MAX_LINE_SIZE, dat)){
      printf("Error reading IC: stuck at particle index %d out of %d\n", i, p->npart);
      exit(605);
    };
    /* asterisks: don't store commas that I'm skipping */
    sscanf(tempbuff, "%le, %le, %le, %le, %le, %le, %le*", \
      &parts->x[i], &parts->y[i], &parts->z[i],    \
      &parts->vx[i], &parts->vy[i], &parts->vz[i], \
      &parts->m[i]);
      parts->h[i] = 0;
      parts->cellind[i] = -1;
  }
  fclose(dat);

}
