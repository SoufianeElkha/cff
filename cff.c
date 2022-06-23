#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "lire_file.h"
#include "liste.h"
#include "cellule.h"

// INVIO numero 4

int main()
{
    Liste my_cities[1000];
    Liste my_connections[1000];
    File path = fileVide();

    int records = 0;
    int dep = 0;
    int arr = 0;

    int tot_indice = lire_file(my_cities, "data/cities.csv", records, 0);
    int valore = lire_file(my_connections, "data/connections.csv", records, 0);

    char *name = (char *)malloc((strlen(my_cities[0].ville1) + 10) * sizeof(char));
    char *ville1 = (char *)malloc((strlen(my_connections[0].ville1) + 10) * sizeof(char));
    char *ville2 = (char *)malloc((strlen(my_connections[0].ville2) + 10) * sizeof(char));
    char *depart = (char *)malloc(30 * sizeof(char *));
    char *arrive = (char *)malloc(30 * sizeof(char *));
    int matr[tot_indice][tot_indice];
    int next[tot_indice][tot_indice];

    // Traduction Ville -> Nombre && Creation Matrice
    matrice(name, ville1, ville2, valore, tot_indice, my_cities, my_connections, matr);
    // Creation de la matrice
    matrice_original(tot_indice, matr, next);
    // Creation de la matrice next
    matrice_next(tot_indice, matr, next);

    dep = convert_ville_to_nbr(input(depart,arrive,tot_indice, my_cities, 0), tot_indice, my_cities);
    arr = convert_ville_to_nbr(input(arrive,arrive,tot_indice, my_cities, 1), tot_indice, my_cities);

    // First City
    enfiler(path, dep);
    while (dep != arr)
    {
        dep = next[dep][arr];
        enfiler(path, dep);
    }

    ecrireFile(path, my_cities, tot_indice, matr);
    defiler(path);
    free(ville1);
    free(ville2);
    free(depart);
    free(arrive);
    free(name);
    free(path);
    fflush(stdout);
    return 0;
}
