#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
bool init(SDL_Window* wind, SDL_Renderer* rend, SDL_Rect* rect)
{
if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) { std::cerr << "failed SDL init\n"; return false; }
SDL_DisplayMode d;
SDL_GetCurrentDisplayMode(0, &d);
wind = SDL_CreateWindow( "base", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, d.w/2, d.h/2, SDL_WINDOW_SHOWN );
if(wind == nullptr) { std::cerr << "error init wind\n"; return false; }
rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);
if(rend == nullptr) { std::cerr << "error init rend\n"; return false; }
SDL_SetRenderDrawColor( rend, 200, 200, 200, 255);
rect->x = 0;
rect->y = 0;
rect->w = d.w;
rect->h = d.h;
return true;
}

bool loadMedia()
{
return true;
}

void cleanup(SDL_Window* wind, SDL_Renderer* rend)
{
SDL_DestroyWindow(wind);
wind = nullptr;
SDL_DestroyRenderer(rend);
rend = nullptr;
SDL_Quit();

}
int main(int argc, char* argv[])
{
SDL_Window* wind = nullptr;
SDL_Renderer* rend = nullptr;
SDL_Rect fullViewport;
init(wind, rend, &fullViewport);
SDL_Event e;
bool quit = false;
while(!quit) {
while(SDL_PollEvent(&e) != 0) {
if(e.type == SDL_QUIT) {quit = true; }
}
SDL_SetRenderDrawColor(rend, 240, 14, 23, 255);
SDL_RenderClear(rend);

SDL_SetRenderDrawColor(rend, 12, 12, 12, 255);
SDL_RenderFillRect(rend, &fullViewport);
SDL_RenderPresent(rend);
}
cleanup(wind, rend);
}


