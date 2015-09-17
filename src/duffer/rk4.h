#ifndef RK4_H
#define RK4_H

double rk4 ( double t0, double u0, double dt, double f ( double t, double u ) );
double *rk4vec ( double t0, int n, double u0[], double dt,
                 double *f ( double t, int n, double u[] ) );
double *rk4vecRT ( double t0, int n, double u0[], double dt,
                   double *f ( double t, int n, double u[], void* data, double buf[] ) , void* data, double buf[]);
void timestamp ( void );

#endif
