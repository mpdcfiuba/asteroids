#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>

void vector_rotate(float **v,size_t n,double rad);
float** vector_create(size_t n);
void vector_destroy(float** v,size_t n);
float** vector_create_n_copy(const float** m, size_t n);
void vector_const_copy(float (*om)[2],float** nm,size_t n);

#endif // _VECTOR_H_
