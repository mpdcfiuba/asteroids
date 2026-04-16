#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <stdlib.h>

typedef const int (*character_t)[2];

typedef struct
{
	character_t character;
	const char ascii;
	size_t size;
}
dictionary_t;

void letter_to_func(char ascii,dictionary_t** letter);

#endif // _DICTIONARY_H_
