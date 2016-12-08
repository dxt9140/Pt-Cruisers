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
		fprintf( stderr, "Usage:  pt-cruisers delay [names]\n\
	pt-cruisers [names]\n" );
		return EXIT_FAILURE;
	}

	//pthread_t selfid = pthread_self();

	int lane = 1;
	long delay = strtol( argv[1], NULL, 10 );
	int num_racers;

	Racer * racer_list[argc];

	if ( delay != 0 ) {
		initRacers( delay );
		num_racers = argc - 2;
		clear();
	} else {
		clear();
		num_racers = argc - 1;
		char * name = argv[1];
		if ( strlen( name ) >= MAX_NAME_LEN ) {
			fprintf( stderr, "ERROR: name must not exceed %d characters...\n", MAX_NAME_LEN );
			return EXIT_FAILURE;
		}
		initRacers( DEFAULT_WAIT );
		Racer * racer = makeRacer( name, lane );	
		lane++;
		racer_list[0] = racer;
	}

	for ( int i = 2; i < argc; i++ ) {
		char * name = argv[i];
		if ( strlen( name ) >= MAX_NAME_LEN ) {
			fprintf( stderr, "ERROR: name must not exceed %d characters...\n", MAX_NAME_LEN );
			return EXIT_FAILURE;
		}

		Racer * racer = makeRacer( name, lane );
		lane++;
		racer_list[i-1] = racer;
	}

	if ( num_racers < 2 ) {
		fprintf( stderr, "ERROR: Race must contain at least 2 cars!\n" );
		return EXIT_FAILURE;
	}
	
	for ( int racer = 0; racer < argc; racer++ ) {
		Racer * driver = racer_list[racer];
		if ( driver != NULL ) {
			pthread_t thread;
			pthread_create( &thread, NULL, run, driver );
			pthread_join( thread, NULL );
		}
	}
/*
	for ( int racer = 0; racer < argc; racer++ ) {
		if ( racer_list[racer] != NULL ) { 
			destroyRacer( racer_list[racer] );
		}
	}
*/
	printf( "\n\n" );
}
