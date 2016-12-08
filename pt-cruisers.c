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

	int lane = 1;
	long delay = strtol( argv[1], NULL, 10 );
	int num_racers;

	Racer * racer_list[ argc ];
	int racer_id = 0;		

	if ( delay != 0 ) {
		initRacers( delay );
		num_racers = argc - 2;
		lane++;
	} else {
		num_racers = argc - 1;
		char * name = malloc( MAX_NAME_LEN );
		strncpy( name, argv[1], MAX_NAME_LEN );
				
		if ( strlen( name ) > MAX_NAME_LEN ) {
			fprintf( stderr, "ERROR: name must not exceed %d characters...\n", MAX_NAME_LEN );
			return EXIT_FAILURE;
		}
		initRacers( DEFAULT_WAIT );
		Racer * racer = makeRacer( name, lane );
		lane++;

		free( name );
		racer_list[racer_id] = racer;
		racer_id++;
	}

	for ( int i = 2; i < argc; i++ ) {		

		char * name = malloc( MAX_NAME_LEN );
		strncpy( name, argv[i], MAX_NAME_LEN );

		if ( strlen( name ) > MAX_NAME_LEN ) {
			fprintf( stderr, "ERROR: name must not exceed %d characters...\n", MAX_NAME_LEN );
			return EXIT_FAILURE;
		}
		Racer * racer = makeRacer( name, lane );
		lane++;

		free( name );
		racer_list[racer_id] = racer;
		racer_id++;
	}

	clear();

	if ( num_racers < 2 ) {
		fprintf( stderr, "ERROR: Race must contain at least 2 cars!\n" );
		return EXIT_FAILURE;
	}
	
	pthread_t thread_list[num_racers];

	for ( int racer_id = 0; racer_id < num_racers; racer_id++ ) {
		Racer * driver = racer_list[racer_id];
		if ( driver != NULL ) {
			pthread_t thread;
			pthread_create( &thread, NULL, run, driver );
			thread_list[racer_id] = thread;
		}
	}

	for ( int thid = 0; thid < num_racers; thid++ ) {
		pthread_join( thread_list[thid], NULL );
	}

	for ( int i = 0; i < num_racers; i++ ) {
		clear();
		if ( racer_list[i] != NULL ) { 
			destroyRacer( racer_list[i] );
		}
	}


	set_cur_pos( num_racers, 0 );
	printf( "\n\n\n" );
}
