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
Liste my_cities[1000];
Liste my_connections[1000];

int lire_file(Liste *my_liste, char *name_file, int records, int type_file);

#endif