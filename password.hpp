//#pragma once
#include <ncurses.h>
#include <string>
#include <signal.h>
#include "sigign.h"

std::string passwdbox(const std::string title="", const unsigned int len=10) {
    signal(SIGWINCH, sigign);
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
    WINDOW * win = newwin(4, lenx + 2, maxy / 2 - 2, maxx / 2 - lenx / 2 - 1);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    refresh();
    wmove(win, 0, lenx / 2 - title.length() / 2);
    waddstr(win, title.c_str());
    wrefresh(win);
    refresh();
    char inp[lenx];
    wmove(win, 1, 1);
    noecho();
    curs_set(0);
    wgetstr(win, inp);
    echo();
    delwin(win);
    return inp;
}
