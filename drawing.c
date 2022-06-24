#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "lire_file.h"
#include "drawing.h"


int min_xy(int tot_indice, int *y)
{
	int min = y[0];
	for (int i = 0; i < tot_indice; i++)
		if (min > y[i])
			min = y[i];
	return min;
}

int max_xy(int tot_indice, int *y)
{
	int max = 1;
	for (int i = 0; i < tot_indice; i++)
		if (max < y[i])
			max = y[i];
	return max;
}

void render(struct gfx_context_t *context)
{
	int *x = (int *)malloc(500 * sizeof(int *));
	int *y = (int *)malloc(500 * sizeof(int *));
	//Liste pos_swiss[4000];
	int tot_indice_swiss = lire_file_perimetre("data/swiss.txt", x, y);
	int tot_indice_cities = lire_file(my_cities, "data/cities.csv", 0, 2);

	int min_x = min_xy(tot_indice_swiss, x);
	int min_y = min_xy(tot_indice_swiss, y) / 80;
	//int max_x = max_xy(tot_indice_swiss, x);
	int max_y = max_xy(tot_indice_swiss, y);
	int zoom = 2;
	// printf("Tot indice %d\n", tot_indice_cities);

	gfx_clear(context, COLOR_WHITE);
	for (int i = 0; i < tot_indice_swiss; i++)
	{
		gfx_drawline(context, (x[i] - min_x) * zoom, (max_y - y[i] - min_y) * zoom, (x[i++] - min_x) * zoom, (max_y - y[i++] - min_y) * zoom, COLOR_BLACK);
	}
	for (int i = 0; i < tot_indice_cities; i++)
	{
		gfx_drawrect(context, (my_cities[i].dist - min_x) * zoom, (max_y - my_cities[i].indice - min_y) * zoom, 10, 10, COLOR_BLUE);
	}
	for (int i = 0; i < tot_indice_cities; i++)
	{
		gfx_drawline(context, (my_cities[i].dist - min_x) * zoom, (max_y - my_cities[i].indice - min_y) * zoom,
					 (my_cities[i++].dist - min_x) * zoom, (max_y - my_cities[i++].indice - min_y) * zoom,
					 COLOR_RED);
	}

	// printf("valore %d %d\n", my_cities[i].dist ,my_cities[i].indice);
}

// int main(int argc, char **argv)
// {
// 	int arr = 0;
// 	char buffer[100];
// 	int width = 1250, height = 1000;
// 	while (/*strlen(buffer) > 1 ||*/ buffer[0] != 'q')
// 	{
// 		scanf("%99s", buffer);
// 		if (buffer[0] = 'a')
// 		{
// 			struct gfx_context_t *ctxt = gfx_create("CFF", width, height);
// 			if (!ctxt)
// 			{
// 				fprintf(stderr, "Graphics initialization failed!\n");
// 				return EXIT_FAILURE;
// 			}
// 			render(ctxt, width, height);
// 			gfx_present(ctxt);
// 			scanf("%99s", buffer);
// 		}
// 	}
// }
