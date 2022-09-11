#pragma once
#include <stdio.h>
#include <map>
#include <string>
#include <wchar.h>

std::map<unsigned int, std::string> getbraille() {
	std::map<unsigned int, std::string> mp;
	for (unsigned int k=0; k < 257; k++) {
	    wchar_t sym = 0x2800 + k;
	    char *str = 0;
	    asprintf(&str, "%lc", sym);
	    mp.insert(std::make_pair(k, str));
	}
	return mp;
}

std::map<unsigned int, std::string> getlns() {
	std::map<unsigned int, std::string> mp;
	for (unsigned int s=0; s < 128; s++) {
		wchar_t sym = 0x2500 + s;
		char *str = 0;
		asprintf(&str, "%lc", sym);
		mp.insert(std::make_pair(s, str));
	}
	return mp;
}

std::map<unsigned int, std::string> getblocksyms() {
	std::map<unsigned int, std::string> mp;
	for (unsigned int s=0; s < 32; s++) {
		wchar_t sym = 0x2580 + s;
		char *str = 0;
		asprintf(&str, "%lc", sym);
		mp.insert(std::make_pair(s, str));
	}
	return mp;
}
