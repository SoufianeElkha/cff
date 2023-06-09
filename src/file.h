#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "cellule.h"
#include "lire_file.h"

#define fileEstVide(F) ((F)->longueur == 0)
struct _file
{
   int longueur;
   Cellule tete;
   Cellule queue;
};

typedef struct _file *File;

File file_vide();
int longueur(File F);
void enfiler(File F, typage element);
void defiler(File F);
typage tete(File F);
typage defilement(File F);
void delete(File F);

#endif