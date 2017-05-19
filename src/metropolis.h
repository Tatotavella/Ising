#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float B, double *mc_list, double *p_ener, int *p_magnet);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, int idx, float T, float B, double *mc_list, double *p_ener, int *p_magnet);
int sgn(int x);
int get_neighbours(int *neigh, int n_neigh, int *lattice, int n, int idx);
int print_data(int *lattice, int n, int *neigh, int n_neigh, int idx);
int mc_table(double *mc_list, int list_length, float T, float B);
double energy_lattice(int *lattice, int n, float B);
int magnet_lattice(int *lattice, int n);
#endif
