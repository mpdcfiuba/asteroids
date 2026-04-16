#include <SDL3/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "draw.h"
#include "config.h"
#include "caracteres.h"
#include "graficador.h"

void draw_vector(float **v,size_t vector_size,float pos_x,float pos_y,float scale_factor,SDL_Renderer* renderer)
{
	for(size_t i=0; i < (vector_size - 1); i++)
			SDL_RenderLine(
				renderer,
				v[i][0] * scale_factor + pos_x,
				VENTANA_ALTO - (v[i][1] * scale_factor + pos_y),
				v[i+1][0] * scale_factor + pos_x,
				VENTANA_ALTO - (v[i+1][1] * scale_factor + pos_y)
			);
}

static void draw_vector_letra(character_t v,size_t vector_size,float pos_x,float pos_y,float scale_factor,SDL_Renderer* renderer)
{
	for(size_t i=0; i < (vector_size - 1); i++)
			SDL_RenderLine(
				renderer,
				v[i][0] * scale_factor + pos_x,
				VENTANA_ALTO - (v[i][1] * scale_factor + pos_y),
				v[i+1][0] * scale_factor + pos_x,
				VENTANA_ALTO - (v[i+1][1] * scale_factor + pos_y)
			);
}

void draw_phrase(char* phrase,float init_pos_x,float init_pos_y,float letters_scale_factor,SDL_Renderer* renderer)
{
	size_t phrase_size=strlen(phrase);
	dictionary_t* the_letter=NULL;
	
	for(size_t i=0;i<phrase_size;i++)
	{
		letter_to_func(phrase[i],&the_letter);
		draw_vector_letra(the_letter->character,the_letter->size,init_pos_x+(CARACTER_ANCHO*i*letters_scale_factor),init_pos_y,letters_scale_factor,renderer);
	}
}

void draw_status(int score,int best_score,int lifes,float letters_scale_factor,SDL_Renderer* renderer)
{
	if(lifes)
	{
		char string[5];
		sprintf(string,"%d",score);
		draw_phrase(string,FIRST_COLUMN,FIRST_ROW,letters_scale_factor*4,renderer);
	
		sprintf(string,"%d",best_score);
		draw_phrase(string,VENTANA_ANCHO/2,FIRST_ROW,letters_scale_factor*1.5,renderer);
	}
	
	for(size_t i=0;i<lifes;i++)
	{
		graficador_dibujar("SHIP",letters_scale_factor,CARACTER_ANCHO+FIRST_COLUMN+i*SHIP_ANCHO,FIRST_ROW-2*ROW_SIZE,PI/2.0);
	}
}

void draw_game_over_status(int score,float letters_scale_factor,SDL_Renderer* renderer)
{
	draw_phrase("GAME OVER",VENTANA_ANCHO/2-2.5*CARACTER_ANCHO*letters_scale_factor,FIRST_ROW-3*CARACTER_ALTO*letters_scale_factor,letters_scale_factor/1.5,renderer);
	
	char string[5];
	sprintf(string,"%d",score);
	draw_phrase(string,FIRST_COLUMN,FIRST_ROW,letters_scale_factor,renderer);
}
