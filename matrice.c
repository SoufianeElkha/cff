#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "file.h"
#include "cellule.h"
#include "lire_file.h"
#include "matrice.h"

void print_file(File F, Liste *my_cities, int tot_indice, int matr[tot_indice][tot_indice])
{
    Cellule cellule;
    printf("\nChemins:\n[");
    if (F == NULL)
        printf("erreur print_file");
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
            tab = realloc(tab, 10 * sizeof(int));
    }
    tab[a + 1] = 0;
    printf("]\n");
    int somma = 0;
    for (int i = 0; i < (longueur(F) - 1); i++)
        somma = matr[tab[i]][tab[i + 1]] + somma;

    printf("\nTemps de parcours est: %d minutes", somma);

    free(tab);
    free(cellule);
}
// Retourn 1 si la ville existe dans le tableau
int existe(int tot_indice, Liste *my_cities, char *ville)
{
    int existe = 0;
    for (int i = 0; i < tot_indice; i++)
        if (strcmp(ville, my_cities[i].ville1) == 0)
            existe = 1;

    return existe;
}

void matrice(char *name, char *ville1, char *ville2, int tot_connections, int tot_indice, Liste *my_cities, Liste *my_connections, int matr[tot_indice][tot_indice])
{

    int *tab1 = (int *)malloc(4000 * sizeof(int *));
    int *tab2 = (int *)malloc(4000 * sizeof(int *));
    int cnt1 = 0;
    int cnt2 = 0;

    // Traduction Ville -> Nombre
    for (int i = 0; i < tot_indice; i++)
    {
        for (int j = 0; j < tot_connections + 1; j++)
        {
            strcpy(ville1, my_connections[j].ville1);
            strcpy(ville2, my_connections[j].ville2);

            for (int c = 0; c < tot_indice; c++)
            {
                if (*tab1 == 4000)
                    tab1 = realloc(tab1, 50);

                if (*tab2 == 4000)
                    tab2 = realloc(tab2, 50);

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
    for (int i = 0; i < tot_connections; i++)
        matr[tab1[i]][tab2[i]] = my_connections[i].dist;

    free(tab1);
    free(tab2);
}

// Convert Nom Ville to Nbr Int de la liste
int convert_ville_to_nbr(char *nome, int tot_indice, Liste *my_cities)
{
    int nb_ville = 0;
    for (int i = 0; i < tot_indice; i++)
        if (strcmp(my_cities[i].ville1, nome) == 0)
            nb_ville = i;

    return nb_ville;
}

void matrice_original(int tot_indice, int matr[tot_indice][tot_indice], int next[tot_indice][tot_indice])
{
    for (int i = 0; i < tot_indice; i++)
        for (int j = 0; j < tot_indice; j++)
        {
            matr[i][i] = 0;
            next[i][j] = j;
            next[i][i] = 0;
            matr[j][i] = matr[i][j];
        }
}

int matrice_next(int tot_indice, int matr[tot_indice][tot_indice], int next[tot_indice][tot_indice])
{
    // Matrice Next
    for (int k = 0; k < tot_indice; ++k)
        for (int i = 0; i < tot_indice; ++i)
            for (int j = 0; j < tot_indice; ++j)
                if (matr[i][j] > matr[i][k] + matr[k][j])
                {
                    matr[i][j] = matr[i][k] + matr[k][j];
                    next[i][j] = next[i][k];
                }
}

// Return Nombre de l'indice de la Ville pris in input
// type --> si 0 alors on return le depart
// type --> si 1 alors on return l'arrive
char *input(char *depart, char *arrive, int tot_indice, Liste *my_cities, int type)
{
    if (type == 0)
    {
        printf("\nDepart: ");
        scanf("%s", depart);

        if (existe(tot_indice, my_cities, depart) != 1)
            printf("Ville non trouvée\n");

        return depart;
    }

    if (type == 1)
    {
        printf("Arrive: ");
        scanf("%s", arrive);
        if (existe(tot_indice, my_cities, arrive) != 1)
            printf("Ville non trouvée\n");

        return arrive;
    }
    return 0;
}

void free_tot(char *__ptr1, char *__ptr2, char *__ptr3, char *__ptr4, char *__ptr5)
{
    free(__ptr1);
    free(__ptr2);
    free(__ptr3);
    free(__ptr4);
    free(__ptr5);

    fflush(stdout);
}
