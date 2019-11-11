/**
 * main.cpp
 *
 *  \date 23 févr. 2013
 */

#include <iostream>
#include <fstream>

#include "game.h"
#include "parameter_analyser.h"

int main(int argc, char **argv) {
	parameter_analyser p(argc, argv);

	// redirect cout and cerr in files
	std::ofstream Out("out.txt");
	std::ofstream Err("err.txt");
	std::cout.rdbuf(Out.rdbuf());
	std::cerr.rdbuf(Err.rdbuf());
    
	game g(p);
	g.run();
	return 0;
}
