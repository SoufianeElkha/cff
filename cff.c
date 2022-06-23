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

    int records = 0;
    char depart[30];
    char arrive[30];

    int tot_indice = lire_file(my_cities, "data/cities.csv", records, 0);
    int valore = lire_file(my_connections, "data/connections.csv", records, 0);

    char *name = (char *)malloc((strlen(my_cities[0].ville1) + 10) * sizeof(char));
    char *ville1 = (char *)malloc((strlen(my_connections[0].ville1) + 10) * sizeof(char));
    char *ville2 = (char *)malloc((strlen(my_connections[0].ville2) + 10) * sizeof(char));

    int matr[tot_indice][tot_indice];
    int next[tot_indice][tot_indice];

    // Traduction Ville -> Nombre && Creation Matrice
    matrice(name, ville1, ville2, valore, tot_indice, my_cities, my_connections, matr);

    matrice_original(tot_indice, matr, next);
    matrice_next(tot_indice, matr, next);

    printf("\nDepart: ");
    scanf("%s", depart);

    if (exixte(tot_indice, my_cities, depart) != 1)
        printf("Ville non trouvée\n");

    printf("Arrive: ");
    scanf("%s", arrive);
    if (exixte(tot_indice, my_cities, arrive) != 1)
        printf("Ville non trouvée\n");

    int dep = convert_ville_to_nbr(depart, tot_indice, my_cities);
    int arr = convert_ville_to_nbr(arrive, tot_indice, my_cities);

    File path = fileVide();
    // First City
    enfiler(path, dep);
    while (dep != arr)
    {
        dep = next[dep][arr];
        enfiler(path, dep);
    }
    printf("\n");

    ecrireFile(path, my_cities, tot_indice, matr);
    defiler(path);

    free(ville1);
    free(ville2);
    free(name);
    free(path);

    printf("\n");

    fflush(stdout);
    return 0;
}
