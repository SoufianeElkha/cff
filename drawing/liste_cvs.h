#ifndef _LISTA_CVS_H
#define _LISTA_CVS_H

typedef struct _liste
{

  char ville1[50];
  char ville2[50];
  int dist;
  int indice;
} Liste;

int lire_file(Liste *my_liste, char *name_file, int records, int type_file);

#endif