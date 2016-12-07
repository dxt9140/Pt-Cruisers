/// racer.c
/// Author: Dominick Taylor (dxt9140@g.rit.edu)
/// Created: 12/5/2016
/// Implementation of the racer.h file. This program will handle the construction of the racers.

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "racer.h"
#include "display.h"

int MAX_DELAY

void initRacers( long milliseconds ) {
	MAX_DELAY = milliseconds;
}

Racer * makeRacer( char * name, int position ) {
	Racer * racer = malloc( sizeof( Racer ) );
	char * buff = malloc( MAX_CAR_LEN );
	buff[0] = '~';
	buff[1] = 'O';
	buff[2] = '=';
	strcat( buff, name );
	for ( int i = 3; i <= 9; i++ ) {
		if ( buff[i] == '\0' ) {
			buff[i] = '-';
		}
	}
	buff[10] = 'o';
	buff[11] = '>';
	racer->graphic = buff;
	racer->row = position;
	racer->dist = 0;
	return racer;
}

void destroyRacer( Racer * racer ) {
	free( racer->graphic );
	free( racer );
}

void * run( void * racer ) {
	Racer * driver = (Racer *)racer;
	printf( "%s\n", driver->graphic );
	while ( racer->dist != FINISH_LINE ) {
		int delay = rand() % MAX_DELAY;
		if ( delay <= 3 ) {
			racer->graphic[1] = 'X';
			break;
		}
		usleep( delay );
		racer->dist++;		
	}
}
