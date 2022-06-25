/*
    Soufiane El kharmoudi
    tp17 -> Recherce du plus court chemin dans un réseau ferré
    24/06/2022

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "lire_file.h"
#include "file.h"
#include "cellule.h"
#include "matrice.h"
#include "drawing.h"
#include "gfx.h"

int main()
{
    printf("\nRecherce du plus court chemin dans un réseau ferré\n");
    printf("====================================================\n\n");
    // Declaration liste
    File path = file_vide();
    File path_next = file_vide();
    int records = 0;

    int tot_indice = lire_file(my_cities, "data/cities.csv", records, 0);
    int tot_connections = lire_file(my_connections, "data/connections.csv", records, 0);

    char *name = (char *)malloc((strlen(my_cities[0].ville1) + 10) * sizeof(char));
    char *ville1 = (char *)malloc((strlen(my_connections[0].ville1) + 10) * sizeof(char));
    char *ville2 = (char *)malloc((strlen(my_connections[0].ville2) + 10) * sizeof(char));
    int matr[tot_indice][tot_indice];
    int next[tot_indice][tot_indice];

    char *buffer = (char *)malloc(400 * sizeof(char *));
    const int width = 1300, height = 800;

    // Traduction Ville -> Nombre && Creation Matrice
    matrice(name, ville1, ville2, tot_connections, tot_indice, my_cities, my_connections, matr);
    // Creation de la matrice dist
    matrice_original(tot_indice, matr, next);
    // Creation de la matrice next
    matrice_next(path_next, tot_indice, matr, next);

    while (strcmp(buffer, "quitter") != 0)
    {
        printf(">Entrez une ville de départ: ");
        scanf("%99s", buffer);
        exit_prog(buffer);

        // Convertion de Ville en entree vers de nombre
        int dep = convert_ville_to_nbr(input(buffer, tot_indice, my_cities, 0), tot_indice, my_cities);
        printf(">Entrez une ville d'arrivée: ");
        scanf("%99s", buffer);
        exit_prog(buffer);
        int arr = convert_ville_to_nbr(input(buffer, tot_indice, my_cities, 1), tot_indice, my_cities);

        // enfiler 1er Ville
        enfiler(path, dep);
        while (dep != arr)
        {
            dep = next[dep][arr];
            enfiler(path, dep);
        }

        exit_prog(buffer);

        // Print la liste complet de chemis parcouire
        print_file(path, my_cities, tot_indice, matr);

        printf("\n>Imprimer le trajet ? y/n:");
        scanf("%99s", buffer);
        exit_prog(buffer);
        if (buffer[0] == 'y')
        {
            struct gfx_context_t *ctxt = gfx_create("CFF", width, height);
            if (!ctxt)
            {
                fprintf(stderr, ">Graphics initialization failed!\n");
                return EXIT_FAILURE;
            }
            render(ctxt, path);
            gfx_present(ctxt);
            defiler(path_next);
        }
        defiler(path);
    }
    // Liberation de la memoire occupe
    free_tot(ville1, ville2, name, buffer, path, path_next);

    exit(0);
}
