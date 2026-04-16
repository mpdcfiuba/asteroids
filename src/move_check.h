#ifndef _MOVE_CHECK_H_
#define _MOVE_CHECK_H_

void move_shots_list(list_t* shots_list);
void check_shot_collition(list_t* shots_list,asteroid_t* asteroid,list_t* asteroids_list,iterator_t* asteroids_iterator,unsigned int* score);

bool check_ship_collition(ship_t* the_ship,void* asteroid_rec,list_t* asteroids_list,iterator_t* asteroids_iterator,float* last_angle,bool* spawn,int* wait_time,bool* starting_level,unsigned int* score);

void check_asteroids_quantity(list_t* asteroids_list,size_t* streak);
bool move_asteroids_check_collition(ship_t* the_ship,list_t* shots_list,list_t* asteroids_list,float* last_angle,int* wait_time,bool* starting_level,unsigned int* score,float dt);

#endif // _MOVE_CHECK_H_
