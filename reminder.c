/*
 * DON'T FUCKING FORGET SHIT
 *
 * by: Damon Getsman
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "my-ncurses.h"
#include "my-general.h"

#define SHORTMAX	40 
#define FULLMAX		255
#ifndef CL_OPTS
# define CL_OPTS        1
#endif
#define DOTFILE         ".reminderrc"


/*  Data Structures  */
typedef struct chowFormation {
	char	severity;
	char	title[SHORTMAX];
	char	msg[FULLMAX];
	time_t	bz;
} ChowFormation;

/*  External Functions (prototypes)  */
extern int *pcline(int ac, char *opts);
extern int editor(void *events, bool *fullscreen);
/* extern void *read_events(void *events); */
extern bool init_ncurses(void);

void *read_events(void *evnts) {
	FILE    *dfile;
	void    *buf;
	ChowFormation   tmp;
	
	buf = malloc(sizeo
	if ((dfile = fopen(DOTFILE, "r")) == NULL) {
		/* need to create? */
		if ((dfile = fopen(DOTFILE, "w")) == NULL) {
			return NULL;
		}
		while (fread(buf, sizeof(ChowFormation), 1, dfile) != 0) {
			

int main(int argc, char *argv) {
	void	*options, *events;
	bool	fullscr = false;
	int	tmp;

	/* parse command line here */
	options = pcline(argc, argv);
	if (options == NULL) {	/* oopthspthspthsie! */
		prinf("\nUnable to allocate memory!\n");
		return 1;
	}
	if ((bool)*options) {	/* we're editing */
		fullscr = init_ncurses();
		tmp = editor(events, fullscr);
		
	}
}

