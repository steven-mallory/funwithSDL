#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL_image.h>

bool init(SDL_Window* win, SDL_Renderer* rend)
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO < 0) )
	{	std::cerr << "error!\n"; success = false; }
	else {
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		int x, y;

		win = SDL_CreateWindow("base bitch", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dm.w, dm.h,SDL_WINDOW_SHOWN);	
		if(win == nullptr) {std::cerr<< "error!" <<SDL_GetError(); success = false; }
		else {
			rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
			if(rend == nullptr) {std::cerr << "error with rend!" << SDL_GetError(); success = false; }
			else {
				SDL_SetRenderDrawColor(rend, 0xFF,0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG; //2
				if ( !(IMG_Init( imgFlags ) & imgFlags) )
				{
					std::cerr << "error with img initalization " << IMG_GetError();
					success = false;
				}

			}
		}
	}
	return success;

}

SDL_Texture* loadTexture(std::string path, SDL_Texture* text, SDL_Renderer* rend)
{
	SDL_Texture* finalText = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());	
	if(loadedSurface == nullptr) {std::cerr << " error with path " << path.c_str() << IMG_GetError();}
	else {
		finalText = SDL_CreateTextureFromSurface(rend, loadedSurface);
		if(finalText == nullptr) {std::cout << "failure with final text initalization " << SDL_GetError(); }
		else{ SDL_FreeSurface(loadedSurface); }
	}
	return finalText;
}
bool loadMedia(SDL_Texture* text, SDL_Renderer* rend)
{
	bool success = true;
	text = loadTexture("img/base.jpg", text, rend);
	if(text == nullptr) {success = false; std::cerr << "failed text " << SDL_GetError(); }
	return success;

}

void close(SDL_Window* win, SDL_Renderer* rend, SDL_Texture* text)
{
	SDL_DestroyTexture(
}

int main(int argc, char *argv[])
{
	SDL_Window* win;
	SDL_Renderer* rend;
	SDL_Texture* text;
	init(win, rend);
	loadMedia(text, rend);
}
