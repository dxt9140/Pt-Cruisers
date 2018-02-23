/// racer.c
/// Author: Dominick Taylor (dxt9140@g.rit.edu)
/// Created: 12/5/2016
/// Implementation of the racer.h file. This program will handle the construction of the racers.

#define _BSD_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "racer.h"
#include "display.h"

static long MAX_DELAY;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void initRacers( long milliseconds ) {
	MAX_DELAY = milliseconds;
	srand( time( NULL ) );
}

Racer * makeRacer( char * name, int position ) {
	Racer * racer = malloc( sizeof( Racer ) );

	char * buff;
	buff = malloc( MAX_CAR_LEN+1 );
	buff[ MAX_CAR_LEN ] = '\0';
	buff[0] = '~';
	buff[1] = 'O';
	buff[2] = '=';
	strncpy( buff+3, name, MAX_NAME_LEN+1 );
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
	
	while ( driver->dist <= FINISH_LINE ) {
		pthread_mutex_lock( &mutex );
		set_cur_pos( driver->row, 0 );
		int i = 0;
		while ( i < driver->dist ) {
			put( ' ' );
			i++;
		}
		for ( size_t i = 0; i < MAX_CAR_LEN; i++ ) {
			put( driver->graphic[i] );
		}
		pthread_mutex_unlock( &mutex );	

		if ( driver->graphic[1] == 'X' ) break;
	
		driver->dist++;
		int delay = ( rand() % MAX_DELAY );
		if ( delay <= 3 ) {
			driver->graphic[1] = 'X';
		}
		usleep( delay * 1000 );
	}
	return 0;
}
