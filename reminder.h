#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define SHORTMAX        40
#define FULLMAX         255
#define EOR		"End of Records"
#ifndef CL_OPTS
# define CL_OPTS        1
#endif
#define DEBUGGING	true
/* #define CMDLINEFLAGS	"flag_table" */

/*  Data Structures  */
typedef struct chowFormation {
        char    severity;
        char    title[SHORTMAX];
        char    msg[FULLMAX];
        time_t  bz;
} ChowFormation;

/*  
 * Constants (are these only bogus in C++, or should I
 * be staying away from these in standard C, as well?)
 */
const char *	EventFilename	=	".remevents";
const size_t	RecSize		=	sizeof(ChowFormation);

/*  Mutlipurpose Functions  */
/*
void *read_events(void) {
	void	*miscPtr, *bufPtr;
	char	sBuf[RecSize], recCount = FULLMAX; */
				/* event limitation */

	/* if (fstat(EventFilename, miscPtr) >= 0) 
		if ((miscPtr = fopen(EventFilename, "r")) == NULL)
			return NULL; 

	bufPtr = malloc(RecSize * FULLMAX); */	/* add error checking */
	/* while (((fread(sBuf, RecSize, 1, miscPtr) > 0)) 
	       & (recCount < FULLMAX)) {
		(void) memcpy(bufPtr[(RecSize * recCount++)],
				miscPtr, RecSize);
		(void) realloc(bufPtr, recCount); */ /* here, too */
		/* strcpy(bufPtr->title, EOR);
	}

	return (void *) bufPtr;
}
*/

void *read_events(void *evnts) {
        FILE    *dfile;
        void    *buf;
        int     cntr = 0;
        size_t  chowSize;

        ChowFormation   tmp;

        /* chowSize = sizeof(ChowFormation); durrr already in RecSize */
        buf = malloc(RecSize);
        strcpy(tmp.title, EOR);

        if ((dfile = fopen(DOTFILE, "r")) == NULL) {
                /* need to create? */
                if ((dfile = fopen(DOTFILE, "w")) == NULL) {
                        return NULL;
                } else {
                        err(1, "Unable to open config file for writing!");
                }
        } else {
                while (fread(&tmp, RecSize, 1, dfile) != 0) {
                        memcpy(buf, &tmp, RecSize);

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

