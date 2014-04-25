#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define SHORTMAX        40
#define FULLMAX         255
#ifndef CL_OPTS
# define CL_OPTS        1
#endif
#define DEBUGGING	true
/*  
 * Constants (are these only bogus in C++, or should I
 * be staying away from these in standard C, as well?)
 */
const char	EventFilename	=	".remevents";

/*  Data Structures  */
typedef struct chowFormation {
        char    severity;
        char    title[SHORTMAX];
        char    msg[FULLMAX];
        time_t  bz;
} ChowFormation;
const size_t	RecSize		=	sizeof(ChowFormation);

/*  Mutlipurpose Functions  */
void *read_events(void) {
	void	*miscPtr, *bufPtr;
	char	sBuf[RecSize], recCount = FULLMAX;
				/* event limitation */

	if (fstat(EventFilename, miscPtr) >= 0) 
		if ((miscPtr = fopen(EventFilename, "r")) == NULL)
			return NULL;

	bufPtr = malloc(RecSize * FULLMAX);	/* add error checking */
	while (((fread(sBuf, RecSize, 1, miscPtr) > 0)) 
	       & (recCount < FULLMAX)) {
		(void) memcpy(bufPtr[(RecSize * recCount++)],
				miscPtr, RecSize);
		(void) realloc(bufPtr, recCount); /* here, too */
		strcpy(bufPtr->title, "End of Buffer");
	}

	return (void *) bufPtr;
}

int event_editor(void *evnts, bool *fs) {
	int eventCount	=	0;

	if ((evnts = read_events()) == NULL) {
		if (DEBUGGING) {
			printf("Error encountered in ");
			printf("read_events()\n\n");
			return -1;
		}
		/* other error handling code */
	}

	while (strcmp(evnts->title, "End of Buffer") != 0) {
		
