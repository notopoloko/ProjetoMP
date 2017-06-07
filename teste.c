#include <ncurses.h>

int main(){
	initscr();
	raw();
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLUE);
	attron(COLOR_PAIR(1));
	printw("AHH my eyes");
	attroff(COLOR_PAIR(1)); 
	getch();
	endwin();
	return 0;
}