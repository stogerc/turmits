#ifndef MAIN_HPP
#define MAIN_HPP
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <getopt.h>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <FL/fl_ask.H>

bool load(std::string);					//load turmite frome file

int load_config(std::string);			//load setings from config


void show_help(void);


static const struct option longOpts[] = {
	{ "turmit", required_argument, NULL, 't' },
	{ "field", required_argument, NULL, 'f' },
	{ "rule", required_argument, NULL, 'r' },
	{ "config", required_argument, NULL, 'c' },
	{ "output", required_argument, NULL, 'o' },
	{ "verbose", no_argument, NULL, 'v' },
	{ "randomize", no_argument, NULL, 0 },
	{ "help", no_argument, NULL, 'h' },
	{ NULL, no_argument, NULL, 0 }
};


#endif
