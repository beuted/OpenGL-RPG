
#ifndef H__engine__
#define H__engine__

#include <queue>
#include <map>
#include <string>
#include <boost/thread/thread.hpp>
//#include <asio.hpp>

//- #include "config_file.h"
#include "engine_event.h"

class game_engine;
//- class network_engine;
class graphics_engine;
//- class sound_engine;
class game;

/**
 *  abstract class, uninstaciable
 * engines are used as modules in the game objet
 * each engine is connected to the other engines (game, graphics, network)
 * Two solutions to send messages to another message : 
 * - directly call the functions through a pointor to the engine to contact
 * - push a message to the event_queue of the engine to contact
 * The event_queue is emptied on each frame
 */
class engine{
public:
	engine(game*);
	virtual ~engine();

	// accepts the event from previous engines
	void push_event(engine_event&);

	// empty the queues from previous engines
	void process_queue();

	virtual void frame() = 0;

	void attach_game_engine(game_engine *e){ge = e;}
	//- void attach_network_engine(network_engine *e){ne = e;}
	void attach_graphics_engine(graphics_engine *e){gfxe = e;}
	//- void attach_sound_engine(sound_engine *e){se = e;}

	void send_message_to_graphics(engine_event&);
	//- void send_message_to_network(engine_event&);
	void send_message_to_game(engine_event&);
	//- void send_message_to_sound(engine_event&);

	inline game*		get_parent()		{return parent;}
	inline game_engine*	get_game_engine()	{return ge;}
	//- inline network_engine*	get_network_engine()	{return ne;}
	inline graphics_engine* get_graphics_engine()	{return gfxe;}
	//- inline sound_engine*	get_sound_engine()	{return se;}

	int state;

	enum{
		STATE_NOTHING,
		STATE_QUITTING,	
		STATE_WAITING_PLAYERS,
		STATE_PLAYING_INTRO,
		STATE_LOADING_ROUND,
		STATE_PLAYING
	};

	// mutex to protect the current state
	boost::mutex state_mutex;
protected:
	game *parent;

	game_engine *ge;
	//- network_engine *ne;
	graphics_engine *gfxe;
	//- sound_engine *se;
	
	std::string engine_name;
	
	std::queue<engine_event> events_queue;
	virtual void process_event(engine_event&) = 0;
	//- virtual void get_config_data() = 0;

	//- config_file cfile;

	// mutex to protect the event queue
	boost::mutex queue_mutex;

	bool passive_mode;
};

#endif
