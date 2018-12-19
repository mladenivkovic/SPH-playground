/*========================================*/
/* Particle related structs and functions */
/*========================================*/


typedef struct {
  double* x;        /* x position                       */
  double* y;        /* y position                       */
  double* z;        /* z position                       */
  double* vx;       /* x velocity                       */
  double* vy;       /* y velocity                       */
  double* vz;       /* z velocity                       */
  double* m;        /* mass                             */
  double* h;        /* smoothing length                 */
  double* P;        /* pressure                         */
  double* rho;      /* density                          */
  int*    cellind;  /* cell index where particle is in  */
} part;
