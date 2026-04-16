#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ship.h"
#include "graficador.h"
#include "draw.h"
#include "computar.h"
#include "config.h"

struct ship_s
{
	float pos_x;
	float pos_y;
	double angle;
	float vel_x;
	float vel_y;
	float power;
};

ship_t* ship_create(float last_angle)
{
	ship_t* the_ship=malloc(sizeof(ship_t));
	if(!the_ship)
		return NULL;
	
	(the_ship->pos_x)=NAVE_X_INICIAL;
	(the_ship->pos_y)=NAVE_Y_INICIAL;
	(the_ship->angle)=last_angle;
	(the_ship->vel_x)=NAVE_VX_INICIAL;
	(the_ship->vel_y)=NAVE_VY_INICIAL;
	(the_ship->power)=NAVE_POTENCIA_INICIAL;
	
	return the_ship;
}

void ship_destroy(ship_t* the_ship)
{
	free(the_ship);
}

bool ship_draw(const ship_t *the_ship)
{
	bool th_check=true;
	bool ship_check;
	
	if((the_ship->power)!=0)
			th_check = graficador_dibujar("THURST",SCALE_FACTOR,the_ship->pos_x,the_ship->pos_y,the_ship->angle);
	
	ship_check = graficador_dibujar("SHIP",SCALE_FACTOR,the_ship->pos_x,the_ship->pos_y,the_ship->angle);
	
	return (th_check&&ship_check);
}

void ship_apply_impulse(ship_t* the_ship)
{
	(the_ship->power)+=1000;
}

void ship_move(ship_t* the_ship,float dt)
{
	the_ship->power=computar_potencia(the_ship->power,dt);
	(the_ship->vel_x)=computar_velocidad((the_ship->vel_x),(the_ship->power)*cos(the_ship->angle),dt);
	(the_ship->vel_y)=computar_velocidad((the_ship->vel_y),((the_ship->power)*sin(the_ship->angle)),dt);
	
	(the_ship->pos_x)=computar_posicion((the_ship->pos_x),(the_ship->vel_x),dt);
	(the_ship->pos_y)=computar_posicion((the_ship->pos_y),(the_ship->vel_y),dt);
	
	graficador_ajustar_variables(&(the_ship->pos_x),&(the_ship->pos_y));
}

void ship_rotate_right(ship_t* the_ship)
{
	(the_ship->angle)-=NAVE_ROTACION_PASO;
}

void ship_rotate_left(ship_t* the_ship)
{
	(the_ship->angle)+=NAVE_ROTACION_PASO;
}

float ship_get_pos_x(const ship_t* the_ship)
{
	return the_ship->pos_x;
}

float ship_get_pos_y(const ship_t* the_ship)
{
	return the_ship->pos_y;
}

double ship_get_angle(const ship_t* the_ship)
{
	return the_ship->angle;
}
