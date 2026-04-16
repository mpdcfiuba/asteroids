#include "computar.h"

double computar_posicion(double pi,double vi,double dt)
{
	return vi*dt+pi;
}

double computar_velocidad(double vi,double a,double dt)
{
	return ((a*dt+vi)*0.99)*(dt/0.01);
}

double computar_potencia(double pot_inicial,double dt)
{
	if(pot_inicial<1)
		return pot_inicial=0;
	return (pot_inicial*0.9)*(dt/0.01);
}
