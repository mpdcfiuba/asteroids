#ifndef _SHOTS_H_
#define _SHOTS_H_

#include "ship.h"

typedef struct shot_s shot_t;

shot_t* shot_create(const ship_t* the_ship);
void shot_destroy(shot_t* shot);
void shot_set_parameters(shot_t* shot,const ship_t* the_ship);

float shot_get_pos_x(const shot_t* shot);
float shot_get_pos_y(const shot_t* shot);

bool shot_draw(const shot_t* shot);
bool shot_move(shot_t* shot,float dt);

#endif // _SHOTS_H_
