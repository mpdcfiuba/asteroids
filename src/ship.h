#ifndef _SHIP_H_
#define _SHIP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct ship_s ship_t;

ship_t* ship_create(float last_angle);
void ship_destroy(ship_t* the_ship);

void ship_apply_impulse(ship_t* the_ship);
void ship_rotate_right(ship_t* the_ship);
void ship_rotate_left(ship_t* the_ship);
void ship_restart_parameters(ship_t* the_ship,float last_angle);

bool ship_draw(const ship_t* the_ship);
void ship_move(ship_t* the_ship,float dt);

float ship_get_pos_x(const ship_t* the_ship);
float ship_get_pos_y(const ship_t* the_ship);
double ship_get_angle(const ship_t* the_ship);

#endif // _SHIP_H_
