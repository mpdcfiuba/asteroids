CC := gcc
CFLAGS := -Wall -pedantic -std=c99 -Werror -c -g -O3
LFLAGS := -lm -lSDL3

all: asteroids

lists.o: lists.c lists.h config.h
	$(CC) $(CFLAGS) lists.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) vector.c

draw.o: draw.c draw.h dictionary.h vector.h
	$(CC) $(CFLAGS) draw.c

graficador.o: graficador.c graficador.h dictionary.h vector.h config.h caracteres.h
	$(CC) $(CFLAGS) graficador.c

computar.o: computar.c computar.h
	$(CC) $(CFLAGS) computar.c

move_check.o: move_check.c move_check.h lists.h ship.h asteroids.h shots.h
	$(CC) $(CFLAGS) move_check.c

ship.o: ship.c ship.h draw.h config.h computar.h
	$(CC) $(CFLAGS) ship.c

shots.o: shots.c shots.h draw.h ship.h lists.h computar.h
	$(CC) $(CFLAGS) shots.c

asteroids.o: asteroids.c asteroids.h draw.h ship.h lists.h computar.h
	$(CC) $(CFLAGS) asteroids.c

dictionary.o: dictionary.c dictionary.h
	$(CC) $(CFLAGS) dictionary.c

caracteres.o: caracteres.c caracteres.h
	$(CC) $(CFLAGS) caracteres.c

main.o: main.c dictionary.h vector.h graficador.h config.h ship.h shots.h config.h asteroids.h lists.h  move_check.h
	$(CC) $(CFLAGS) main.c

asteroids: lists.o vector.o draw.o graficador.o computar.o move_check.o ship.o shots.o asteroids.o dictionary.o caracteres.o main.o
	$(CC) lists.o vector.o draw.o graficador.o computar.o  move_check.o ship.o shots.o asteroids.o dictionary.o caracteres.o main.o -o asteroids $(LFLAGS)

clean:
	rm *.o

valgrind: asteroids
	valgrind --leak-check=full ./asteroids
