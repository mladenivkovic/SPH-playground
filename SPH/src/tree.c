/*================================================*/
/* Structs and functions for the particle tree    */
/*================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "params.h"
#include "tree.h"

void init_tree(cell *tree, params *params){

  if (params->verbose) printf("Initializing tree\n");

  /* Allocate tree, initialize cells */

  int ncelltot = 0;
  for (int l=0; l<=params->levelmax; l++){
    ncelltot += pow(2, l*NDIM);
  }

  params->ncelltot = ncelltot;

  printf("ncelltot: %d\n", ncelltot);

  tree = malloc(ncelltot*sizeof(cell));

  int ind=0;
  for (int l=0; l<=params->levelmax; l++){
    int jmax = pow(2,l*NDIM);
    for (int j=0; j<jmax; j++){
      tree[ind].index = ind;
      tree[ind].level = l;
      tree[ind].np = 0;
      tree[ind].npmax = 0;
      tree[ind].nptot = 0;
      ind += 1;
    }
  }

  /* for (int j=0; j<ncelltot; j++){ */
  /*   printf("%d %d %d %d %d %d\n", j, tree[j].index, tree[j].level, tree[j].np, tree[j].npmax, tree[j].nptot); */
  /* } */


  /* Initialize root */
  if (params->verbose) printf("Initializing root\n");

  tree[0].np = params->npart;
  tree[0].parts = malloc(params->npart*sizeof(int));
  for (int i=0; i<params->npart; i++){
    tree[0].parts[i] = i;
  }

}


void get_cell_center(double *x, double *y, double *z, int ind){

}

void get_cell_index(double x, double y, double z, int* ind){
}
