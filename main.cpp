#include <iostream>
//#include <SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>//delay
#include <string>
#include "header.h"
//soem problems in larger files with global vars, idc for smaller

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr; // surface? use renderer?
SDL_Surface* gCurrentSurface = nullptr; //Image loading?
SDL_Surface* loadSurface (std::string patha)
{
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* loadedSurface = SDL_LoadBMP(patha.c_str());
	if(loadedSurface == nullptr) {std::cerr << "error loading next bmps" << patha.c_str() << '\n'; }
	else {
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface ->format, 0 );	
	}
	SDL_FreeSurface( loadedSurface ); //SDL_ConvertSurface returns sa copy of original loaded surface, so we have two. So we free one of them.
	return optimizedSurface;

}
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

bool init()
{
	if(SDL_Init( SDL_INIT_VIDEO ) != 0 ) {	std::cerr << "error initialization of SDL_INIT_VIDEO\n" << SDL_GetError(); return false; }
	else {
			SDL_DisplayMode displayMode;
			if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) { std::cerr << "could not get display mode" << SDL_GetError(); SDL_Quit(); return 1; }

		gWindow = SDL_CreateWindow("bitch base", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, displayMode.w, displayMode.h, SDL_WINDOW_SHOWN); //SDL_WINDOW_FULLSCREEN_DESKTOP
		if(gWindow == nullptr) {return false; }
		gScreenSurface = SDL_GetWindowSurface( gWindow);
	}
	if(gWindow == nullptr) {return false; }
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	return true;
}

bool loadMedia()
{
	/*
	gCurrentSurface = IMG_Load("img/base.jpg");
	if(gCurrentSurface == nullptr) { std::cerr << "error loading media\n"; return false; }
	return true;
	*/
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP] = loadSurface("img/up.bmp");
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN] = loadSurface("img/down.bmp");
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT] = loadSurface("img/right.bmp");
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT] = loadSurface("img/left.bmp"); //add erorr handling
	gCurrentSurface = SDL_LoadBMP("img/base.bmp");
	if(gCurrentSurface == nullptr) {std::cerr << "error loading bmp\n"; return false; }
	return true;
}

void cleanup()
{
	SDL_FreeSurface( gCurrentSurface );
	gCurrentSurface = nullptr;

	SDL_DestroyWindow(gWindow); //takes care of gScreenSurface
	gWindow = nullptr;

	SDL_Quit();	
}
int main()
{
	gCurrentSurface = gKeyPressSurfaces [KEY_PRESS_SURFACE_DEFAULT];
	bool quit = false;
	if(init() == false) {std::cout << "failure initalization\n"; }
	if(loadMedia() == false) {std::cout << "failure loading Media\n"; }
	SDL_Event e;
	while(!quit){
		while( SDL_PollEvent(&e) != 0 )
		{//fuck around
			if(e.type == SDL_QUIT) {quit = true;}	
			else if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym) //wtf is this?
				{
					case SDLK_UP:
					     gCurrentSurface = gKeyPressSurfaces [KEY_PRESS_SURFACE_UP];
					     break;
					case SDLK_DOWN:
					     gCurrentSurface = gKeyPressSurfaces [KEY_PRESS_SURFACE_DOWN];
					     break;
					case SDLK_LEFT:
					     gCurrentSurface = gKeyPressSurfaces [KEY_PRESS_SURFACE_LEFT];
					     break;
					case SDLK_RIGHT:
					     gCurrentSurface = gKeyPressSurfaces [KEY_PRESS_SURFACE_RIGHT];
					     break;
					default:
					     gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					     break;
				}
			}
		}
		SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
	}

	cleanup();
}
