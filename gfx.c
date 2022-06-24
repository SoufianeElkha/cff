/// @file gfx.c
/// @author Florent Gluck, modified by Pierre Kunzli
/// @date May 17 2022
/// Helper routines to render pixels in resizable graphic mode.
/// Uses the SDL2 library.

#include <assert.h>
#include "gfx.h"

/// Create graphic window.
/// @param title Title of the window.
/// @param width Width of the window in pixels.
/// @param height Height of the window in pixels.
/// @return a pointer to the graphic context or NULL if it failed.
struct gfx_context_t* gfx_create(char *title, uint width, uint height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) goto error;
	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	uint32_t *pixels = malloc(width*height*sizeof(uint32_t));
	struct gfx_context_t *ctxt = malloc(sizeof(struct gfx_context_t));

	if (!window || !renderer || !texture || !pixels || !ctxt) goto error;

	ctxt->renderer = renderer;
	ctxt->texture = texture;
	ctxt->window = window;
	ctxt->width = width;
	ctxt->height = height;
	ctxt->pixels = pixels;

	SDL_ShowCursor(SDL_DISABLE);
	gfx_clear(ctxt, COLOR_BLACK);
	return ctxt;

error:
	return NULL;
}

/// Draw a line in the specified graphic context.
/// @param ctxt Graphic context where the line is to be drawn.
/// @param x1 X coordinate of the starting point of the line.
/// @param y1 Y coordinate of the starting point of the line.
/// @param x2 X coordinate of the end point of the line.
/// @param y2 Y coordinate of the end point of the line.
/// @param color Color of the line.
void gfx_drawline(struct gfx_context_t *ctxt, int x1, int y1, int x2, int y2, uint32_t color){
    SDL_SetRenderDrawColor(ctxt->renderer, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(ctxt->renderer, x1, y1, x2, y2);
}

/// Draw a rectangle in the specified graphic context.
/// @param ctxt Graphic context where the line is to be drawn.
/// @param x X coordinate of the center of the rectangle.
/// @param y Y coordinate of the center of the rectangle.
/// @param width Width of the rectangle.
/// @param height Height of the rectangle.
/// @param color Color of the rectangle.
void gfx_drawrect(struct gfx_context_t *ctxt, int x, int y, int width, int height, uint32_t color){
    SDL_SetRenderDrawColor(ctxt->renderer, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), SDL_ALPHA_OPAQUE);
    SDL_Rect r = {x-width/2, y-width/2, width, height};
    SDL_RenderFillRect(ctxt->renderer, &r);
}

/// Draw a pixel in the specified graphic context.
/// @param ctxt Graphic context where the pixel is to be drawn.
/// @param x X coordinate of the pixel.
/// @param y Y coordinate of the pixel.
/// @param color Color of the pixel.
void gfx_putpixel(struct gfx_context_t *ctxt, int x, int y, uint32_t color) {
	if (x < ctxt->width && y < ctxt->height)
		ctxt->pixels[ctxt->width*y+x] = color;
}

/// Get a pixel in the specified graphic context.
/// @param ctxt Graphic context where we want to get the pixel.
/// @param x X coordinate of the pixel.
/// @param y Y coordinate of the pixel.
/// @param color Color of the pixel.
/// @return color at position x, y.
uint32_t gfx_getpixel(struct gfx_context_t *ctxt, int x, int y) {
	assert(x >= 0 && x < ctxt->width && y >= 0 && y < ctxt->height);
	return ctxt->pixels[ctxt->width*y+x];
}

/// Clear the specified graphic context.
/// @param ctxt Graphic context to clear.
/// @param color Color to use.
void gfx_clear(struct gfx_context_t *ctxt, uint32_t color) {
	int n = ctxt->width*ctxt->height;
	while (n)
		ctxt->pixels[--n] = color;

    SDL_UpdateTexture(ctxt->texture, NULL, ctxt->pixels, ctxt->width*sizeof(uint32_t));
	SDL_RenderCopy(ctxt->renderer, ctxt->texture, NULL, NULL);
}

/// Display the graphic context.
/// @param ctxt Graphic context to clear.
void gfx_present(struct gfx_context_t *ctxt) {
	SDL_RenderPresent(ctxt->renderer);
}

/// Destroy a graphic window.
/// @param ctxt Graphic context of the window to close.
void gfx_destroy(struct gfx_context_t *ctxt) {
	SDL_ShowCursor(SDL_ENABLE);
	SDL_DestroyTexture(ctxt->texture);
	SDL_DestroyRenderer(ctxt->renderer);
	SDL_DestroyWindow(ctxt->window);
	free(ctxt->pixels);
	ctxt->texture = NULL;
	ctxt->renderer = NULL;
	ctxt->window = NULL;
	ctxt->pixels = NULL;
	SDL_Quit();
	free(ctxt);
}

/// If a key was pressed, returns its key code (non blocking call).
/// List of key codes: https://wiki.libsdl.org/SDL_Keycode
/// @return the key that was pressed or 0 if none was pressed.
SDL_Keycode gfx_keypressed() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN)
			return event.key.keysym.sym;
	}
	return 0;
}
