#include <SDL3/SDL_render.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL3/SDL.h>

#include "graficador.h"
#include "draw.h"
#include "vector.h"
#include "dictionary.h"
#include "config.h"
#include "caracteres.h"

#define READ_PER_CYCLE 7

struct sprite_s
{
	char sprite_name[10];
	size_t sprite_lenght;
	float** sprite_vector;
};

static SDL_Renderer* renderer;
static sprite_t* sprites = NULL;
static size_t sprite_quantity=0;

typedef float (*td_vector)[2];

bool graficador_inicializar(const char* fn,SDL_Renderer* renderer_received)
{
	FILE* fp = NULL;
	fp = fopen(fn,"rb");
	if(!fp)
	{
		return false;
	}

	sprite_t* sprites_aux = NULL;

	sprite_quantity = 0;
	size_t requested=0;

	char name[10];

	while((fread(&name,sizeof(char),10,fp))>1)
	{
		if(requested==sprite_quantity)
		{
			sprites_aux = realloc(sprites,sizeof(sprite_t)*(sprite_quantity+READ_PER_CYCLE));
			if(!sprites_aux)
			{
				if(sprites)
				{
					for(size_t i=0;i<sprite_quantity;i++)
						vector_destroy((sprites[i]).sprite_vector,(sprites[i]).sprite_lenght);

					free(sprites);
					sprites=NULL;
				}
				sprite_quantity = 0;
				fclose(fp);
				return false;
			}
			sprites=sprites_aux;
			sprites_aux=NULL;
			requested+=READ_PER_CYCLE;
		}




		strcpy(sprites[sprite_quantity].sprite_name,name);

		uint16_t aux_lenght;
    bool result = fread(&aux_lenght, sizeof(uint16_t), 1, fp);
    if (result)
      result = !result;
		size_t fixed_lenght = (size_t)aux_lenght;
		((sprites[sprite_quantity]).sprite_lenght) = fixed_lenght;

		if(((sprites[sprite_quantity].sprite_vector) = vector_create(fixed_lenght))==NULL)
		{
			graficador_finalizar();
			return false;
		}

		td_vector sprite_read;
		sprite_read=malloc(sizeof(float)*fixed_lenght*2);
    result = fread(sprite_read, sizeof(float), fixed_lenght * 2, fp);
    if (result)
      result = !result;
		vector_const_copy(sprite_read,((sprites[sprite_quantity]).sprite_vector),fixed_lenght);
		free(sprite_read);

		sprite_quantity++;
	}

	renderer = renderer_received;
	fclose(fp);
	return true;
}



void graficador_finalizar()
{
	for(size_t i = 0;i<sprite_quantity;i++)
	{
		vector_destroy((sprites[i]).sprite_vector,(sprites[i]).sprite_lenght);
	}


	free(sprites);
	sprites = NULL;
	sprite_quantity = 0;
	renderer = NULL;
}


void graficador_ajustar_variables(float *x_old,float* y_old)
{
	if(x_old&&y_old)
	{
		int width=0;
		int height=0;
		SDL_GetCurrentRenderOutputSize(renderer,&width,&height);

		if((*x_old)>0)
		{
			while((*x_old)>width)
				(*x_old)-=width;
		}
		else
		{
			while((*x_old)<0)
				(*x_old)+=width;
		}

		if((*y_old)>0)
		{
			while((*y_old)>height)
				(*y_old)-=height;
		}
		else
		{
			while((*y_old)<0)
				(*y_old)+=height;
		}
	}
}

bool graficador_dibujar(const char* name,float scale_factor,float x,float y,float angle)
{
	for(size_t i=0;i<sprite_quantity;i++)
	{
		if(!strcmp(name,(sprites[i].sprite_name)))
		{
			float** sprite_to_print = vector_create_n_copy((const float**)(sprites[i].sprite_vector),(sprites[i].sprite_lenght));
			vector_rotate(sprite_to_print,(sprites[i].sprite_lenght),angle);
			draw_vector(sprite_to_print,sprites[i].sprite_lenght,x,y,scale_factor,renderer);
			return true;
		}
	}
	return false;
}
