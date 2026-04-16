#ifndef _LISTS_H_
#define _LISTS_H_

#include <stdbool.h>

typedef struct node_s node_t;
typedef struct list_s list_t;
typedef struct iterator_s iterator_t;

typedef void (*destroy_data)(void* data);

list_t* list_create();
void list_destroy(list_t* l,destroy_data destroyer);
bool list_is_empty(const list_t* l);
bool list_insert_at_ending(list_t* l, void* d);
bool list_insert_at_beginning(list_t* l, void* d);

iterator_t* iterator_create(list_t* l);
void iterator_destroy(iterator_t* il);
bool iterator_finished(const iterator_t* il);
void* iterator_position(const iterator_t* l);
bool iterator_next(iterator_t* il);
void* iterator_delete_position(iterator_t* il);

#endif // _LISTS_H_
