#include <string>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>

SDL_Window* wind = nullptr;
SDL_Renderer* rend = nullptr;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
bool init()
{
	if(SDL_Init( SDL_INIT_VIDEO ) != 0 ) {std::cerr << "error init\n"; return false;}
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	SCREEN_WIDTH = DM.w; SCREEN_HEIGHT = DM.h; 
	wind = SDL_CreateWindow("base", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DM.w, DM.h, SDL_WINDOW_SHOWN);
	if(wind == nullptr) {return false;}
	rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);
	if(rend == nullptr) {return false;}
	return true;

}
SDL_Texture* loadMedia(std::string spath)
{//error rhandling, nullptr handling
	SDL_Texture* r;
	SDL_Surface* s = IMG_Load(spath.c_str());	
	r = SDL_CreateTextureFromSurface(rend, s);
	return r;
}
/*
SDL_Texture* loadTexture(std::string p)
{//error handling for nullptrs
	SDL_Surface* sur = IMG_LOad(p.c_str());
	SDL_Texture* ptr = SDL_CreateTextureFromSurface(rend, sur);	
	return ptr;
}*/
void cleanup()
{
	SDL_DestroyWindow(wind);
	wind = nullptr;
	SDL_DestroyRenderer(rend);
	rend = nullptr;
}
int main(int argc, char* argv[])
{
	init();
	bool flag = false;
	SDL_Event e;
	SDL_Rect topLeftViewport = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
	SDL_Rect topRightViewport = {SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
	SDL_Rect bottomViewport = { 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2 };
	SDL_Rect fullViewport = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	while(!flag) {
		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {flag = true; }
			else if(e.type == SDL_KEYDOWN)
			{
				//switch(e.key.keysym.sym)
			}
		}//end polling
		SDL_SetRenderDrawColor( rend, 122, 122, 122, 255);
		SDL_RenderFillRect( rend, &topLeftViewport);
		SDL_SetRenderDrawColor( rend, 122, 12, 122, 255);
		SDL_RenderFillRect( rend, &topRightViewport);
		SDL_SetRenderDrawColor( rend, 10, 122, 122, 255);
		SDL_RenderFillRect( rend, &bottomViewport);
		SDL_SetRenderDrawColor( rend, 122, 122, 122, 255);
		SDL_RenderSetViewport(rend, &topLeftViewport);
		SDL_Texture* text = loadMedia("img/lain.jpg");
		SDL_RenderCopy(rend, text, NULL, NULL);

		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		SDL_RenderSetViewport(rend, &fullViewport);
		SDL_SetRenderDrawColor(rend, 250, 12, 12, 25); // red
		SDL_RenderFillRect( rend, &fillRect);

		SDL_SetRenderDrawColor(rend, 1, 12, 255, 255);
		SDL_RenderDrawLine(rend, 0, SCREEN_HEIGHT / 3, SCREEN_WIDTH, SCREEN_HEIGHT / 3 );
		SDL_SetRenderDrawColor(rend, 220, 220, 25, 255);
		for(int i = 0; i < SCREEN_WIDTH; i += 4)
		{
			SDL_RenderDrawPoint(rend, i, SCREEN_HEIGHT/2);
		}
		
		SDL_RenderPresent(rend);
	}
	cleanup();
}
