#include <ncurses.h>
#include <string.h>
#include <thread>

// Variables
bool running = true;

/*
 * HelloWorld function for Ncurses. Accepts the users name and replies. 
 *
 * @author IWriteThings 
 * @date
 */
void sayHello() {
	char playerName[25];
	printw( "What is your name? " );
	getnstr( playerName, 25 );
	printw( "Hello there " );
	addstr( playerName );
	printw( "." );
}

/*
 * Manages the inputs from the user. This is where actions happen.
 *
 * @author IWriteThings
 * @date
 */
void menu_input_management() {
	int choice;
	choice = getch();
	switch( choice ) {
		case KEY_F( 1 ):
			addstr( "I pressed F1!" );
			refresh();
			break;
		case KEY_F( 2 ):
			running = false;
			addstr( "You have ended the game." );
			refresh();
			break;
		case KEY_F( 3 ):
			echo();
			curs_set( 1 );
			sayHello();
			curs_set( 0 );
			break;
		case '2':
			addstr( "Not Yet Implemented!" );
			break;
		default:
			addstr( "Please select from the list!" );
			refresh();
			break;
	} 
}

/*
 * Creates the soft labels and manages their inputs at the bottom of the window.
 *
 * @author IWriteThings
 * @date
 */
void displaySoftLabels() {
	clear();
	noecho();
	slk_restore();
	slk_set( 1,	"F1:Help",	0 );
	slk_set( 2,	"F2:Quit",	0 );
	slk_set( 3,	"F3:Print",	0 );
	slk_set( 4,	"F4:Text",	1 );
	slk_set( 5,	"F5:Edit",	1 );
	slk_set( 6,	"F6:Quick",	2 );
	slk_set( 7,	"F7:Conf",	2 );
	slk_set( 8,	"F8:Pups",	2 );
	slk_refresh();
	menu_input_management();
	getch();
	slk_clear();
}


/*
 * A function designed to accept text and a row in order to center the text.
 *
 * @author IWriteThings
 * @date
 */
void center(int row, char* title) {
	int len, indent, y, width;
	getmaxyx( stdscr, y, width);
	len = strlen( title );
	indent = width - len;
	indent /= 2;
	mvaddstr( row, indent, title );
	refresh();
}

/*
 * Display a title.
 *
 * @author IWriteThings
 * @date
 */
void display_title() {
	int y, x;
	getmaxyx( stdscr, y, x );
	center( ( y / 2 ), "This is a title test!" );
	center( ( y / 2 + 1 ), "Press any key to continue." );
	getch();
}

/*
 * The main Application.
 *
 * @author IWriteThings
 * @date
 */
int main() {
	// Enable and allow softkeys. Must come before initscr.
	slk_init( 0 );
	// Initialize the screen.
	initscr();
	// Flip off the cursor.
	curs_set( 0 );
	// Display a title string.
	display_title();
	// Allow keypad input.
	keypad( stdscr, TRUE );
	// Run the game.
	while( running ) { displaySoftLabels(); }
	// Free the window. This kills the application.
	endwin();
	// Return 0 because we are done.
	return 0;
}
