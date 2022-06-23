#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "liste.h"
#include "cellule.h"
#include "lire_file.h"

File fileVide()
{
   File F;
   F = (File)malloc(sizeof(struct _file));
   if (F == NULL)
      printf("erreur allocation fileVide");
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

// typage tete(File F)
// {
//    if (F == NULL || longueur(F) == 0)
//       printf(" File existe pas - tete");
//    return (F->tete->element);
// }

void defiler(File F)
{
   Cellule cellule;

   if (F == NULL || longueur(F) == 0)
      printf("File existe pas - defiler");
   cellule = F->tete;
   if (longueur(F) == 1)
      F->tete = F->queue = NULL;
   else
      F->tete = F->tete->suivant;
   --(F->longueur);
   free(cellule);
}

// typage defilement(File F)
// {
//    Cellule cellule;
//    typage element;
//    if (F == NULL || longueur(F) == 0)
//       printf("File existe pas - defilement");
//    cellule = F->tete;
//    element = cellule->element;
//    if (longueur(F) == 1)
//    {
//       F->tete = F->queue = NULL;
//    }
//    else
//    {
//       F->tete = F->tete->suivant;
//    }

//    --(F->longueur);
//    return (element);
// }

void ecrireFile(File F, Liste *my_cities, int tot_indice, int matr[tot_indice][tot_indice])
{
   Cellule cellule;
   printf("\nChemins:\n[");
   if (F == NULL)
      printf("erreur ecrireFile");
   cellule = F->tete;
   int *tab = malloc(tot_indice * sizeof(int *));
   int a = 0;
   while (cellule != NULL)
   {
      tab[a] = cellule->element;
      printf("%s  ", my_cities[cellule->element].ville1);
      cellule = cellule->suivant;
      a++;
      if (a > tot_indice)
      {
         tab = realloc(tab, 10 * sizeof(int));
      }
   }
   tab[a + 1] = 0;
   printf("]\n");
   int somma = 0;
   for (int i = 0; i < (longueur(F) - 1); i++)
   {
      somma = matr[tab[i]][tab[i + 1]] + somma;
   }
   printf("\nTemps de parcours est: %d minutes", somma);

   free(tab);
   free(cellule);
}

int exixte(int tot_indice, Liste *my_cities, char *ville)
{
   int control = 0;
   for (int i = 0; i < tot_indice; i++)
   {
      if (strcmp(ville, my_cities[i].ville1) == 0)
      {
         control = 1;
      }
   }
   return control;
}

void matrice(char *name, char *ville1, char *ville2, int valore, int tot_indice, Liste *my_cities, Liste *my_connections, int matr[tot_indice][tot_indice])
{

   int tab1[4000];
   int tab2[4000];
   int cnt1 = 0;
   int cnt2 = 0;

   // Traduction Ville -> Nombre
   for (int i = 0; i < tot_indice; i++)
   {
      for (int j = 0; j < valore + 1; j++)
      {
         strcpy(ville1, my_connections[j].ville1);
         strcpy(ville2, my_connections[j].ville2);

         for (int c = 0; c < tot_indice; c++)
         {
            strcpy(name, my_cities[c].ville1);

            if (strcmp(name, ville1) == 0)
            {
               tab1[cnt1] = c;
               cnt1++;
            }

            if (strcmp(name, ville2) == 0)
            {
               tab2[cnt2] = c;
               cnt2++;
            }
         }
      }
   }

   for (int i = 0; i < tot_indice; i++)
      for (int j = 0; j < tot_indice; j++)
         matr[i][j] = 10000;

   // Update matrice
   for (int i = 0; i < valore; i++)
      matr[tab1[i]][tab2[i]] = my_connections[i].dist;
}
