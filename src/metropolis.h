#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float J, float B, double *mc_list, double *p_ener, int *p_magnet);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, int idx, float T, float J, float B, double *mc_list, double *p_ener, int *p_magnet);
int sgn(int x);
int get_neighbours(int *neigh, int n_neigh, int *lattice, int n, int idx);
int get_neighbours_diag(int *neigh, int n_neigh, int *lattice, int n, int idx);
int print_data(int *lattice, int n, int *neigh, int n_neigh, int idx);
int mc_table(double *mc_list, float T, float J, float B);
double energy_lattice(int *lattice, int n, float J, float B);
double energy_lattice_diag(int *lattice, int n, float J, float B);
int magnet_lattice(int *lattice, int n);
double autocorr(double *arr, int len_arr, int tau);
double mean(double *array,int arraysize);
double disp(double *array,int arraysize);
#endif
