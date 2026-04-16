#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sprite_s sprite_t;

bool graficador_inicializar(const char* fn,SDL_Renderer *renderer);
void graficador_finalizar();
bool graficador_dibujar(const char* name,float scale_factor,float x,float y,float angle);
void graficador_ajustar_variables(float* x,float* y);

#endif //_GRAFICADOR_H_
