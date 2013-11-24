#ifndef H__graphics_engine__
#define H__graphics_engine__

#include <map>
//#include <irrlicht.h>
//#include <CEGUI.h> !! A VIRER !!
//#include <RendererModules/IrrlichtRenderer/irrlichtrenderer.h>
#include <string>

#include "engine.h"
#include "engine_event.h"
//- #include "gui_system.h"
#include "game.h"
//#include "event_handler.h"
// #include "freeflycamera.h" plus besoin
#include "playercamera.h"
#include "skybox.h"

class gui_system;
class game;

/**
 * graphics engine class
 */
class graphics_engine : public  engine{
public:
	graphics_engine(game*, bool);
	~graphics_engine();

	void frame();

	void set_state(int);

	// requested by children classes to stop the application
	void request_close();

	/**
	 * Enum des etats du jeu (Pas encore utilisé c'etait dans le projet exemple)
	 * TODO : Est-ce utile à garder ? ou faut-il faire autrement ?
	 */
	enum{
		ON_MENUS,
		ON_GAME
	};

	/**
	 * enum des types de camera
	 */
	enum TypeCamera{
		FREE_CAMERA,
		PERSO_CAMERA
	};

    /* **** Fonctions liées aux evenements ***** */

    /**
     * Change le type de vue de la camera courant
     * (3em pers, 1ere pers, 3em pers inversee ...)
     */
    void changerTypeVue();
    
    /**
     * Change la distance de la camera par rapport au joueur
     */
    void changerDistanceCamera(double i);

    /* **** GETTERS **************************** */
    PlayerCamera* getPlayerCamera() {return playerCamera;}

    Uint32 getElapsed_time() {return elapsed_time;}

protected:
	/*boost::shared_ptr<gui_system> gui;
	boost::shared_ptr<scene_graph> sg;
	std::map<int, boost::shared_ptr<event_handler>> l_eh;

	irr::video::IVideoDriver *driver;
	CEGUI::System *sys;
	irr::IrrlichtDevice *idevice;
	CEGUI::IrrlichtRenderer *irrRenderer;*/

	void process_event(engine_event&);

	/**
	 * load the whole config of the graphics engine
	 */
	void get_config_data();

	int lastFPS;

	/**
	 * Largeur de la fenetre
	 */
	unsigned int width;

	/**
	 * hauteur de la fenetre
	 */
	unsigned int height;
	
	/**
	 * Distance max en cube que peux voir le joueur
	 */
	double vision_max;

	/**
	 * Skybox
	 */
	//Skybox skybox;

private :
	/**
	 * Emplacement du fichier de config graphique
	 */
	const char* fichier_config;
	
	/**
	 *  Parametres de la lumiere de base TODO: Gerer la lumiere de base dans une classe ?
	 */
	GLfloat light0_position [4]; // Position du soleil
	GLfloat ambient[4];          // couleur
	GLfloat diffuse[4];          // diffusivite du soleil
	
	
	/**
	 * Temps entre chaque image
	 */
	Uint32 time_per_frame;
	/**
	 * Permet de retenir le temps auquel on a afficher la derniere image
	 */
	Uint32 last_time;
	
	/**
	 * Permet de retenir le temps entre deux images
	 */
	Uint32 elapsed_time;
	
	/**
	 * Camera permettant à l'utilisateur de se deplacer
	 * librement sur la carte
	 */
	PlayerCamera * playerCamera;

	/**
	 * Type de camera activée
	 */
	TypeCamera typeCamera;

	/**
	 * Fonction initialisant la SDL et les options utilisé de cele-ci
	 */
	void initialisation_SDL_OpenGL();
	
	/**
	 * Dessine tout les elements du jeu (la carte, les personnages etc ...)
	 */
	void drawAll();
	
	/**
	 * Gere les entrées clavier/sourie
	 */
	void handleInput();

};

#endif
