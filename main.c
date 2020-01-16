#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <readline/readline.h>

#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;

char *choices[] = { 
	"Choice 1",
	"Choice 2",
	"Choice 3",
	"Choice 4",
	"Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
void exit_shell(int);


int main()
{
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c, x, y;
	wchar_t wchar = 195 + 168 - 131;
	//wchar_t wchar = 233;
	
	char str[80];
	wint_t *wch;
	char *line= NULL;
	line = readline("test ");
	
	/*setlocale(LC_ALL, "");
	filter();
	initscr();
	//clear();
	noecho();
	//cbreak();	// Line buffering disabled. pass on everything
	raw();	// Line buffering disabled. pass on everything
	// nonl();
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	//menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	//keypad(menu_win, TRUE);
	keypad(stdscr, TRUE);
	//mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	//refresh();
	//print_menu(menu_win, highlight);
	printw("%lc\n", wchar);
	wchar = 0;

	while((c = getch()) != 3)
	{
		//getstr(str);
		//printw("%s", str);
		
		// c = get_wch(wch);
		//wscanf(L"%lc",&wchar);
		//c = wchar & 0xFFFF;
		switch(c)
		{
			case KEY_UP:
			  printw("KEY_UP\n");
			  break;
			case KEY_DOWN:
			  printw("KEY_DOWN\n");
			  break;
			case KEY_LEFT:
			  //printw("KEY_LEFT\n");
			  getyx(stdscr, y, x);
			  move(y, x - 1);
			  break;
			case KEY_RIGHT:
			  //printw("KEY_RIGHT\n");
			  getyx(stdscr, y, x);
			  move(y, x + 1);
			  break;
			case KEY_HOME:
			  printw("KEY_HOME\n");
			  break;
			case KEY_END:
			  printw("KEY_END\n");
			  break;
			case KEY_F(1):
				printw("F1\n");
				break;
			case KEY_BACKSPACE:
				printw("\b");
				break;
			case KEY_ENTER:
				printw("\n");
				break;
			case '\n':
				printw("\n");
				break;
			//case 3:
			//	exit_shell(0);
			case 195:
				wchar = 195 - 131;
				printw("195 %d %d\n", c, wchar);
				break;
			default:
				if (isprint(c)) {
					//printw("%c %d", c, c);
					printw("%c", c);
					wchar = 0;
				}
				else {
					//printw("default %d %d\n", c, wchar);
					if(wchar != 0) {
						wchar += c;
						printw("%lc", wchar);
						wchar = 0;
					} else {
						printw("%d %s - %s (ASCII control character)\n",
							//unctrl(UChar(c)));
							c, unctrl(c), keyname(c));
					}
				}

				refresh();
				break;
		}
		// print_menu(menu_win, highlight);
		// if(choice != 0)	// User did a choice come out of the infinite loop
		//	break;
	}	
	//mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	exit_shell(0);*/
	return 0;
}

void exit_shell(int code) {
	clrtoeol();
	refresh();
	endwin();
	printf("Exit.\n");
	exit(code);
}


void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
