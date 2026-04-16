#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "shots.h"
#include "graficador.h"
#include "draw.h"
#include "computar.h"

#define SHOT_SPEED 1000
#define SHOT_LIFETIME 70

struct shot_s
{
	float pos_x;
	float pos_y;
	float angle;
	unsigned int remaining_time;
};

shot_t* shot_create(const ship_t* the_ship)
{
	shot_t* shot = malloc(sizeof(shot_t));
	if(!shot)
		return NULL;
	shot_set_parameters(shot,the_ship);
	return shot;
}

void shot_destroy(shot_t* shot)
{
	free (shot);
}

void shot_set_parameters(shot_t* shot,const ship_t* the_ship)
{
	shot->pos_x = ship_get_pos_x(the_ship);
	shot->pos_y = ship_get_pos_y(the_ship);
	shot->angle = ship_get_angle(the_ship);
	shot->remaining_time = SHOT_LIFETIME;
}

float shot_get_pos_x(const shot_t* shot)
{
	return shot->pos_x;
}

float shot_get_pos_y(const shot_t* shot)
{
	return shot->pos_y;
}

bool shot_draw(const shot_t* shot)
{
	return graficador_dibujar("SHOT",SCALE_FACTOR,shot->pos_x,shot->pos_y,shot->angle);
}

bool shot_move(shot_t* shot,float dt)
{
	shot->pos_x=computar_posicion(shot->pos_x,SHOT_SPEED*cos(shot->angle),dt);
	shot->pos_y=computar_posicion(shot->pos_y,SHOT_SPEED*sin(shot->angle),dt);
	graficador_ajustar_variables(&(shot->pos_x),&(shot->pos_y));
	(shot->remaining_time)=(shot->remaining_time)-dt;
	if((shot->remaining_time)<=0)
	{
		return false;
	}
	return true;
}
