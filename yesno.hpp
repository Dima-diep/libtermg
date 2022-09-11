#pragma once
#include <ncurses.h>
#include <vector>
#include <string>
#include "sigign.h"

bool nc_yesno(const std::string text, const std::string stitle="") {
    noecho();
    curs_set(0);
    signal(SIGWINCH, sigign);
    unsigned int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    static bool sel = true;
    static unsigned int tx = text.length() + 4;
    if (tx < 13) {
    	tx = 13;
    }
    const unsigned int titlex = tx / 2 - stitle.length() / 2;
	WINDOW * win = newwin(6, tx, maxy / 2 - 2, maxx / 2 - (text.length() + 4) / 2);
	wrefresh(win);
	refresh();
	box(win, 0, 0);
	wrefresh(win);
	refresh();
	wmove(win, 0, titlex);
	waddstr(win, stitle.c_str());
	wrefresh(win);
	refresh();
	wmove(win, 1, 2);
	waddstr(win, text.c_str());
	wrefresh(win);
	refresh();
	wmove(win, 4, 0);
	waddstr(win, " <Yes>");
	wmove(win, 4, tx - 5);
	waddstr(win, " No ");
	wrefresh(win);
	while (true) {
      	int ch = getch();
      	if (ch == 9) {
      	     if (sel) {
      	     	wmove(win, 4, 0);
      	     	waddstr(win, "  Yes ");
      	     	wmove(win, 4, tx - 5);
      	     	waddstr(win, "<No>");
      	     	wrefresh(win);
      	     	refresh();
      	     	sel = false;
      	     } else {
      	     	wmove(win, 4, 0);
      	     	waddstr(win, " <Yes>");
      	        wmove(win, 4, tx - 5);
      	     	waddstr(win, " No ");
      	     	wrefresh(win);
      	     	refresh();
      	     	sel = true;
      	     }
        } else if (ch == 10) {
        	delwin(win);
        	refresh();
        	return sel;
        }
    }
}

bool nc_yesno(std::vector<std::string> text, const std::string stitle="") {
    noecho();
    curs_set(0);
    signal(SIGWINCH, sigign);
    static bool sel = true;
    unsigned int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    static unsigned int maxlen = 0;
    for (unsigned int k=0; k < text.size(); k++) {
    	if (text[k].length() > maxlen) {
    		maxlen = text[k].length();
    	}
    }
    maxlen += 4;
    if (maxlen < 9) {
    	maxlen = 9;
    }
    const unsigned int titlex = (maxlen + 4 / 2 - stitle.length() / 2);
	WINDOW * win = newwin(text.size() + 3, maxlen, maxy / 2 - (text.size() + 3) / 2, maxx / 2 - maxlen / 2);
	wrefresh(win);
	refresh();
	box(win, 0, 0);
	wrefresh(win);
	refresh();
	wmove(win, 0, titlex);
	waddstr(win, stitle.c_str());
	wrefresh(win);
	refresh();
	for (unsigned int k=0; k < text.size(); k++) {
		wmove(win, 1 + k, 2);
		waddstr(win, text[k].c_str());
	}
	wrefresh(win);
	refresh();
	wmove(win, text.size() + 1, 0);
	waddstr(win, " <Yes>");
	wrefresh(win);
	wmove(win, text.size() + 1, maxlen - 5);
	waddstr(win, " No ");
	while (true) {
	    int ch = getch();
	    if (ch == 9) {
	        if (sel) {
	        	wmove(win, text.size() + 2, 0);
	            waddstr(win, "  Yes ");
	            wmove(win, text.size() + 1, maxlen - 5);
	        	waddstr(win, "<No>");
	        	wrefresh(win);
	        	refresh();
	        	sel = false;
	        } else {
	        	wmove(win, text.size() + 1, 0);
	        	waddstr(win, " <Yes>");
	        	wmove(win, text.size() + 1, maxlen - 5);
	            waddstr(win, " No ");
	        	wrefresh(win);
	        	refresh();
	        	sel = true;
	        }
	    } else if (ch == 10) {
        	delwin(win);
	        refresh();
	        return sel;
	    }
	}
}
