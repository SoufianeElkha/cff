#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "lire_file.h"
#include "liste.h"
#include "cellule.h"

//INVIO numero 2

int main()
{

    Liste my_cities[100];
    Liste my_connections[100];
    int records = 0;
    int tab[4000];
    int tab2[4000];
    int a = 0;
    int b = 0;

    char *name;
    char *ville1;
    char *ville2;

    int tot_indice = lire_file(my_cities, "data/cities.csv", records, 0);
    int valore = lire_file(my_connections, "data/connections.csv", records, 0);

    name = (char *)malloc((strlen(my_cities[0].ville1) + 10) * sizeof(char));
    ville1 = (char *)malloc((strlen(my_connections[0].ville1) + 10) * sizeof(char));
    ville2 = (char *)malloc((strlen(my_connections[0].ville2) + 10) * sizeof(char));

    int matr[tot_indice][tot_indice];
    int next[tot_indice][tot_indice];

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

                if (strcmp(name, ville2) == 0)
                {
                    tab2[b] = c;
                    b++;
                }

                if (strcmp(name, ville1) == 0)
                {
                    tab[a] = c;
                    a++;
                }
            }
        }
    }

    for (int i = 0; i < tot_indice; i++)
        for (int j = 0; j < tot_indice; j++)
            matr[i][j] = 10000;

    // Update matrice
    for (int i = 0; i < valore; i++)
        matr[tab[i]][tab2[i]] = my_connections[i].dist;

    matrice_original(tot_indice, matr, next);
    matrice_next(tot_indice, matr, next);


    char depart[30];
    char arrive[30];
    printf("\nDepart: ");
    scanf("%s", depart);

    if (exixte(tot_indice, my_cities, depart) != 1){printf("Ville non trovata\n");}

    printf("Arrive: ");
    scanf("%s", arrive);
    if (exixte(tot_indice, my_cities, arrive) != 1){printf("Ville non trovata\n");}

    int dep = convert_ville_to_nbr(depart, tot_indice, my_cities);
    int arr = convert_ville_to_nbr(arrive, tot_indice, my_cities);

    //Cellule cellule
    File path = fileVide();
    enfiler(path, dep);
    while (dep != arr)

    {
        dep = next[dep][arr];
        enfiler(path, dep);
    }
    printf("\n");
    
    ecrireFile(path,my_cities,tot_indice,matr);

    defiler(path);










    // int N = valore;
    // printf("\n\n/**************************************************/\n\n");
    // pSommet *graphe = NULL;
    // graphe = CreerGraphe(N);
    // for (int i = 0; i < valore; i++)
    // {
    //     graphe = CreerArete(graphe, tab[i], tab2[i], my_connections[i].dist);
    // }

    // affiche(graphe, valore);
    // // InitialParcourLongueur(graphe, N);
    // printf("\n");
    // // InitialParcourLargeur(graphe, N);

    // free(graphe);
    free(ville1);
    free(ville2);
    free(name);
    free(path);
    printf("\n");

    fflush(stdout);
    return 0;
}
