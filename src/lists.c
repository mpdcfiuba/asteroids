#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "lists.h"

struct node_s
{
	void* data;
	struct node_s* next;
};

struct list_s
{
	node_t* first;
};

struct iterator_s
{
	list_t* iterated_list;
	node_t* prev;
	node_t* actual;
};

list_t* list_create()
{
	list_t* l = malloc(sizeof(list_t));
	if(!l)
		return NULL;

	l->first = NULL;
	return l;
}

void list_destroy(list_t* l,destroy_data destroyer)
{
	node_t* node_aux = l->first;
	while(node_aux) {
		node_t* node_next = node_aux->next;

		if(destroyer)
			destroyer(node_aux->data);

		free(node_aux);

		node_aux = node_next;
	}

	free(l);
}

bool list_is_empty(const list_t* l)
{
	return (l->first)==NULL;
}

static node_t* node_create(void* d)
{
	node_t* node_new = malloc(sizeof(node_t));
	if(!node_new)
		return NULL;

	node_new->data = d;
	node_new->next = NULL;

	return node_new;
}

bool list_insert_at_ending(list_t* l, void* d)
{
	node_t* node_new = node_create(d);
	if(!node_new)
		return false;

	if(!(l->first))
	{
		l->first = node_new;
		return true;
	}

	node_t* node_aux = l->first;
	while(node_aux->next)
		node_aux = node_aux->next;

	node_aux->next = node_new;

	return true;
}

bool list_insert_at_beginning(list_t* l, void* d)
{
	node_t* node_new = node_create(d);
	if(!node_new)
		return false;

	node_new->next = l->first;
	l->first = node_new;

	return true;
}

iterator_t* iterator_create(list_t* l)
{
	iterator_t* il_new = malloc(sizeof(iterator_t));
	if(!il_new)
		return NULL;

	(il_new->prev)=NULL;
	(il_new->actual)=(l->first);

	il_new->iterated_list = l;


	return il_new;
}

void iterator_destroy(iterator_t* il)
{
	free (il);
}

void* iterator_position(const iterator_t* il)
{
	if(iterator_finished(il))
		return NULL;

	return (il->actual->data);
}

bool iterator_finished(const iterator_t* il)
{
	return ((il->actual)==NULL);
}

bool iterator_next(iterator_t* il)
{
	if(iterator_finished(il))
		return false;

	node_t* node_aux = il->actual;
	(il->prev)=node_aux;
	(il->actual)=node_aux->next;
	return true;
}

void* iterator_delete_position(iterator_t* il)
{
	if(!(il->actual))
		return NULL;

	void* aux = il->actual->data;

	node_t* node_aux = il->actual->next;
	if((il->iterated_list->first)==(il->actual))
	{
		(il->iterated_list->first) = (il->actual->next);
		il->prev = NULL;
	}
	free(il->actual);
	il->actual=node_aux;

	//There is previous
	if(il->prev)
	{
		(il->prev->next) = (il->actual);
		return aux;
	}

	//There isnt previous. Maybe the list has shomething before (someone added to the list after creating iterator). It has to be iterated
	if(il->iterated_list->first!=NULL)
	{
		iterator_t* aux_iterator=NULL;

		for(aux_iterator = iterator_create(il->iterated_list);!iterator_finished(aux_iterator);iterator_next(aux_iterator))
		{
			if(((aux_iterator->actual)==(il->actual))&&(aux_iterator->prev))
				aux_iterator->prev->next = il->actual;
			break;
		}
		iterator_destroy(aux_iterator);
		aux_iterator=NULL;
		return aux;
	}

	il->iterated_list->first = il->actual;
	return aux;
}
