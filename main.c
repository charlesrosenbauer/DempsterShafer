#include "SDL/SDL.h"


typedef struct{
	float a, b;
}Pair;


Pair sum(Pair x, Pair y) {
	Pair q;
	float a  = x.a;
	float b  = x.b;
	float c  = y.a;
	float d  = y.b;
	float a_ = 1.0-a;
	float b_ = 1.0-b;
	float c_ = 1.0-c;
	float d_ = 1.0-d;
	
	float denom = 1.0 - ((a * d) + (b * c));
	q.a = 1.0 - ((a_ * c_) / denom);
	q.b = 1.0 - ((b_ * d_) / denom);
	return q;
}


int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen = SDL_SetVideoMode(512, 1024, 32, 0);

	uint32_t* pixels = screen->pixels;

	Pair a, b;
	a.a = 0;
	a.b = 0;
	b.a = 0;
	b.b = 0;
	
	int shift = 0;
	int cont  = 1;
	SDL_Event e;
	while(cont){
		
		int ix = 0;		
		for(int i = 0; i < 512; i++){
			for(int j = 0; j < 512; j++){
				a.a = ((float)i) / 512.0;
				a.b = ((float)j) / 512.0;
				Pair q = sum(a, b);
				pixels[ix       ] = (256 * q.a);
				pixels[ix+262144] = (256 * q.b);
				ix++;	
			}
		}

		while (SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) cont = 0;
			if(e.type == SDL_KEYDOWN){
				if(e.key.keysym.sym == SDLK_UP    ) b.a += (1.0 / 512.0) * (shift * 51.2);
				if(e.key.keysym.sym == SDLK_DOWN  ) b.a -= (1.0 / 512.0) * (shift * 51.2);
				if(e.key.keysym.sym == SDLK_LEFT  ) b.b += (1.0 / 512.0) * (shift * 51.2);
				if(e.key.keysym.sym == SDLK_RIGHT ) b.b -= (1.0 / 512.0) * (shift * 51.2);
				if(e.key.keysym.sym == SDLK_LSHIFT) shift = 1;
				if(e.key.keysym.sym == SDLK_RSHIFT) shift = 1;
				printf("%f %f\n", b.a, b.b);
			}
			if(e.type == SDL_KEYUP){
				if(e.key.keysym.sym == SDLK_LSHIFT) shift = 0;
				if(e.key.keysym.sym == SDLK_RSHIFT) shift = 0;
			}
		}
		
		SDL_Flip(screen);
		SDL_Delay(16);
	}
	SDL_Quit();
}
