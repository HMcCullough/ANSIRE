#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "sdl_surface.h"

using std::string;
using std::cout;

class sdl_window
{
public:
	// Constructors/Destuctors
	sdl_window(int _width, int _height, string _title)
	{
		window = nullptr;

		width = _width;
		height = _height;
		title = _title;
	}

	~sdl_window()
	{
		_close();
	}

	// Getter/Setter Accessors

	/// Used for initializing the window/SDL sub-systems
	/// This will make an SDL_Window struct with the parameters passed into the constructor
	/// The function returns a boolean false if any of the SDL sub-systems did not initialize or if the window was not allocated
	/// surface is also initialized here
	bool init (Uint32 initFlags = SDL_INIT_EVERYTHING)
	{
		bool success = true;

		// Initializes SDL sub-systems, if it fails a number below 0 is returned
		if (SDL_Init(initFlags) < 0)
		{
			// SDL_GetError will get an error if one exists
			cout << "SDL did not initialize properly.\nSDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Creates the window with the parameters passed into the constructor
			// We might want to change the SDL_WINDOW_UNDEFINED later, but it defaults to the center of the screen so it should be fine
			window = SDL_CreateWindow(title.c_str(),
						  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // Here we can define starting window position
						  width, height,
						  SDL_WINDOW_SHOWN);
			if (window != nullptr)
			{
				// If we successfully created a window, we can retrieve that window's surface
				// Surface is the modifiable pixel array of window
				surface = sdl_surface(window);
			}
			else
			{
				cout << "SDL could not create a window.\nSDL_Error: " << SDL_GetError() << std::endl;
				success = false;
			}
		}
		return success;
	}

	/// Any changes to surface will be rendered when update is called
	void update ()
	{
		SDL_UpdateWindowSurface(window);
	}

	void blitSurface(sdl_surface &surfaceData)
	{
		_optimizeSurface(surfaceData);
		if (SDL_BlitSurface(surfaceData.surface, NULL, surface.surface, NULL) < 0)
		{
			cout << "Surface Blit was unsuccessful\nSDL Error: " << SDL_GetError() << std::endl;
		}
	}

private:
	SDL_Window * window;
	sdl_surface surface;

	int width, height;
	string title;

	void _close ()
	{
		// No need to call SDL_FreeSurface on surface because SDL_DestroyWindow will take care of surface
		SDL_DestroyWindow(window);

		// Quits SDL systems such as 
		SDL_Quit();
	}

	/// Optimizes a given surface to the window so that SDL_BlitSurface will be more efficient
	void _optimizeSurface(sdl_surface &noOpSurface)
	{
		if (window == nullptr)
			return;

		SDL_Surface * opSurface = nullptr;
		opSurface = SDL_ConvertSurface(noOpSurface.surface, surface.surface->format, 0);
		if (opSurface == nullptr)
		{
			cout << "Error optimizing surface\nSDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			try
			{
				noOpSurface.free();
			}
			catch (InvalidSurfaceDeallocate)
			{
				// This means that the surface is already optimized to a the window
				return;
			}

			noOpSurface.surface = opSurface;
		}
	}
};
