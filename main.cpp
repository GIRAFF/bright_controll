#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>

#define BRT_STEP	5
#define BRT_MAX		100
#define BRT_MIN		0
#define BRT_PATH	"/sys/class/backlight/acpi_video0/brightness"

int main(int argc, char **argv)
{
	if(argc == 0) { std::cout << "Usage: brt <up/down>"; exit(0); }

	std::ifstream in;
	in.open(BRT_PATH, std::ifstream::in);
	if(!in.is_open()) { std::cout << "PANIC! Can't open file!"; exit(0); }

	int brt = NULL;
	in >> brt;

	if(!strcmp(argv[1], "down"))
	{
		if(brt == BRT_MIN) exit(0);
		brt -= BRT_STEP;
	}
	else if(!strcmp(argv[1], "up"))
	{
		if(brt == BRT_MAX) exit(0);
		brt += BRT_STEP;
	}
	else { std::cout << "Usage: brt <up/down>"; exit(0); }
	char req[200];
	sprintf(req,"echo %i > %s",brt,BRT_PATH);
	system(req);
}