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
#include <err.h>

#include "my-ncurses.h"
#include "my-general.h"

#include "event_edit.h"
#include "notify_daemon.h"

#define SHORTMAX	40 
#define FULLMAX		255
#ifndef CL_OPTS
# define CL_OPTS        1
#endif
#define DOTFILE         ".reminderrc"

/*  External Functions (prototypes)  */
extern int *pcline(int ac, char *opts);
extern int event_editor(void *events, bool *fullscreen);
/* extern void *read_events(void *events); */
extern void list_events(void *events);
extern void add_events(void *events);
extern void del_events(void *events);
extern void ed_event(void *events);

extern int notifyd(void *events);

extern bool init_ncurses(void);

void *read_events(void *evnts) {
	FILE    *dfile;
	void    *buf;
	int	cntr = 0;
	size_t	chowSize;

	ChowFormation   tmp;

	chowSize = sizeof(ChowFormation);	
	buf = malloc(chowSize);
	strcpy(tmp.title, EOR);

	if ((dfile = fopen(DOTFILE, "r")) == NULL) {
		/* need to create? */
		if ((dfile = fopen(DOTFILE, "w")) == NULL) {
			return NULL;
		} else {
			err(1, "Unable to open config file for writing!");
		}
	} else {
		while (fread(&tmp, chowSize, 1, dfile) != 0) {
			memcpy(buf, &tmp, chowSize);

			realloc(buf, (++cntr * chowSize));
			tmp.severity = '\0';
			strcpy(tmp.title, "\0");
			strcpy(tmp.msg, "\0");	
		}			
		fclose(dfile);
	}
	#ifdef DEBUGGING
		warn("\n\nFell through the bottom of read_events();");
		warn("\nWTF-f-f :-?(beep)\n");
	#endif
}

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

	if (((bool) *options) == true) {	/* we're editing */
		fullscr = init_ncurses();
		/* TODO: Implement non-fullscreen functionality */

		while ((tmp = event_editor(events, fullscr)) != 5) {
		  switch (event_editor(events, fullscr)) {
		    case 1: /* list events */
			list_events(*events);
			break;
		    case 2: /* delete event(s) */
			delete_events(*events);
			break;
		    case 3: /* add event(s) */
			add_events(*events);
			break;
		    case 4: /* edit event */
			ed_event(*events);
			break;
		    case 5: /* exit */
			return 0;
			break;
		    default:
			err("\n\nWTF?\nFell through main loop: %s\n");
		  }
		}
	
	} else if (((bool) *(options + 1)) == true) { /* fork & notify */
		if (notifyd != 0) return 2;
	}

}

