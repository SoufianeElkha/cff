#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "file.h"
#include "cellule.h"
#include "lire_file.h"

File file_vide()
{
   File F;
   F = (File)malloc(sizeof(struct _file));
   if (F == NULL)
      printf("erreur allocation file_vide");
   F->longueur = 0;
   F->tete = F->queue = NULL;
   return (F);
}

int longueur(File F)
{
   if (F == NULL)
      printf("file existe pas - longueur");
   return (F->longueur);
}

void enfiler(File F, typage element)
{
   Cellule cellule;
   if (F == NULL)
      printf("file existe pas - enfiler");

   cellule = (Cellule)malloc(1 * sizeof(struct _cellule));
   if (cellule == NULL)
      printf("erreur allocation memoire - enfiler");
   cellule->element = element;
   cellule->suivant = NULL;
   if (longueur(F) == 0)
   {
      F->tete = F->queue = cellule;
   }
   else
   {
      F->queue->suivant = cellule;
      F->queue = cellule;
   }
   ++(F->longueur);
}

typage tete(File F)
{
   if (F == NULL || longueur(F) == 0)
      printf(" File existe pas - tete");
   return (F->tete->element);
}

void defiler(File F)
{
   Cellule cellule;

   if (F == NULL || longueur(F) == 0)
      printf("File existe pas - defiler");
   while (longueur(F) != 0)
   {

      cellule = F->tete;
      if (longueur(F) == 1)
         F->tete = F->queue = NULL;
      else
         F->tete = F->tete->suivant;
      --(F->longueur);
   }
   free(cellule);
   free(F);
}
