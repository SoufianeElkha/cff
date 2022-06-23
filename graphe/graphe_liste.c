#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "graphe_liste.h"
#include "fifo.h"
#include "cellule.h"

pSommet *CreerGraphe(int taille)
{
  pSommet *Newgraphe = (pSommet *)malloc(taille * sizeof(pSommet));
  int i;
  for (i = 0; i < taille; i++)
  {
    Newgraphe[i] = (pSommet)malloc(sizeof(struct Sommet));
    Newgraphe[i]->valeur = i;
    Newgraphe[i]->arc = NULL;
  }
  return Newgraphe;
}

/**************************************************/
pSommet *CreerArete(pSommet *graphe, int s1, int s2, int valeur)
{
  if (graphe[s1]->arc == NULL)
  {
    pArc Newarc = (pArc)malloc(sizeof(struct Arc));
    Newarc->valeur = valeur;
    Newarc->sommet = s2;
    Newarc->arc_suivant = NULL;
    graphe[s1]->arc = Newarc;
    return graphe;
  }
  else
  {
    pArc temp = graphe[s1]->arc;
    while (!(temp->arc_suivant == NULL))
    {
      temp = temp->arc_suivant;
    }
    pArc Newarc = (pArc)malloc(sizeof(struct Arc));
    Newarc->valeur = valeur;
    Newarc->sommet = s2;
    Newarc->arc_suivant = NULL;

    if (temp->sommet > s2)
    {
      Newarc->arc_suivant = temp->arc_suivant;
      Newarc->sommet = temp->sommet;
      temp->sommet = s2;
      temp->arc_suivant = Newarc;
      return graphe;
    }

    temp->arc_suivant = Newarc;
    return graphe;
  }
}

/**************************************************/
void affiche(pSommet *graphe, int taille)
{
  int i;
  pArc temp;

  for (i = 0; i < taille; i++)
  {
    printf("le sommet %d ", graphe[i]->valeur);
    if (!(graphe[i]->arc == NULL))
    {
      printf("lie a  %d", graphe[i]->arc->sommet);
      temp = graphe[i]->arc;
      while (!(temp->arc_suivant == NULL))
      {
        temp = temp->arc_suivant;
        printf(",%d", temp->sommet);
      }
    }
    printf("\n");
  }
}

/**************************************************/
void InitialParcourLongueur(pSommet *graphe, int taille)
{
  /*Initialisation de la couleur des sommets*/
  /*N=Noir, deja vu.  B=Blanc a voir*/
  printf("\n***PARCOURS EN LONGUEUR***\n");
  int i;
  for (i = 0; i < taille; i++)
  {
    graphe[i]->couleur = 'B';
  }
  for (i = 0; i < taille; i++)
  {
    if (graphe[i]->couleur == 'B')
    {
      printf("%d,", graphe[i]->valeur);
      graphe[i]->couleur = 'N';
      pArc Temparc = graphe[i]->arc;
      while (!(Temparc == NULL))
      {
        ParcourLongueur(graphe, Temparc->sommet, taille);
        Temparc = Temparc->arc_suivant;
      }
    }
  }
  return;
}
/****************************************************/
void ParcourLongueur(pSommet *graphe, int s, int taille)
{
  if (graphe[s]->couleur == 'B')
  {
    printf("%d ", graphe[s]->valeur);
    graphe[s]->couleur = 'N';
    pArc Temparc = graphe[s]->arc;
    while (!(Temparc == NULL))
    {
      ParcourLongueur(graphe, Temparc->sommet, taille);
      Temparc = Temparc->arc_suivant;
    }
  }
  return;
}

/**************************************************/
void InitialParcourLargeur(pSommet *graphe, int taille)
{
  /*Initialisation de la couleur des sommets*/
  /*N=Noir, deja vu.  B=Blanc a voir*/
  printf("\n***PARCOURS EN LARGEUR***\n");
  int i = 0;
  File file = fileVide();
  for (i = 0; i < taille; i++)
  {
    graphe[i]->couleur = 'B';
  }
  enfiler(file, 0);
  while (longueur(file))
  {
    i = defilement(file);
    if (graphe[i]->couleur == 'B')
    {
      pArc Temparc = graphe[i]->arc;
      if (Temparc != NULL)
      {
        enfiler(file, Temparc->sommet);
        while (Temparc->arc_suivant != NULL)
        {
          Temparc = Temparc->arc_suivant;
          enfiler(file, Temparc->sommet);
        }
      }
      printf("%d ", graphe[i]->valeur);
      graphe[i]->couleur = 'N';
    }
  }
  free(file);
  printf("\n");
}

int percorso(pSommet *graphe, int nb_ville, int *tab)
{
  int a = 0;
  pArc temp;

  tab[0]=nb_ville;

  printf("le sommet %d ", graphe[nb_ville]->valeur);

  printf("lie a  %d", graphe[nb_ville]->arc->sommet);
  tab[a + 1] = graphe[nb_ville]->arc->sommet;
  temp = graphe[nb_ville]->arc;
  a =2;
  while (!(temp->arc_suivant == NULL))
  {
    temp = temp->arc_suivant;
    printf(",%d", temp->sommet);
    tab[a] = temp->sommet;
    a++;
  }
  printf("\n");
  return a;
}


