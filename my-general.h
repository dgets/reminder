#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define DEBUG	true
#define CL_OPTS	10


/*
 * pcline();
 *
 * function returns a pointer to an integer value of how many
 * variables set by command-line option, or NULL if none parsed
 *
 * int ac: count of command line parameters
 * char *opts: array of command line options
 *
 * NOTE: This function requires a global level (void *) to point
 * to the array of booleans (variable-length) to hold the current
 * program's command line flag toggles.  This is currently defaulting
 * to the name 'flag_table', set in CMDLINEFLAGS in project's toplevel
 * .h file.
 */
int * pcline(int ac, char *opts) {
	void *	CMDLINEFLAGS;
	char	cntr1, cntr2 = 0;

	CMDLINEFLAGS = malloc(sizeof(bool) * CL_OPTS);
	if (CMDLINEFLAGS < 0) return NULL;	/* err */

	for (char ouah = 0; ouah < ac; ouah++) {
		if (strncmp(opts[ouah], "--", (size_t) 2) != 0) {
			/* long option */
			cntr = strlen(opts[ouah]);
			strncpy(opts[ouah], opts[ouah], cntr-1);
			switch (opts[ouah]) {
				case "help":
					printf("\nUsage:\n\n");
					printf("Under construction!\n\n");
					break;
				default:
					printf("\nHit default\n\n");
					break;
			}
		} else {
			if (strcmp(opts[ouah], "-e")) {
				/* edit reminders */
				flag_table[1] = true;
				cntr2++;
			}
		}
	}

	if (cntr2 == 0) return NULL; else return &cntr2;
}


