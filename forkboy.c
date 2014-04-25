/*
 * jackalope.c
 *
 * That's just what I'm gonna call it.  Y'all can kiss my ass.
 */


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "my-ncurses.h"

#define DEBUGGING
#define RCFN	jackalope

#define NO_PAUSE	true

const int TextBoxLimit	78*5+1;	/* 5 lines is good, rite? */

struct Bone {
	time_t	tut;
	char	flags;
	char	*notice, *notes;
};

/*
 * parseCommandLine();
 *
 * It, ereh, takes apart the command line piece by piece and checks
 * to see if it matches any of our happy option strings
 */

int parseCommandLine(int c, char *rubbish) {
	/*
	 * Let's get down to parsing that command line, shall
	 * we?  God ouah ouah ouah
	 */
	if (ac == 0) return 0;

	switch (ac) {
		case 1:		
			if strcmp(av, "-h") {
				printf("\n\nThis is your pretty l");
				printf("ittle jackalope trying to");
				printf(" follow orders and shit :)\n\n");

				return 0;
				break;
			} else {
				printf("Straight up no idea :-?\n");
			}
		default:	
			printf("Bugger off.\n\n");
			return 1;
			break;
	}	

	/* this should be an oopthsieoopths */
	return 2;
}

int main(int argc, char *argv) {
	/*
	 *
	 * My reminder program.  I've been wanting to write this since
	 * I was what, 15?  God ouah.  :'D  Gotta love the wild wild
	 * west!
	 *
	 */

	int	tmp;

	if (parseCommandLine(argc, argv)) 
		printf("\nOoopthieoopthieoopths!\n");
		return 1;
	else {
		init_ncurses(NO_PAUSE);

