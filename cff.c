#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "lire_file.h"
#include "file.h"
#include "cellule.h"
#include "matrice.h"

// INVIO numero 4

int main()
{
    // Declaration dela liste
    File path = file_vide();
    int records = 0;

    int tot_indice = lire_file(my_cities, "data/cities.csv", records, 0);
    int tot_connections = lire_file(my_connections, "data/connections.csv", records, 0);

    char *name = (char *)malloc((strlen(my_cities[0].ville1) + 10) * sizeof(char));
    char *ville1 = (char *)malloc((strlen(my_connections[0].ville1) + 10) * sizeof(char));
    char *ville2 = (char *)malloc((strlen(my_connections[0].ville2) + 10) * sizeof(char));
    char *depart = (char *)malloc(30 * sizeof(char *));
    char *arrive = (char *)malloc(30 * sizeof(char *));
    int matr[tot_indice][tot_indice];
    int next[tot_indice][tot_indice];

    // Traduction Ville -> Nombre && Creation Matrice
    matrice(name, ville1, ville2, tot_connections, tot_indice, my_cities, my_connections, matr);
    // Creation de la matrice dist
    matrice_original(tot_indice, matr, next);
    // Creation de la matrice next
    matrice_next(tot_indice, matr, next);
    // Convertion de Ville en entree vers de nombre
    int dep = convert_ville_to_nbr(input(depart, arrive, tot_indice, my_cities, 0), tot_indice, my_cities);
    int arr = convert_ville_to_nbr(input(arrive, arrive, tot_indice, my_cities, 1), tot_indice, my_cities);
    // enfiler 1er Ville
    enfiler(path, dep);
    while (dep != arr)
    {
        dep = next[dep][arr];
        enfiler(path, dep);
    }
    // Print la liste complet de chemis parcouire
    print_file(path, my_cities, tot_indice, matr);
    // defiler(path);

    // Liberation de la memoire occupe
    free_tot(ville1, ville2, name, depart, arrive);
    free(path);
    fflush(stdout);

    return 0;
}
