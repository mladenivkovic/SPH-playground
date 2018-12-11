/*================================================*/
/* Structs and functions for the particle tree    */
/*================================================*/

typedef struct{

  int index;  /* cell index in array              */
  int level;  /* cell level                       */
  int np;     /* number of particles in this cell */
  int npmax;  /* number of maximal particles that can be stored before reallocation */
  int nptot;  /* number of particles in child cells in total */
  int *parts; /* array of particles in this cell  */

} cell;



extern void init_tree();

extern void get_cell_center();
extern void get_cell_index();
