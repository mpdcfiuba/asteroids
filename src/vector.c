#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"
#include "config.h"

void vector_rotate(float **v,size_t n,double rad)
{
	double crad=cos(rad);
	double srad=sin(rad);

	for (size_t i=0;i<n;i++)
	{
		double prevx=v[i][0];
		double prevy=v[i][1];

		v[i][0]=prevx*crad-prevy*srad;
		v[i][1]=prevx*srad+prevy*crad;
	}
}

float** vector_create(size_t n)
{
	float** v;
	if(!(v=(malloc(sizeof(float *)*n))))
	{
		return NULL;
	}
	
	for (size_t i=0;i<n;i++)
	{
		if(!(v[i] =((float *)malloc(sizeof(float)*2))))
		{
			vector_destroy(v,i);
			return NULL;
		}
	}
	return v;
}

void vector_const_copy(float (*om)[2],float** nm,size_t n)
{
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<2;j++)
		{
			nm[i][j] = om[i][j];
		}
	}
}

static void vector_copy(const float** om,float** nm,size_t n)
{
	for (size_t i=0;i<n;i++)
	{
		for (size_t j=0;j<2;j++)
		{
			nm[i][j] = om[i][j];
		}
	}
}

float** vector_create_n_copy(const float** m, size_t n)
{
	float** v;
	v = vector_create(n);
	if(!v)
	{
		return NULL;
	}
	vector_copy(m,v,n);
	return v;
}

void vector_destroy(float** v,size_t n)
{
	for (size_t i=0;i<n;i++)
	{
		free (v[i]);
	}
	free (v);
}
