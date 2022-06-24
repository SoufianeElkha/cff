#include "drawing.h"

// Trouver le val0eur minimum
int min_xy(int tot_indice, int *y)
{
	int min = y[0];
	for (int i = 0; i < tot_indice; i++)
		if (min > y[i])
			min = y[i];
	return min;
}
// Trouver la valeur maximale
int max_xy(int tot_indice, int *y)
{
	int max = 1;
	for (int i = 0; i < tot_indice; i++)
		if (max < y[i])
			max = y[i];
	return max;
}

void render(struct gfx_context_t *context, File F)
{
	Cellule cellule;
	cellule = F->tete;

	int *x = (int *)malloc(500 * sizeof(int *));
	int *y = (int *)malloc(500 * sizeof(int *));

	int tot_indice_swiss = lire_file_perimetre("data/swiss.txt", x, y);
	int tot_indice_cities = lire_file(my_cities, "data/cities.csv", 0, 2);

	int min_x = min_xy(tot_indice_swiss, x);
	int min_y = min_xy(tot_indice_swiss, y) / 100;
	int max_y = max_xy(tot_indice_swiss, y);

	int *tab = malloc((tot_indice_cities * tot_indice_cities) * sizeof(int *));
	int a = 0;
	float zoom = 3.5;

	gfx_clear(context, COLOR_WHITE);

	// imprimer le périmètre de la Suisse en noir
	for (int i = 0; i < tot_indice_swiss; i++)
	{
		if (i < tot_indice_swiss - 1)
			gfx_drawline(context, (x[i] - min_x) * zoom, (max_y - y[i] - min_y) * zoom, (x[i + 1] - min_x) * zoom, (max_y - y[i + 1] - min_y) * zoom, COLOR_BLACK);

		if (i == tot_indice_swiss - 1)
			gfx_drawline(context, (x[i] - min_x) * zoom, (max_y - y[i] - min_y) * zoom, (x[0] - min_x) * zoom, (max_y - y[0] - min_y) * zoom, COLOR_BLACK);
	}
	for (int i = 0; i < tot_indice_cities; i++)
	{
		gfx_drawrect(context, (my_cities[i].dist - min_x) * zoom, (max_y - my_cities[i].indice - min_y) * zoom, 10, 10, COLOR_BLUE);
	}

	// imprimer les connexions entre les villes de couleur verte
	for (int i = 0; i < tot_indice_cities; i++)
	{
		if (i < tot_indice_cities - 1)
		{
			gfx_drawline(context, (my_cities[i].dist - min_x) * zoom, (max_y - my_cities[i].indice - min_y) * zoom,
						 (my_cities[i + 1].dist - min_x) * zoom, (max_y - my_cities[i + 1].indice - min_y) * zoom,
						 COLOR_GREEN);
		}
		if (i == tot_indice_cities - 1)
			gfx_drawline(context, (my_cities[i].dist - min_x) * zoom, (max_y - my_cities[i].indice - min_y) * zoom,
						 (my_cities[0].dist - min_x) * zoom, (max_y - my_cities[0].indice - min_y) * zoom,
						 COLOR_GREEN);
	}
	// compter la grandeur liste du trajet pour l’impression
	while (cellule != NULL)
	{
		tab[a] = cellule->element;
		cellule = cellule->suivant;
		a++;
	}

	// imprimer le trajet de couleur rouge
	for (int i = 0; i < a - 1; i++)
	{
		gfx_drawline(context, (my_cities[tab[i]].dist - min_x) * zoom, (max_y - my_cities[tab[i]].indice - min_y) * zoom,
					 (my_cities[tab[i + 1]].dist - min_x) * zoom, (max_y - my_cities[tab[i + 1]].indice - min_y) * zoom,
					 COLOR_RED);
		// Première ville de couleur Rouge plus grande
		gfx_drawrect(context, (my_cities[tab[0]].dist - min_x) * zoom, (max_y - my_cities[tab[0]].indice - min_y) * zoom, 20, 20, COLOR_RED);
		// Chemin des villes avec la couleur rouge
		gfx_drawrect(context, (my_cities[tab[i]].dist - min_x) * zoom, (max_y - my_cities[tab[i]].indice - min_y) * zoom, 10, 10, COLOR_RED);
		gfx_drawrect(context, (my_cities[tab[i + 1]].dist - min_x) * zoom, (max_y - my_cities[tab[i + 1]].indice - min_y) * zoom, 10, 10, COLOR_RED);
	}

	// Libre la mémoire
	free(x);
	free(y);
	free(tab);
	fflush(stdout);
}
