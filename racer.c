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
static int sleep_flag = 1;

void initRacers( long milliseconds ) {
	MAX_DELAY = milliseconds;
	srand( time( NULL ) );
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
	
	while ( driver->dist <= FINISH_LINE ) {
		
		int delay = ( rand() % MAX_DELAY );
		if ( delay <= 3 ) {
			driver->graphic[1] = 'X';
			pthread_mutex_lock( &mutex );
			set_cur_pos( driver->row, 0 );
			int j = 0;
			while ( j < driver->dist ) {
				put( ' ' );
				j++;
			}
			printf( "%s", driver->graphic );
			pthread_mutex_unlock( &mutex );
			break;
		}
		usleep( delay * 1000 );

		pthread_mutex_lock( &mutex );
		set_cur_pos( driver->row, 0 );
		int i = 0;
		while ( i < driver->dist ) {
			put( ' ' );
			i++;
		}
		printf( "%s", driver->graphic );
		pthread_mutex_unlock( &mutex );	
	
		driver->dist++;
	}
	//destroyRacer( racer );
	return;
}
