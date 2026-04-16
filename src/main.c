#include <SDL3/SDL.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "graficador.h"
#include "ship.h"
#include "lists.h"
#include "shots.h"
#include "asteroids.h"
#include "draw.h"
#include "move_check.h"

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer("Asteroids",VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);

	int dormir = 0;

	graficador_inicializar("sprites.bin",renderer);
	srand(time(NULL));
	bool up_key=false;
	bool space_key=false;

	unsigned int score=0;
	unsigned int best_score=0;

	unsigned int lifes=4;
	size_t streak=0;
	int wait_time=0;
	float last_angle=NAVE_ANGULO_INICIAL;

	bool starting_level=false;

	ship_t* the_ship=NULL;
	list_t* shots_list=NULL;
	list_t* asteroids_list=NULL;

	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				break;
	    		if (event.type == SDL_EVENT_KEY_DOWN) {
				switch(event.key.key) {
					case SDLK_UP:
						if((!up_key)&&(the_ship))
						{
							ship_apply_impulse(the_ship);
							up_key=true;
						}
						break;
					case SDLK_SPACE:
						if((!space_key)&&(the_ship)&&(shots_list))
							list_insert_at_beginning(shots_list,shot_create(the_ship));
						if((!space_key)&&(!the_ship))
							starting_level=true;
						space_key=true;
						break;
					case SDLK_RIGHT:
						if(the_ship)
							ship_rotate_right(the_ship);
						break;
					case SDLK_LEFT:
						if(the_ship)
							ship_rotate_left(the_ship);
						break;
				}
			}
			if (event.type == SDL_EVENT_KEY_UP) {
				switch(event.key.key) {
					case SDLK_UP:
						up_key=false;
						break;
					case SDLK_SPACE:
						space_key=false;
						break;
				}
			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

		if(!asteroids_list)
		{
			if(asteroids_list)
				list_destroy(asteroids_list,(destroy_data)asteroid_destroy);
			asteroids_list = list_create();
			if(!asteroids_list)
				break;

			if(shots_list)
				list_destroy(shots_list,(destroy_data)shot_destroy);
			shots_list = list_create();
			if(!shots_list)
				break;

			starting_level=false;
		}

		if((starting_level)&&(!wait_time)&&(!the_ship))
		{
			the_ship = ship_create(last_angle);
			if(!the_ship)
				break;

			wait_time=1;
			starting_level=false;
		}

		if(list_is_empty(asteroids_list))
		{
			check_asteroids_quantity(asteroids_list,&streak);
		}

		move_shots_list(shots_list);

		if(move_asteroids_check_collition(the_ship,shots_list,asteroids_list,&last_angle,&wait_time,&starting_level,&score,DT))
			the_ship=NULL;

		if(the_ship)
		{
			ship_move(the_ship,DT);
			ship_draw(the_ship);
		}

		if(wait_time>0)
			wait_time--;

		if((!the_ship)&&(wait_time==99))
		{
			lifes--;
			starting_level=true;
		}

		if(!lifes)
		{
			if(score>best_score)
				best_score=score;

			draw_game_over_status(score,LETTERS_SCALE_FACTOR*4,renderer);

			score=0;
			lifes=4;
			streak=0;
			wait_time=0;

			if(asteroids_list)
				list_destroy(asteroids_list,(destroy_data)asteroid_destroy);
			asteroids_list = list_create();
			if(!asteroids_list)
				break;

			starting_level=false;

			dormir=5000;
		}

		if((lifes==4)&(!the_ship))
		{
			draw_status(0,best_score,0,LETTERS_SCALE_FACTOR,renderer);
		}
		else
		{
			draw_status(score,best_score,lifes,LETTERS_SCALE_FACTOR,renderer);
		}

        SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	if(shots_list)
		list_destroy(shots_list,(destroy_data)shot_destroy);
	if(asteroids_list)
		list_destroy(asteroids_list,(destroy_data)asteroid_destroy);
	if(the_ship)
		ship_destroy(the_ship);

	graficador_finalizar();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

