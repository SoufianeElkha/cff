#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "lire_file.h"
#include "liste.h"
#include "cellule.h"

int lire_file(Liste *my_liste, char *name_file, int records, int type_file)
{

  FILE *file;
  file = fopen(name_file, "r");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 0;
  }

  if (type_file == 0)
  {
    do
    {
      fscanf(file,
             "%30[^,] , %30[^,],  %d \n",
             my_liste[records].ville1,
             my_liste[records].ville2,
             &my_liste[records].dist);

      records++;
      my_liste[records].indice = records;
    } while (!feof(file));
  }

  if (type_file == 1)
  {
    do
    {
      fscanf(file,
             "%d, %d\n",
             &my_liste[records].dist,
             &my_liste[records].indice);

      records++;
    } while (!feof(file));
  }

  if (type_file == 2)
  {
    do
    {
      fscanf(file,
             "%30[^,] , %d,  %d \n",
             my_liste[records].ville1,
             &my_liste[records].dist,
             &my_liste[records].indice);

    } while (!feof(file));
  }
  fclose(file);
  return records;
}

int convert_ville_to_nbr(char *nome, int tot_indice, Liste *my_cities)
{
  int nb_ville = 0;
  // Convert Nom Ville to Nbr Int de la liste
  for (int i = 0; i < tot_indice; i++)
  {
    if (strcmp(my_cities[i].ville1, nome) == 0)
    {
      nb_ville = i;
    }
  }
  return nb_ville;
}

void matrice_original(int tot_indice, int matr[tot_indice][tot_indice], int next[tot_indice][tot_indice])
{

  for (int i = 0; i < tot_indice; i++)
  {
    for (int j = 0; j < tot_indice; j++)
    {
      matr[i][i] = 0;
      next[i][j] = j;
      next[i][i] = 0;
      matr[j][i] = matr[i][j];
    }
  }
}

void matrice_next(int tot_indice, int matr[tot_indice][tot_indice], int next[tot_indice][tot_indice])
{
  // Matrice Next
  for (int k = 0; k < tot_indice; ++k)
  {
    for (int i = 0; i < tot_indice; ++i)
    {
      for (int j = 0; j < tot_indice; ++j)
      {
        if (matr[i][j] > matr[i][k] + matr[k][j])
        {
          matr[i][j] = matr[i][k] + matr[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }
}

//Return Nombre de l'indice de la Ville pris in input
//type --> si 0 alors on return le depart
//type --> si 1 alors on return l'arrive
char *input(char *depart, char *arrive, int tot_indice, Liste *my_cities, int type)
{

  if (type == 0)
  {
    printf("\nDepart: ");
    scanf("%s", depart);

    if (exixte(tot_indice, my_cities, depart) != 1)
      printf("Ville non trouvée\n");

    return depart;
  }

  if (type == 1)
  {
    printf("Arrive: ");
    scanf("%s", arrive);
    if (exixte(tot_indice, my_cities, arrive) != 1)
      printf("Ville non trouvée\n");

    return arrive;
  }
  return 0;
}
