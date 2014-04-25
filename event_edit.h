/*
 * by: Damon Getsman
 * started: 25 Apr 14 07:30
 * finished:
 *
 * Functions for event menu, user choice, and event editor
 */

int get_menu_choice(void) {
	int uChoice = 0;

	uChoice = getch();

	while ((uChoice < 1) | (uChoice > 5)) {
		vbeep();	/* visual beep? is this rite? */
		mvaddstr(10, 5, "-+=*INVALID CHOICE*=+-");

		refresh();

		uChoice = mvgetch(46, 5);
	}

	return uChoice;
}

int event_menu(void) {
	int userChoice;

	nocbreak;
	clear();
	refresh();

	mvaddstr(1, 5, "Event List Menu");
	mvaddstr(2, 5, "-=-=-=-=-=-=-=-");
	mvaddstr(4, 5, "1) List Events");
	mvaddstr(5, 5, "2) Delete Event");
	mvaddstr(6, 5, "3) Add Event");
	mvaddstr(7, 5, "4) Edit Event");
	mvaddstr(8, 5, "5) Exit Program");
	mvaddstr(11, 5, "Enter your choice (1-5), forgetful one: ");

	refresh();

	if ((userChoice = get_menu_choice()) == 5) return -1 else
		return userChoice;
}


