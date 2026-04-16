#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_



typedef struct asteroid_s asteroid_t;

asteroid_t* asteroid_create(float pos_x,float pos_y,int radius);
void asteroid_destroy(asteroid_t* asteroid);
void asteroid_set_parameters(asteroid_t* asteroid,float pos_x,float pos_y,int radius);

float asteroid_get_pos_x(const asteroid_t* asteroid);
float asteroid_get_pos_y(const asteroid_t* asteroid);
int asteroid_get_radius(const asteroid_t* asteroid);

bool asteroid_collided(const asteroid_t* asteroid,float pos_x,float pos_y);

bool asteroid_draw(const asteroid_t* asteroid);
void asteroid_move(asteroid_t* asteroid,float dt);

#endif // _ASTEROIDS_H_

