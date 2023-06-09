#ifndef _DRAWING_H
#define _DRAWING_H

#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "lire_file.h"
#include "file.h"
#include "cellule.h"

void render(struct gfx_context_t *context, File F);
int min_xy(int tot_indice, int *y);
int max_xy(int tot_indice, int *y);

#endif