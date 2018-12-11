/* ======================================== 
 *  
 * A rudimentary SPH code.
 *
 * Usage: ./sph paramfile.txt datafile.dat
 *  
 * ======================================== */



#include <stdlib.h>
#include <stdio.h>

#include "io.h"
#include "params.h"
#include "part.h"

#ifndef NDIM
#define NDIM 3
#pragma message("You didn't define the number of dimensions in the Makefile. Compiling with NDIM=3\n")
#endif




int main(int argc, char* argv[]){

  params p;
  parts part;
  init_params(&p);
  read_cmdlineargs(argc, argv, &p);
  read_paramfile(&p);
  read_datafile(&p, &part);
  check_params(&p);
  print_params(&p);

  return(0);

}




