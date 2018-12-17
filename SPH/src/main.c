/* ======================================== 
 *  
 * A rudimentary SPH code.
 *
 * Usage: ./sph paramfile.txt datafile.dat
 *  
 * ======================================== */



#include <stdlib.h>
#include <stdio.h>

#include "cells.h"
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
  cell *mesh;

  init_params(&p);
  read_cmdlineargs(argc, argv, &p);
  read_paramfile(&p);
  read_datafile(&p, &part);
  check_params(&p);
  print_params(&p);
  init_cells(&p, &mesh);


  double x, y, z;
  int compind;
  for (int i = 0; i<p.nx*p.nx*p.nx; i++){
    get_cell_center(&p, &mesh[i], &x, &y, &z);
    get_cell_index(&p, x, y, z, &compind);
    printf("%d %d %lf %lf %lf %lf\n", i, compind, x, y, z, x*x + y*y + z*z);
    /* printf("%d %d %d %d %lf %lf %lf %lf\n", c->ind, i, j, k, x, y, z, x*x + y*y + z*z); */
  }

  return(0);

}




