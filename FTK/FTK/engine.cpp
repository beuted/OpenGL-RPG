#include <iostream>

#include "engine.h"
#include "graphics_engine.h"
//#include "network_engine.h"
#include "game_engine.h"

engine::engine(game *g):parent(g){
	ge = NULL;
	//ne = NULL;
	gfxe = NULL;
	//se = NULL;
	passive_mode = false;
}

engine::~engine(){
	// waits for all the threads to terminate
	// take care to interblockings
}

/**
 * empties the event queue. For each event, it launches the appropriate process
 */
void engine::process_queue(){
	while (! events_queue.empty()){
		// we must prevent concurrent accesses, that's why we use scoped lock
		boost::mutex::scoped_lock lock(queue_mutex);
			engine_event &e = events_queue.front();
			events_queue.pop();
		
		// let's release the mutex
		// the mutex is released before the end of the scope in order to minimize the critical zone
		lock.unlock();

		process_event(e);
	}
}

/**
 * adds en event in the To-do queue
 */
void engine::push_event(engine_event& e){
	// as well as for the process queue function, we protect the event queue with the mutec
	
	boost::mutex::scoped_lock lock(queue_mutex);
	events_queue.push(e);

	// the mutex is automatically unlocked at this point due to the end of the scope
}

void engine::send_message_to_graphics(engine_event& e){
	gfxe->push_event(e);
}

/*void engine::send_message_to_network(engine_event& e){
	ne->push_event(e);
	}*/

void engine::send_message_to_game(engine_event& e){
	ge->push_event(e);
}

/*void engine::send_message_to_sound(engine_event& e){
	se->push_event(e);
	}*/
