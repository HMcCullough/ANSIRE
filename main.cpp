#include "sdl_window.h"

// Sample main, prints lines of characters and then layers TEST in the middle.
int main(void) {

	sdl_window window(1000, 500, "Title");
	window.init();

	SDL_Event e;
	bool quit = false;

	sdl_surface image;
	image.loadBMP("./hello_world.bmp");

	window.blitSurface(image);
	window.update();
	while (!quit)
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				default: break;
			}
		}

	return 0;
}
