/*cellule.h*/
#ifndef _CELLULE_H
#define _CELLULE_H

typedef int typage;

struct _cellule
{
   typage element;
   struct _cellule *suivant;
};

typedef struct _cellule *Cellule;

#endif