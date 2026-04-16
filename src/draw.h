#ifndef _DRAW_H_
#define _DRAW_H_

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dictionary.h"

#define SCALE_FACTOR	1.0
#define LETTERS_SCALE_FACTOR	VENTANA_ALTO/800.0

#define FIRST_ROW	VENTANA_ALTO*23/25.0
#define ROW_SIZE	2*CARACTER_ALTO*LETTERS_SCALE_FACTOR
#define FIRST_COLUMN	VENTANA_ANCHO/8.0

#define SHIP_ANCHO 3*CARACTER_ANCHO

void draw_vector(float **v,size_t vector_size,float pos_x,float pos_y,float scale_factor,SDL_Renderer* renderer);

void draw_status(int score,int best_score,int lifes,float letters_scale_factor,SDL_Renderer* renderer);
void draw_game_over_status(int score,float letters_scale_factor,SDL_Renderer* renderer);

#endif //_DRAW_H_

