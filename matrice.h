#ifndef _MATRICE_H
#define _MATRICE_H

#include "cellule.h"
#include "lire_file.h"

void print_file(File F, Liste *my_cities, int tot_indice, int matr[tot_indice][tot_indice]);
int existe(int tot_indice, Liste *my_cities, char *ville);
void matrice(char *name, char *ville1, char *ville2, int tot_connections, int tot_indice, Liste *my_cities, Liste *my_connections, int matr[tot_indice][tot_indice]);
int convert_ville_to_nbr(char *nome, int tot_indice, Liste *my_cities);
void matrice_original(int tot_indice, int matr[tot_indice][tot_indice], int next[tot_indice][tot_indice]);
void matrice_next(int tot_indice, int matr[tot_indice][tot_indice], int next[tot_indice][tot_indice]);
char *input(char *depart, char *arrive, int tot_indice, Liste *my_cities, int type);
void free_tot(char *__ptr1, char *__ptr2, char *__ptr3, char *__ptr4, char *__ptr5);

#endif