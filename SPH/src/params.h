/* All around parameters used in the simulation. */

/* GLOBAL PARAMETERS */
typedef struct {

  int     nstepmax;            /* max number of steps code should do */
  int     step;                /* current step number                */
  double  tmax;                /* max time for code to run           */
  double  t;                   /* current time                       */
  double  dt_max;              /* max next timestep interval         */
  
  double  boxlen;              /* total boxlen                       */
  int     npart;               /* number of particles                */
  int     nx;                  /* number of cells                    */
  double  dx;                  /* cell edge size                     */
  int     nneigh;              /* number of neighbours               */

  double  unit_m;              /* mass unit                          */
  double  unit_l;              /* length unit                        */
  double  unit_t;              /* time unit                          */
  
  int     verbose;             /* am I talking?                      */
  int     debug;               /* am I talking a lot for debugging?  */
  char    paramfilename[200];  /* parameter file name                */
  char    datafilename[200];   /* data file name                     */
} params;



extern void check_params();
extern void init_params();
extern void print_params();

