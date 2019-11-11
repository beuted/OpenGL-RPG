#ifndef H__game__
#define H__game__

#include "game_engine.h"
#include "graphics_engine.h"
//- #include "network_engine.h"
#include "parameter_analyser.h"

class game{
public:
	game(parameter_analyser);
	~game();
	int init();
	void run();

	void stooooop();

private:
	game_engine *g;
	graphics_engine *gfx;
	//- network_engine *n;
	//- sound_engine *s;

	parameter_analyser p;
	boost::mutex still_running_mutex;
	bool still_running;
};

#endif
