#include "params.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

  char varname[80] ;
  char varvalue[80] ;
  char tempbuff[80] ;

  
  while (fgets(tempbuff,80,par))
  // fgets(str_buff, n,filepointer) :
  // gets n characters from file in filepointer and stores them
  // in str_buff.
  // returns 0 if EoF is reached.
  
  {
    sscanf(tempbuff, "%20s = %56[^\n]\n", varname, varvalue);
    // reads formatted input from a string, writes it in
    // the variables given after the format string.
    // The format used is <string> separator <=> <string> ends with <;>
  

    if (strcmp(varname,"verbose") == 0) {
      p->verbose = atoi(varvalue);
    // atoi/atof: convert string to integer/float
    // from stdlib.h
    } 
    else if (strcmp(varname, "levelmax") == 0){
      p->levelmax = atoi(varvalue);
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
    else{
      printf("Unrecongized parameter : \"%s\"\n", varname);
    }
  }

    fclose(par);

}








/* ====================================================================== */
/* Read in initial condition file                                         */
/* ====================================================================== */
void read_datafile(params* p){

  //open file
  FILE *dat = fopen(p->datafilename, "r");

  // check if file exists
  if (dat == NULL) { 
    printf("Error: file '%s' not found.\n", p->datafilename);
    exit(604);
  }

  char xs[12], ys[12], zs[12], vxs[12], vys[12], vzs[12], ms[12];
  char tempbuff[90];

  
  fgets(tempbuff,15,dat);
  sscanf(tempbuff, "%12lg \n", p->boxlen);
  fgets(tempbuff,15,dat);
  sscanf(tempbuff, "%12d \n", p->npart);

  


  for (int i=0; i<p->npart; i++)
  {
    fgets(tempbuff,15,dat);
    sscanf(tempbuff, "%12g %12g %12g %12g %12g %12g %12g\n", xs, ys, zs, vxs, vys, vzs, ms);
  }
  fclose(dat);

}
