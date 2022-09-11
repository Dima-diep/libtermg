#pragma once
#include <ncurses.h>
#include <string>
#include <vector>
#include "sigign.h"
#include <signal.h>

int selectmenu(const std::string title, const std::vector<std::string> select, const unsigned int selectp=6) {
    static unsigned int rselect = 0;
    static bool ok = true;
    signal(SIGWINCH, sigign);
    curs_set(0);
    keypad(stdscr, true);
    refresh();
    if (select.size() < 6) {
    	rselect = select.size();
    } else {
    	rselect = selectp;
    }
    unsigned int maxy, maxx;
    static unsigned int maxlen = title.length();
    getmaxyx(stdscr, maxy, maxx);
    for (unsigned int i=0; i < select.size(); i++) {
    	if (select[i].length() > maxlen) {
    		maxlen = select[i].length();
    	}
    }
    if (maxlen < 13) {
    	maxlen = 13;
    }
    const unsigned int empty = maxlen;
    maxlen += 4;
	WINDOW * win = newwin(rselect + 4, maxlen, maxy / 2 - (rselect + 4) / 2, maxx / 2 - maxlen / 2);
	keypad(win, true);
	wrefresh(win);
	refresh();
	box(win, 0, 0);
	wrefresh(win);
	refresh();
	WINDOW * wtitle = newwin(3, maxlen, maxy / 2 - (rselect + 4) / 2, maxx / 2 - maxlen / 2);
	refresh();
	box(wtitle, 0, 0);
	wrefresh(wtitle);
	refresh();
	wmove(wtitle, 1, 1);
	waddstr(wtitle, title.c_str());
	wrefresh(wtitle);
	refresh();
	WINDOW * okc = newwin(3, maxlen, maxy / 2 + (rselect + 2) / 2, maxx / 2 - maxlen / 2);
	refresh();
	box(okc, 0, 0);
	wrefresh(okc);
	refresh();
	wmove(okc, 1, 2);
	waddstr(okc, "<OK>");
	wmove(okc, 1, 8);
	waddstr(okc, " Cancel");
	wrefresh(okc);
	refresh();
	std::vector<std::string> printed;
	for (unsigned int k=0; k < rselect; k++) {
		wmove(win, 3 + k, 3);
		waddstr(win, select[k].c_str());
		printed.push_back(select[k]);
	}
	wmove(win, 3, 1);
	waddch(win, '>');
	wrefresh(win);
	refresh();
	static unsigned int cursel = 1;
	static unsigned int allsel = 1;
	while (true) {
	    wrefresh(win);
	    refresh();
		int ch = getch();
		if (ch == KEY_UP) {
		    if (allsel > 1) {
		        allsel--;
		    }
			if (cursel > 1) {
				wmove(win, 2 + cursel, 1);
				waddch(win, ' ');
				cursel--;
				wmove(win, 2 + cursel, 1);
				waddch(win, '>');
				wrefresh(win);
				refresh();
			} else if (allsel > 1) {
			    for (unsigned int k=rselect - 1; k > 0; k--) {
			    	printed[k] = printed[k - 1];
			    }
			    allsel--;
			    printed[0] = select[allsel - 1];
			    for (unsigned int k=0; k < rselect; k++) {
			    	for (unsigned int j=0; j < empty; j++) {
			    		wmove(win, 3 + k, 3 + j);
			    		waddch(win, ' ');
			    	}
			    }
			    for (unsigned int k=0; k < rselect; k++) {
			    	wmove(win, 3 + k, 3);
			    	waddstr(win, printed[k].c_str());
			    }
			    wrefresh(win);
			    refresh();
	        }
		} else if (ch == KEY_DOWN) {
		    if (allsel < select.size()) {
		        allsel++;
		    }
			if (cursel < rselect) {
				wmove(win, 2 + cursel, 1);
				waddch(win, ' ');
				cursel++;
				wmove(win, 2 + cursel, 1);
				waddch(win, '>');
				wrefresh(win);
				refresh();
			} else if (allsel < select.size()) {
			    for (unsigned int k=0; k < rselect - 1; k++) {
			    	printed[k] = printed[k+1];
			    }
			    allsel++;
			    printed[rselect - 1] = select[allsel - 1];
			    for (unsigned int k=0; k < rselect; k++) {
			    	for (unsigned int j=0; j < empty; j++) {
			    		wmove(win, 3 + k, 3 + j);
			    		waddch(win, ' ');
			    	}
			    }
			    for (unsigned int k=0; k < rselect; k++) {
			    	wmove(win, 3 + k, 3);
			    	waddstr(win, printed[k].c_str());
			    }
			    wrefresh(win);
			    refresh();
		    }
		} else if (ch == 10) {
			delwin(wtitle);
			delwin(win);
			delwin(okc);
			refresh();
			if (ok) {
		    	return allsel - 1;
		    } else {
		    	return -1;
		    }
		} else if (ch == 9) {
		    if (ok) {
		    	wmove(okc, 1, 2);
		    	waddch(okc, ' ');
		    	wmove(okc, 1, 5);
		    	waddch(okc, ' ');
		    	wmove(okc, 1, 8);
		    	waddch(okc, '<');
		    	wmove(okc, 1, 15);
		    	waddch(okc, '>');
		    	wrefresh(okc);
		    	refresh();
		    	ok = false;
		    } else {
		    	wmove(okc, 1, 2);
		    	waddch(okc, '<');
		    	wmove(okc, 1, 5);
		    	waddch(okc, '>');
		    	wmove(okc, 1, 8);
		    	waddch(okc, ' ');
		    	wmove(okc, 1, 15);
		    	waddch(okc, ' ');
		    	wrefresh(okc);
		    	refresh();
		    	ok = true;
		    }
		}
	}
}
