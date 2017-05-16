#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, int idx, float T);
int sgn(int x);
int get_neighbours(int *neigh, int n_neigh, int *lattice, int n, int idx);
int print_data(int *lattice, int n, int *neigh, int n_neigh, int idx);
int mc_table(double *mc_list, int list_lenght, float T);
#endif
