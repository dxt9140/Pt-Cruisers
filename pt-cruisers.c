/// pt-cruisers.c
/// Author: Dominick Taylor (dxt9140@g.rit.edu)
/// Created: 12/5/2016
/// The main function for running a race between Racer objects found in racer.c. The program also uses display.c to display the events of the race.

#define _BSD_SOURSE
#include <stdlib.h>
#include <stdio.h>
#include "racer.h"
#include "display.h"


int main ( int argc, char * argv[] ) {

	if ( argc < 2 ) {
		fprintf( stderror, "ERROR" );
		return EXIT_FAILURE;
	}

}
