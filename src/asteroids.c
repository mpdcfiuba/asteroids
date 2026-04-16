#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "asteroids.h"
#include "graficador.h"
#include "draw.h"
#include "computar.h"

const char *rocks[] = {"ROCK1", "ROCK2", "ROCK3", "ROCK4"};

struct asteroid_s
{
	float pos_x;
	float pos_y;
	float vel_x;
	float vel_y;
	float angle;
	int radius;
	int class;
};

asteroid_t* asteroid_create(float pos_x,float pos_y,int radius)
{
	asteroid_t* asteroid = malloc(sizeof(asteroid_t));
	if(!asteroid)
		return NULL;
	asteroid_set_parameters(asteroid,pos_x,pos_y,radius);
	return asteroid;
}

void asteroid_destroy(asteroid_t* asteroid)
{
	free (asteroid);
}

void asteroid_set_parameters(asteroid_t* asteroid,float x_new,float y_new,int radius)
{
	asteroid->radius = radius;
	asteroid->angle = (rand()%100)/15.76;
	asteroid->pos_x = x_new;
	asteroid->pos_y = y_new;
	float vel_module = (1000/(radius))-100+(rand()%200);
	asteroid->vel_x = vel_module*cos(asteroid->angle);
	asteroid->vel_y = vel_module*sin(asteroid->angle);
	asteroid->class = rand()%4;
}

float asteroid_get_pos_x(const asteroid_t* asteroid)
{
	return asteroid->pos_x;
}

float asteroid_get_pos_y(const asteroid_t* asteroid)
{
	return asteroid->pos_y;
}

int asteroid_get_radius(const asteroid_t* asteroid)
{
	return asteroid->radius;
}

bool asteroid_draw(const asteroid_t* asteroid)
{
	return graficador_dibujar(rocks[asteroid->class],SCALE_FACTOR*(asteroid->radius),asteroid->pos_x,asteroid->pos_y,asteroid->angle);
}

void asteroid_move(asteroid_t* asteroid,float dt)
{
	asteroid->pos_x=computar_posicion(asteroid->pos_x,asteroid->vel_x,dt);
	asteroid->pos_y=computar_posicion(asteroid->pos_y,asteroid->vel_y,dt);
	
	graficador_ajustar_variables(&(asteroid->pos_x),&(asteroid->pos_y));
}

bool asteroid_collided(const asteroid_t* asteroid,float pos_x,float pos_y)
{
	float x_coord = (asteroid->pos_x)-pos_x;
	x_coord=x_coord*x_coord;
	float y_coord = (asteroid->pos_y)-pos_y;
	y_coord=y_coord*y_coord;
	float hypoth = sqrt(x_coord+y_coord);
	if(hypoth>(asteroid->radius))
		return false;
	return true;
}
