/// pt-cruisers.c
/// Author: Dominick Taylor (dxt9140@g.rit.edu)
/// Created: 12/5/2016
/// The main function for running a race between Racer objects found in racer.c. The program also uses display.c to display the events of the race.

#define _BSD_SOURSE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "racer.h"
#include "display.h"


int main ( int argc, char * argv[] ) {

	if ( argc < 2 ) {
		fprintf( stderr, "ERROR" );
		return EXIT_FAILURE;
	}

	int lane = 0;
	// Check if first argument is the max speed delay
	long delay = strtol( argv[1], NULL, 10 );
	if ( delay != 0 ) {
		// first token is an int, a time delay
		initRacers( delay );
	} else {
		// handle it as a racer
		char * name = argv[1];
		if ( strlen( name ) >= MAX_NAME_LEN ) {
			fprintf( stderr, "ERROR: name must not exceed %d characters...\n", MAX_NAME_LEN );
			return EXIT_FAILURE;
		}
		Racer * racer = makeRacer( name, lane );		
		lane++;

		pthread_t thread;
		pthread_create( &thread, NULL, run, racer );
		pthread_join( thread, NULL );
	}

	for ( int i = 2; i < argc; i++ ) {
		// Do things with each of the racers /lenny_face

		char * name = argv[i];
		if ( strlen( name ) >= MAX_NAME_LEN ) {
			fprintf( stderr, "ERROR: name must not exceed %d characters...\n", MAX_NAME_LEN );
			return EXIT_FAILURE;
		}
		
		Racer * racer = makeRacer( name, lane );
		lane++;
		
		initRacers( DEFAULT_TIME );
		pthread_t thread;
		pthread_create( &thread, NULL, run, racer );
		pthread_join( thread, NULL );	
	}
}
