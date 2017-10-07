#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "sdl_exceptions.h"

using std::string;
using std::cout;

class sdl_surface
{
public:
	sdl_surface(SDL_Window * window = nullptr)
	{
		// If the surface was created from a window we mark it as a window surface
		// Does not keep track of doulbe-buffered systems at the moment
		isWindowSurface = (window != nullptr);
		if (isWindowSurface)
			surface = SDL_GetWindowSurface(window);
		else
			surface = nullptr;
	}

	~sdl_surface()
	{
		// We do not free a window surface because that is supposed to be handled in the sdl_window class wrapper
		if (!isWindowSurface)
			free();
	}

	/// Returns whether of not the surface belongs to a window
	/// Check this before calling free, if not checked free can throw exception
	bool windowSurface()
	{
		return isWindowSurface;
	}

	/// Will load BMP data into a surface if the surface does not belong to a window
	/// If the BMP did not load properly or the surface is already allocated, load will return false
	bool load (string path)
	{
		bool success = true;

		// Surface has not already been allocated
		if (surface == nullptr)
		{
			// Loads the surface from a BMP file path
			surface = SDL_LoadBMP(path.c_str());
			if (surface == nullptr)
			{
				cout << "SDL could not load surface: " << path << "\nSDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
		}
		else if (!isWindowSurface)
		{
			cout << "Surface already allocated, call free first" << std::endl;
			success = false;
		}
		else // We don't want the user trying to load a bmp over a window's surface, we use blit for that!
		{
			cout << "Surface belongs to a window, do NOT deallocate" << std::endl;
			success = false;
		}

		return success;
	}

	/// Frees the current surface so that new data can be loaded into it
	/// Throws an exception if the surface belongs to a window since it cannot be freed
	void free ()
	{
		if (!isWindowSurface)
		{
			SDL_FreeSurface(surface);
			surface = nullptr;
		}
		else
			throw InvalidSurfaceDeallocate(); // Cannot deallocate a surface that belongs to a window, very bad idea
	}

private:
	SDL_Surface * surface;
	bool isWindowSurface;
};
