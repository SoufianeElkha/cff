#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "lire_file.h"

void render(struct gfx_context_t *context, int width, int height);

void render(struct gfx_context_t *context, int width, int height)
{
		int *x=(int*)malloc(500*sizeof(int*));
    int *y=(int*)malloc(500*sizeof(int*));
	Liste pos_swiss[4000];
	int pos = lire_file_perimetre("swiss.txt",x,y);

	gfx_clear(context, COLOR_WHITE);
	for (int i = 0; i < pos; i++)
	{
		gfx_drawline(context, x[i], y[i], x[i++], y[i++], COLOR_BLACK);
	}
}

int main(int argc, char **argv)
{



	char buffer[100];
	int width = 1200, height = 900;
	struct gfx_context_t *ctxt = gfx_create("CFF", width, height);
	if (!ctxt)
	{
		fprintf(stderr, "Graphics initialization failed!\n");
		return EXIT_FAILURE;
	}

	do
	{
		render(ctxt, width, height);
		gfx_present(ctxt);
		scanf("%99s", buffer);
	} while (strlen(buffer) > 1 || buffer[0] != 'q');
}