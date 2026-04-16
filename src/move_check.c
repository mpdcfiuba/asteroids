#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "lists.h"
#include "shots.h"
#include "config.h"
#include "asteroids.h"

static void delete_asteroid_n_add_points(asteroid_t* asteroid,list_t* asteroids_list,iterator_t* asteroids_iterator,unsigned int* score)
{
	switch(asteroid_get_radius(asteroid))
	{
		case 32:
			(*score)+=20;
		break;
		case 16:
			(*score)+=50;
		break;
		case 8:
			(*score)+=100;
		break;
	}
				
	asteroid_t* a_to_destroy = iterator_delete_position(asteroids_iterator);
	if((asteroid_get_radius(a_to_destroy))>8)
	{
		for(size_t i=0;i<2;i++)
		{
			list_insert_at_beginning(asteroids_list,asteroid_create(asteroid_get_pos_x(a_to_destroy),asteroid_get_pos_y(a_to_destroy),(asteroid_get_radius(a_to_destroy))/2));
		}
	}
	asteroid_destroy(a_to_destroy);
}

void move_shots_list(list_t* shots_list)
{
	iterator_t* shots_iterator=NULL;
	
	if(!list_is_empty(shots_list))
	{
		for(shots_iterator=iterator_create(shots_list);!iterator_finished(shots_iterator);iterator_next(shots_iterator))
		{
			shot_t* shot = iterator_position(shots_iterator);
			if(shot&&(!shot_move(shot,DT)))
			{
				shot_destroy(iterator_delete_position(shots_iterator));
				shot=NULL;
				break;
			}
			shot_draw(shot);
		}
		iterator_destroy(shots_iterator);
	}
}

void check_shot_collition(list_t* shots_list,asteroid_t* asteroid,list_t* asteroids_list,iterator_t* asteroids_iterator,unsigned int* score)
{
	iterator_t* shots_iterator=NULL;
	for(shots_iterator=iterator_create(shots_list);!iterator_finished(shots_iterator);iterator_next(shots_iterator))
	{
		shot_t* shot = iterator_position(shots_iterator);
		if(asteroid)
		{
			if(asteroid_collided(asteroid,shot_get_pos_x(shot),shot_get_pos_y(shot)))
			{
				delete_asteroid_n_add_points(asteroid,asteroids_list,asteroids_iterator,score);
								
				shot_t* s_to_destroy = iterator_delete_position(shots_iterator);
				shot_destroy(s_to_destroy);
			}
		}
	}
	iterator_destroy(shots_iterator);
}

bool check_ship_collition(ship_t* the_ship,void* asteroid_rec,list_t* asteroids_list,iterator_t* asteroids_iterator,float* last_angle,int* wait_time,bool* starting_level,unsigned int* score)
{
	asteroid_t* asteroid = asteroid_rec;
	if(asteroid_collided(asteroid,ship_get_pos_x(the_ship),ship_get_pos_y(the_ship)))
	{
		(*last_angle) = ship_get_angle(the_ship);
		ship_destroy(the_ship);
		if((*wait_time)==1)
		{
			(*wait_time)=10;
			(*starting_level)=true;
		}
		else
		{
			(*wait_time)=100;
			delete_asteroid_n_add_points(asteroid,asteroids_list,asteroids_iterator,score);
		}
		return true;
	}
	return false;
}

void check_asteroids_quantity(list_t* asteroids_list,size_t* streak)
{	
	(*streak)++;
	for(size_t i=0;i<((*streak)*2);i++)
	{
		list_insert_at_ending(asteroids_list,asteroid_create(rand(),0,32));
		list_insert_at_ending(asteroids_list,asteroid_create(0,rand(),32));
	}
}

bool move_asteroids_check_collition(ship_t* the_ship,list_t* shots_list,list_t* asteroids_list,float* last_angle,int* wait_time,bool* starting_level,unsigned int* score,float dt)
{
	iterator_t* asteroids_iterator=NULL;
	for(asteroids_iterator=iterator_create(asteroids_list);!iterator_finished(asteroids_iterator);iterator_next(asteroids_iterator))
	{
		asteroid_t* asteroid = iterator_position(asteroids_iterator);
		asteroid_move(asteroid,dt);
		asteroid_draw(asteroid);
		
		if(the_ship)
		{
			if(check_ship_collition(the_ship,asteroid,asteroids_list,asteroids_iterator,last_angle,wait_time,starting_level,score))
			{
				iterator_destroy(asteroids_iterator);
				return true;
			}
		}
		
		if(!list_is_empty(shots_list))
		{
			check_shot_collition(shots_list,asteroid,asteroids_list,asteroids_iterator,score);
		}
	}
	iterator_destroy(asteroids_iterator);
	return false;
}
