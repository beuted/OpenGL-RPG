#include <iostream>
#include <boost/bind.hpp>

#include "game.h"
//- #include "shared.h"

game::game(parameter_analyser pa){
	p = pa;
	still_running = true;
	Gestion_textures** gest_text = new Gestion_textures*();
	*gest_text = NULL;
	//- shared::make();

	//- n = new network_engine(this);
	g = new game_engine(this, gest_text);
	gfx = new graphics_engine(this, pa.data["daemon"]);
	//- s = new sound_engine(this, pa.data["daemon"]);
	
	// let's link the engines together
	//- n->attach_game_engine(g);
	//- n->attach_graphics_engine(gfx);
	//- n->attach_sound_engine(s);
	
	g->attach_graphics_engine(gfx);
	//- g->attach_network_engine(n);
	//- g->attach_sound_engine(s);

	gfx->attach_game_engine(g);
	//- gfx->attach_network_engine(n);
	//- gfx->attach_sound_engine(s);

	//- s->attach_game_engine(g);
	//- s->attach_graphics_engine(gfx);
	//- s->attach_network_engine(n);

	*gest_text = new Gestion_textures();
}

/**
 * basic destructor
 */
game::~game(){
	try{
	  //- delete n;
	  delete g;
	  delete gfx;
	  //- delete s;
	}catch(std::exception &e){
		std::cerr << e.what() << std::endl;
	//}catch(CEGUI::Exception &e){
		//std::cerr << e.getMessage() << std::endl;
	}catch(...){
		std::cerr << "unhandled exception in ~game";
	}

	//- shared::unmake();
}

void game::run(){
	//gfx->get_gui()->display_menu1();
	bool current_still_running = still_running;
	boost::mutex::scoped_lock l(still_running_mutex);
	l.unlock();

	try{
	  //asio::io_service io;
	  //asio::deadline_timer timer(io, boost::posix_time::millisec(10));

		if (p.data["eco_mode"])		
			while (current_still_running){
			    //- n->frame();
				g->frame();
				gfx->frame();
				//s->frame();
				//timer.expires_at(timer.expires_at() + boost::posix_time::millisec(10));
				//timer.wait();
				l.lock();
					current_still_running = still_running;
				l.unlock();
			}
		else
			while (current_still_running){
			    //- n->frame();
				g->frame();
				gfx->frame();
				//s->frame();
				l.lock();
					current_still_running = still_running;
				l.unlock();
			}
	}catch(std::exception &e){
		std::cerr << e.what() << std::endl;
		//}catch(CEGUI::Exception &e){
		//std::cerr << e.getMessage() << std::endl;
	}catch(...){
		std::cerr << "unknown exception handled in game run";
	}
}

/**
 * I want you to stop the game !
 * thread safe
 */
void game::stooooop(){
	std::cout << "Stop requested !" << std::endl;
	boost::mutex::scoped_lock l(still_running_mutex);
		still_running = false;
	// l.unlock(); // not necessary due to end of scope
}
