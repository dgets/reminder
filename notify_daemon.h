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


