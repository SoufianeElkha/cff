#ifndef _LISTE_H_
#define _LISTE_H_

#include "cellule.h"
#include "lire_file.h"

struct _file
{
   int longueur;
   Cellule tete;
   Cellule queue;
};

typedef struct _file *File;

#define fileEstVide(F) ((F)->longueur == 0)

File fileVide();
int longueur(File F);
void enfiler(File F, typage element);
typage tete(File F);
void defiler(File F);
typage defilement(File F);
void ecrireFile(File F, Liste *my_cities, int tot_indice, int matr[tot_indice][tot_indice]);
int exixte(int tot_indice, Liste *my_cities, char *ville);
void matrice(char *name, char *ville1, char *ville2, int valore, int tot_indice, Liste *my_cities, Liste *my_connections, int matr[tot_indice][tot_indice]);

#endif