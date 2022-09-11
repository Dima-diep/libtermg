#pragma once
#include <ncurses.h>
#include <vector>
#include <string>
#include "sigign.h"

void nc_title(const std::string text, const std::string stitle="") {
    noecho();
    curs_set(0);
    signal(SIGWINCH, sigign);
    unsigned int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    const unsigned int titlex = (text.length() + 4) / 2 - stitle.length() / 2;
	WINDOW * win = newwin(4, text.length() + 4, maxy / 2 - 2, maxx / 2 - (text.length() + 4) / 2);
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
	getch();
	delwin(win);
	refresh();
}

void nc_title(std::vector<std::string> text, const std::string stitle="") {
    noecho();
    curs_set(0);
    signal(SIGWINCH, sigign);
    unsigned int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    static unsigned int maxlen = 0;
    for (unsigned int k=0; k < text.size(); k++) {
    	if (text[k].length() > maxlen) {
    		maxlen = text[k].length();
    	}
    }
    maxlen += 4;
    const unsigned int titlex = (maxlen + 4) / 2 - stitle.length() / 2;
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
	getch();
	delwin(win);
	refresh();
}
