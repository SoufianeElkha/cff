#ifndef _LIRE_FILE_H
#define _LIRE_FILE_H

struct _liste
{

  char ville1[30];
  char ville2[30];
  int dist;
  int indice;
};
typedef struct _liste Liste;

int lire_file(Liste *my_liste, char *name_file, int records, int type_file);
int convert_ville_to_nbr(char *nome, int tot_indice, Liste *my_cities);
void matrice_original(int tot_indice, int matr[tot_indice][tot_indice], int next[tot_indice][tot_indice]);
void matrice_next(int tot_indice, int matr[tot_indice][tot_indice], int next[tot_indice][tot_indice]);

#endif