#pragma once
#include <ncurses.h>
#include <string>
#include <signal.h>
#include "sigign.h"

struct reg {
	std::string login, password;
};

reg loginbox(const std::string title="", const unsigned int len=10) {
    reg retreg;
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
    WINDOW * win = newwin(6, lenx + 2, maxy / 2 - 3, maxx / 2 - lenx / 2 - 1);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    refresh();
    wmove(win, 0, lenx / 2 - title.length() / 2);
    waddstr(win, title.c_str());
    wrefresh(win);
    refresh();
    char loginp[lenx];
    char pasinp[lenx];
    wmove(win, 1, 1);
    waddstr(win, "Login: ");
    wmove(win, 3, 1);
    waddstr(win, "Password: ");
    wrefresh(win);
    refresh();
    wmove(win, 1, 8);
    curs_set(0);
    wgetstr(win, loginp);
    wmove(win, 3, 11);
    noecho();
    wgetstr(win, pasinp);
    echo();
    delwin(win);
    retreg.login = loginp;
    retreg.password = pasinp;
    return retreg;
}
