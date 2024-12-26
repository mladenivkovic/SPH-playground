/*================================================*/
/* Structs and functions for the particle tree    */
/*================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "cells.h"
#include "params.h"
#include "part.h"

#define npmax_init 100



/*===================================================*/
/* Double the size of the particle array of a cell   */
/*===================================================*/

void cell_realloc_partarr(cell* c){
  int* temparr = c->parts;
  c->parts = malloc(c->npmax*2*sizeof(int));
  for (int j=0; j<c->npmax; j++){
    c->parts[j] = temparr[j];
  }
  c->npmax *= 2;
  free(temparr);
}












/*=============================================*/
/* Allocate and initialize all cells.          */
/*=============================================*/
void init_cells(params *p, cell** mesh, part * parts){

  if (p->debug) printf("Allocating and initializing cells\n");

  *mesh = malloc(pow(p->nx, 3)*sizeof(cell));

  int ind = 0;
  for(int i=0; i<p->nx; i++){
    for(int j=0; j<p->nx; j++){
      for(int k=0; k<p->nx; k++){
        (*mesh)[ind].ind = ind;
        (*mesh)[ind].np = 0;
        (*mesh)[ind].npmax = npmax_init;
        (*mesh)[ind].parts = malloc(npmax_init*sizeof(int));
        ind += 1;
      }
    }
  }


  if (p->debug) printf("Dividing particles into cells.\n");

  for (int i=0; i<p->npart; i++){
    int cind = get_cell_index(p, parts->x[i], parts->y[i], parts->z[i]);
    cell * c = &(*mesh)[cind];
    if (c->np == c->npmax){
      cell_realloc_partarr(c);
    }
    c->parts[c->np] = i;
    c->np += 1;
    parts->cellind[i] = cind;
  }
}





/*=======================================================*/
/*Computes the cell center coordinates of given cell c.  */
/*=======================================================*/
void get_cell_center(params *p, cell* c, double *x, double *y, double *z){

  int nx2 = p->nx*p->nx;
  int k = c->ind/nx2;
  int knx2 = k*nx2;
  int j = (c->ind - knx2)/p->nx;
  int i = c->ind - knx2 - j*p->nx;

  *x = (i+0.5)*p->dx;
  *y = (j+0.5)*p->dx;
  *z = (k+0.5)*p->dx;
}






/*=======================================================*/
/* Computes the index of the cell any point x,y,z is in. */
/*=======================================================*/
int get_cell_index(params *p, double x, double y, double z){

  int i = (int) floor(x/p->dx);
  int j = (int) floor(y/p->dx);
  int k = (int) floor(z/p->dx);

  return(i + j*p->nx + k*p->nx*p->nx);

}
