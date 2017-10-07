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
	sdl_window(int _width, int _height, string _title)
	{
		window = nullptr;

		width = _width;
		height = _height;
		title = _title;
	}

	~sdl_window()
	{
		close();
	}

	/// Used for initializing the window/SDL sub-systems
	/// This will make an SDL_Window struct with the parameters passed into the constructor
	/// The function returns a boolean false if any of the SDL sub-systems did not initialize or if the window was not allocated
	/// surface is also initialized here
	bool init ()
	{
		bool success = true;

		// Initializes SDL sub-systems, if it fails a number below 0 is returned
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

private:
	SDL_Window * window;
	sdl_surface surface;

	int width, height;
	string title;

	void close ()
	{
		// No need to call SDL_FreeSurface on surface because SDL_DestroyWindow will take care of surface
		SDL_DestroyWindow(window);

		// Quits SDL systems such as 
		SDL_Quit();
	}
};
