/*
 * by: Damon Getsman
 * 
 * started: 25 Apr 14 0826
 * finished:
 *
 * All functions/functionality for sitting around as a daemon
 * waiting for the right time to pop up a notification box
 */

void display_notice(void *eList, int ndx) {
	char 	*tit, *bod, svrty;
	time_t	alertTime;
	int	boxlx, boxry, len, hei, wrapx, wrapy, lines = 0,
		stx, sty;

	WINDOW *popup;

	tit 		= 	(ChowFormation *)eList[ndx]->title;
	bod 		= 	(ChowFormation *)eList[ndx]->msg;
	alertTime	=	(ChowFormation *)eList[ndx]->bz;
	svrty		=	(ChowFormation *)eList[ndx]->severity;

	hei 		=	(int)getmaxx();
	len		=	(int)getmaxy();

	if (len > 5) {
		wrapy = (len - 3);
		sty = (wrapy - 2);
	} else if (len > 0) {
		sty = wrapy = len;
	} else {
		sty = wrapy = -1;
		warn("Something weird returned via getmaxy()\n");
	}

	if (hei > 5) {
		wrapx = (hei - 3);
		stx = (wrapx - 2);
	} else if (hei > 0) {
		stx = wrapx = hei;
	} else {
		stx = wrapx = -1;
		warn("Something weird returned via getmaxx()\n");
	}

	if ((popup = newwin(((bod % hei) + 1), ((len % 

	
	/* 
	 * TODO:
	 * going to need wordwrapping, etc 
	 */
	
	if (strlen(bod) > (wrapx) -
}

int notifyd(void *evnts) {
	time_t	closestEventTime = 0, nextEventTime;
	int nextEventNdx = -1;

	nocbreak;

	addstr("Entering daemon mode\n");
	refresh();

	if (fork() == -1) 
		err("\nProblem fork()ing: %s\n");

	/* primary loop */
	for (int ouah = 0; 
	     strcmp(((ChowFormation *) (evnts+ouah)->title), EOR)
	     ouah++) { /* find time till the next event */
		nextEventTime = ((ChowFormation *) (evnts+ouah)->bz) -
				time(NULL);
		if ((nextEventTime <= closestEventTime) |
		    (closestEventTime == 0)) { 
			closestEventTime = nextEventTime;
			nextEventNdx = ouah;
		}
	}

	if (sleep(nextEventTime) != 0)
		err("\nProblem sleeping: %s\n");

	display_notice(evnts, nextEventNdx);

	return 0;
}


