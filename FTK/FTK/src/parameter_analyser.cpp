#include <vector>
#include <iostream>

#include "parameter_analyser.h"

parameter_analyser::parameter_analyser(){
}

/**
 * parses the command line and store the argument into data
 */
parameter_analyser::parameter_analyser(int argc, char **argv){
	std::vector<std::string> command_line;
	for (int i=1; i<argc; i++)
		command_line.push_back(std::string(argv[i]));

	// set the default values
	data["daemon"]   = false;
	data["eco_mode"] = false;

	// parsing
	std::vector<std::string>::iterator i;
	for (i=command_line.begin(); i!=command_line.end(); i++){
		std::cout << *i << ", ";
		if (*i == "--daemon")
			data["daemon"] = true;
		else if (*i == "--eco_mode")
			data["eco_mode"] = true;
	}
}
