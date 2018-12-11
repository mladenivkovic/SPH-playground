/* All around parameters used in the simulation. */

/* GLOBAL PARAMETERS */
typedef struct {

  int nstepmax;
  int step;
  double tmax;
  double t;
  double dt_max;
  
  double boxlen;
  int npart;
  int levelmax;
  int ncelltot;

  double unit_m;
  double unit_l;
  double unit_t;
  
  int verbose;
  int debug;
  char paramfilename[200];
  char datafilename[200];
} params;



extern void check_params();
extern void init_params();
extern void print_params();

