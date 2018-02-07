#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

bool success;
bool cordControl = false;
int cords[4][2];
const Uint16 wWidth = 600;
const Uint16 wHeight = 500;
Uint32 wFlags = SDL_WINDOW_SHOWN;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init();
void close();

bool init(){
	success = true;
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "No se pudo iniciar SDL! %s\n", SDL_GetError() );
		success = false;
	}else if( SDL_CreateWindowAndRenderer(wWidth, wHeight, wFlags, &window, &renderer)){
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "No se pudo crear la ventana ni el renderer! %s\n", SDL_GetError() );
	}
	return success;
}

void close(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[]){
	if( !init() ){
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Fallo al iniciar! \n");
	}else {
		SDL_bool done = SDL_FALSE;
		SDL_Event event;
				
		while (!done){
			int pt1 = 1;
			int pt2 = 2;			

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			//SDL_RenderPresent(renderer);
			
			SDL_SetRenderDrawColor(renderer, 255, 50, 50, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(renderer, cords[0][0], cords[0][1]);
								
			SDL_SetRenderDrawColor(renderer, 50, 255, 50, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawLine(renderer, cords[1][0], cords[1][1], cords[2][0], cords[2][1]);

			SDL_RenderPresent(renderer);
			SDL_Delay(200);
			
			while (SDL_PollEvent (&event)){
				if (event.type == SDL_QUIT){
					done = SDL_TRUE;
				}else if (event.type == SDL_KEYDOWN){
					switch(event.key.keysym.sym){
						case SDLK_w:
						cords[0][1]-=2;
						break;
						case SDLK_s:
						cords[0][1]+=2;
						break;
						case SDLK_d:
						cords[0][0]+=2;
						break;
						case SDLK_a:
						cords[0][0]-=2;
						break;
						case SDLK_ESCAPE:
						done = SDL_TRUE;
					}
				}else if (event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON_LEFT){
					printf("x: %i y: %i\n",event.motion.x, event.motion.y);
					if(!cordControl){
						cordControl = true;
						cords[3][0] = event.motion.x;
						cords[3][1] = event.motion.y;
					}else {
						cordControl = false;
						cords[2][0] = event.motion.x;
						cords[2][1] = event.motion.y;
						cords[1][0] = cords[3][0];
						cords[1][1] = cords[3][1];
					}
				}
			}
		}
	}
	close();
	return 0;
}
