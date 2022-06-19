#include <stdio.h>
#include <stdlib.h>
#include "graphe_liste.h"

int N = 10;

int main()
{

    system("clear");
    printf("\n/**************************************************/\n\n");
    pSommet *graphe = NULL;
    graphe = CreerGraphe(N);
    graphe = CreerArete(graphe, 0, 1, 50);
    graphe = CreerArete(graphe, 1, 4, 60);
    graphe = CreerArete(graphe, 1, 3, 10);
    graphe = CreerArete(graphe, 1, 9, 5);
    graphe = CreerArete(graphe, 1, 8, 10);
    graphe = CreerArete(graphe, 3, 2, 4);
    graphe = CreerArete(graphe, 2, 7, 10);
    graphe = CreerArete(graphe, 7, 4, 10);

    affiche(graphe, N);
    // InitialParcourLongueur(graphe,N);
    printf("\n");
    InitialParcourLargeur(graphe, N);
    system("PAUSE");
    free(graphe);
    return 0;
}
