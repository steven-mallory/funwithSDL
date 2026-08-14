#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_CreateWindow("Base", 100, 100, 800, 300, 0);

	while(true)
	{
		SDL_PumpEvents();
	}
}
