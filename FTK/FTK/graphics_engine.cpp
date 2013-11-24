#include <iostream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <fstream>
#include <boost/archive/text_oarchive.hpp> // Lecture ecriture fichier
#include <boost/archive/text_iarchive.hpp>

#include "graphics_engine.h"
#include "util_fig.h"
#include "config_graphique.h"
#include "brique_particulaire.h"

//#include "shared.h"
//#include "menu_event_handler.h"


/**
 *  constructor. it creates Irrlicht & CEGUI contexts
 *  gui_system is connected to the graphics_engine
 */
graphics_engine::graphics_engine(game *g, bool daemon) :
	engine(g) {

	fichier_config = "config/config_graphique.conf";
	passive_mode = daemon;
	engine_name = "graphics engine";
	lastFPS = -1;

	// let's create the irrlicht context				
	if (!passive_mode)
		;//definir resolution fullscreen
	else
		;//definir resolution PAS D'ECRAN

	if (!passive_mode) {
		//rendre curseur invisible
		SDL_ShowCursor(SDL_DISABLE);

		// TODO : create the CEGUI context, using the irrlicht ressource provider
		set_state(ON_MENUS);
	}

	// On reccupère les config
	get_config_data();

	// Initilisation de la SDL
	initialisation_SDL_OpenGL();

	// Initialisation de l'horloge
	last_time = SDL_GetTicks();
	elapsed_time = 10;

	// Chargement des textures
	chargerTextures();

	typeCamera = PERSO_CAMERA;

	//Chargement de la camera fixé au personnage
	playerCamera = new PlayerCamera(vision_max);
}

graphics_engine::~graphics_engine() {
	supprimerTextures();
	delete playerCamera;
	
	//delete sys;
	//delete irrRenderer;
}

/**
 *	process events incoming to the graphics engine
 */
void graphics_engine::process_event(engine_event &e) {
	switch (e.type) {
	case engine_event::LOAD:
		//get_game_engine()->gr->load();
		break;
	default:
		break;

	}
}


/** 
 * called at each frame
 */
void graphics_engine::frame() {

	process_queue();

	// Gere les action clavier et sourie
	handleInput();

	// calcul les actions correspondants aux entrées
	get_game_engine()->gestionInputs(elapsed_time);

	// Affiche les elements du jeu
	drawAll();

	Uint32 stop_time = SDL_GetTicks();
	if ((stop_time - last_time) < time_per_frame) {
		SDL_Delay(time_per_frame - (stop_time - last_time));
	}

	// check if we must stop
	//if (!driver || !idevice->run())
	//parent->stooooop();

	//int fps = driver->getFPS();

	/*if (lastFPS != fps){
	 irr::core::stringw str = L"[";
	 str += driver->getName();
	 str += "] FPS:";
	 str += fps;
	 idevice->setWindowCaption(str.c_str());
	 lastFPS = fps;
	 }*/

	//driver->beginScene(true, true, irr::video::SColor(0,100,100,100));

	//sg->render();
	//gui->render();

	//driver->endScene();
}

/**
 *  function to invoke in order to close the application
 */
void graphics_engine::request_close() {
	parent->stooooop();
}

void graphics_engine::set_state(int s) {
	//state = s;

	//idevice->setEventReceiver(l_eh[s].get());
}

/**
 * load the whole config of the graphics engine
 */
void graphics_engine::get_config_data() {

	double fps;
	// On reccupere la configuration graphique stockée dans le fichier de config
	Config_graphique conf;
	{
		std::ifstream ifs(fichier_config);
		boost::archive::text_iarchive ia(ifs);

		ia >> conf;
	}
	// On charge les parametres avec la config reccupérée
	conf.dechargerConfig(width, height, vision_max, fps);

	time_per_frame = 1000 / fps;
}

/* ******** Fonctions internes ************** */

/**
 * Fonction appelée lors de l'"exit" d'SDL
 */
void sdlStop() {
	// ICI IL EST IMPERATIF DE TOUT DETRUIRE
	//delete camera;
	SDL_Quit();
}

void graphics_engine::initialisation_SDL_OpenGL() {
	// A METTRE AILLEURS ///////////////////////////////////
	light0_position[0] = -4.0f;
	light0_position[1] = -5.0f;
	light0_position[2] = 10.0f;
	light0_position[3] = 0.0f; // Position du soleil

	ambient[0] = 0.15f;
	ambient[1] = 0.15f;
	ambient[2] = 0.15f;
	ambient[3] = 1.0f; // couleur

	diffuse[0] = 0.5f;
	diffuse[1] = 0.5f;
	diffuse[2] = 0.5f;
	diffuse[3] = 1.0f; // diffusivite du soleil
	////////////////////////////////////////////////////////

	SDL_Init(SDL_INIT_VIDEO);
	atexit(sdlStop);
	SDL_WM_SetCaption("SDL GL Application", NULL);
	SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST); // Active le test de profondeur
	glEnable(GL_LIGHTING); // Active l'éclairage
	//glEnable(GL_COLOR_MATERIAL); // Active la couleur des materiaux
	glEnable(GL_CULL_FACE); // do not display back faces

	// Activations des parametres de la lumiere //
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	//////////////////////////////////////////////

	glEnable(GL_LIGHT0); // Allume la lumière n°1

	// Activation du brouillard ////////
	glEnable(GL_FOG);
	float FogCol[3]={0.8f,0.8f,0.8f}; // light grey
	glFogfv(GL_FOG_COLOR,FogCol);     // Set the fog color
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 30); //vision_max
	glFogf(GL_FOG_END, 40);
	////////////////////////////////////
	glEnable(GL_TEXTURE_2D);
}

void graphics_engine::drawAll() {
	// Mise à jour des buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// definition de l'angle de vue de la camera
	playerCamera->look(get_game_engine()->getPersonnage());

	// Positionnement du soleil
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// Skybox dans player_camera !

	get_game_engine()->getCarte()->dessinerCarte();
	get_game_engine()->getPersonnage()->dessinerMobile();
	get_game_engine()->getMobiles_liste()->draw();
	// On affiche les objets transparents en dernier !
	get_game_engine()->getCarte()->dessinerCarteTransparent();
	//get_game_engine()->getBP()->dessinerBrique();
	glPushMatrix();

	glTranslatef(get_game_engine()->getPersonnage()->position.X, get_game_engine()->getPersonnage()->position.Y, get_game_engine()->getPersonnage()->position.Z);

	glRotatef(get_game_engine()->getPersonnage()->orientation.X, 1, 0, 0);
	glRotatef(get_game_engine()->getPersonnage()->orientation.Y, 0, 1, 0);
	glRotatef(get_game_engine()->getPersonnage()->orientation.Z, 0, 0, 1);

	glPopMatrix();

	SDL_GL_SwapBuffers();
}

void graphics_engine::handleInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_QUIT:
			parent->stooooop();
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				parent->stooooop();
				break;
			default:
				get_game_engine()->keyboardInput(event.key);
			}
			break;
		case SDL_KEYUP:
		  get_game_engine()->keyboardInput(event.key);
			break;
		case SDL_MOUSEMOTION:
			get_game_engine()->mouseMotion(event.motion);
			break;
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
		  get_game_engine()->OnMouseButton(event.button);
			break;
		default:
			break;
		}
	}
	Uint32 current_time = SDL_GetTicks();
	elapsed_time = current_time - last_time;
	//std::cout << "FPS : " << 1000*double(1/double(elapsed_time)) << std::endl; //DEBUG
	last_time = current_time;

}

void graphics_engine::changerTypeVue() {
	if (playerCamera->getTypeVue() == TEM_PERSONNE_INV)
		playerCamera->setTypeVue(TEM_PERSONNE);
	else if (playerCamera->getTypeVue() == TEM_PERSONNE)
		playerCamera->setTypeVue(PERE_PERSONNE);
	else if (playerCamera->getTypeVue() == PERE_PERSONNE)
		playerCamera->setTypeVue(TEM_PERSONNE_INV);
}

void graphics_engine::changerDistanceCamera(double i) {
  playerCamera->chgDistanceCamera(i);
}


