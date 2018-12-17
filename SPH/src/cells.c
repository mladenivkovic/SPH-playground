/*================================================*/
/* Structs and functions for the particle tree    */
/*================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "cells.h"
#include "params.h"

#define nptot_init 100



/*=============================================*/
/* Allocate and initialize all cells.          */
/*=============================================*/

void init_cells(params *p, cell** mesh){

  if (p->debug) printf("Allocating and initializing cells\n");

  *mesh = malloc(pow(p->nx, 3)*sizeof(cell));

  int ind = 0;
  for(int i=0; i<p->nx; i++){
    for(int j=0; j<p->nx; j++){
      for(int k=0; k<p->nx; k++){
        (*mesh)[ind].ind = ind;
        (*mesh)[ind].np = 0;
        (*mesh)[ind].nptot = nptot_init;
        (*mesh)[ind].parts = malloc(nptot_init*sizeof(int));
        ind += 1;
      }
    }
  }
}






/*Computes the cell center coordinates of given cell c. */
void get_cell_center(params *p, cell* c, double *x, double *y, double *z){

  int nx2 = p->nx*p->nx;
  int k = c->ind/nx2;
  int knx2 = k*nx2;
  int j = (c->ind - knx2)/p->nx;
  int i = c->ind - knx2 - j*p->nx;

  /* printf("inside: %d %d %d %d %lf \n", i, j, k, p->nx, p->dx); */

  *x = (i+0.5)*p->dx;
  *y = (j+0.5)*p->dx;
  *z = (k+0.5)*p->dx;
}


/* Computes the index of the cell any point x,y,z is in. */
void get_cell_index(params *p, double x, double y, double z, int* ind){

  int i = (int) floor(x/p->dx);
  int j = (int) floor(y/p->dx);
  int k = (int) floor(z/p->dx);

  *ind = i + j*p->nx + k*p->nx*p->nx;

}
