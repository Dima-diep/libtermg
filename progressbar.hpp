#pragma once
#include <ncurses.h>
#include <string>
#include <signal.h>
#include "sigign.h"

void progress(const std::string title="", int& start, const int end, const unsigned int len=10) {
    signal(SIGWINCH, sigign);
    curs_set(0);
    unsigned int maxy, maxx;
    static unsigned int lenx = 0;
    getmaxyx(stdscr, maxy, maxx);
    if (title.length() < len) {
    	lenx = len;
    } else {
    	lenx = title.length();
    }
    if (lenx > maxx - 2) {
    	lenx = maxx - 2;
    }
    const unsigned int proglen = maxx - 4;
    WINDOW * win = newwin(4, lenx + 2, maxy / 2 - 2, maxx / 2 - lenx / 2 - 1);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    refresh();
    wmove(win, 0, lenx / 2 - title.length() / 2);
    waddstr(win, title.c_str());
    wrefresh(win);
    refresh();
    wmove(win, 2, 1);
    while (true) {
    	for (unsigned int k=0, k < proglen, k++) {
    		wmove(win, 2, 1 + k);
    		waddch(win, ' ');
    	}
    	unsigned int lines = proglen * (start / end);
    	for (unsigned int k=0, k < lines, k++) {
    		wmove(win, 2, 1 + k);
    		waddch(win, '=');
    	}
    	wrefresh(win);
    	refresh();
    }
    delwin(win);
}
