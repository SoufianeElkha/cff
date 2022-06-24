#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "lire_file.h"
#include "file.h"
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
  // lecture 2 string et 1 int
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

  // Lecture 2 int
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
  // Lecture 1string et 2 int
  if (type_file == 2)
  {
    do
    {
      fscanf(file,
             "%30[^,] , %d,  %d \n",
             my_liste[records].ville1,
             &my_liste[records].dist,
             &my_liste[records].indice);
      records++;
    } while (!feof(file));
  }
  fclose(file);
  return records;
}

int lire_file_perimetre(char *name_file, int *x, int *y)
{

  char *import_database;
  char table[TMP_MAX];
  char *x_char;
  char *y_char;
  int i = 0;
  FILE *fid;
  fid = fopen(name_file, "r");
  if (fid)
  {
    while (1)
    {
      import_database = fgets(table, 999, fid);
      if (import_database == NULL)
        break;
      x_char = strtok(table, " ");
      y_char = strtok(NULL, "\n");
      x[i] = atoi(x_char);
      y[i] = atoi(y_char);
      i++;
    }
  }
  else
    printf("\nErreur d’ouverture de fichier\n");

  fclose(fid);
  fflush(stdin);
  return i;
}
