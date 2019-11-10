#ifndef H__game_engine__
#define H__game_engine__

#include <map>
#include <string>
#include <vector>
#include <SDL/SDL.h>

#include "engine.h"
#include "engine_event.h"
#include "carte.h"
#include "personnage.h"
#include "mobiles_liste.h"
#include "playercamera.h"
#include "vector3d.h"

#include "brique_particulaire.h" // A VIRER APRES TEST

//- #include "game_round.h"
//- #include "console.h"
//- #include "available_map.h"

class graphics_engine;
class network_engine;
class console;

/**
 * game engine class
 */
class game_engine: public engine {
public:
	game_engine(game*, Gestion_textures** _gest_text);
	~game_engine();

	void frame();
	virtual void process_event(engine_event&);

	// round in construction (work in progress)
	//- round_options wip;

	//- boost::shared_ptr<game_round> gr;

	//- inline boost::shared_ptr<console> get_console(){return cons;}

	/* ***** Getters ****** */
	Carte* getCarte() {
		return carte;
	} //TODO : mettre a const?

	Personnage* getPersonnage() const{
		return personnage;
	} //TODO : mettre a const?

	Mobiles_liste* getMobiles_liste() const{
		return mobiles_liste;
	}

	/* ******* Autres fonctions ******** */
	
	/**
	 * Teste la collision du personnage avec l'environnement
	 */
	bool detectCollision(Brique hitbox);

	bool touchGround();

	/**
	 * Deplace un mobile dans une direction à une certaine vitesse
	 * \return : si le deplacement a pu etre effectué ou non (collision etc ...)
	 */
	//bool deplacerMobile(Mobile& m, Vector3D direction, GLfloat vitesse);

	/**
	 * Mise a jour du tableau des touches enfoncé
	 */
	void keyboardInput(const SDL_KeyboardEvent & event);

	/**
	 * mise a jour de la position de le tete du personnage
	 */
	void mouseMotion(const SDL_MouseMotionEvent & event);

	/**
	 * Gere les input. Fait les actions relative a chaque entree en fct de la situation.
	 */
	void gestionInputs(Uint32 timestep);

	/**
	 * Gere les inputs à la sourie
	 */
	void OnMouseButton(const SDL_MouseButtonEvent & event);

protected:

	// own interpreter, used to control the game by a command line
	//- boost::shared_ptr<console> cons;

	//- std::string map_path;

	//- void collect_available_maps();

	//- std::vector<boost::shared_ptr<available_map>> l_maps;
	//- std::vector<boost::shared_ptr<available_ai >> l_ais;

	/**
	 * Carte où se déroule le jeu
	 */
	Carte* carte;

	/**
	 * Personnage incarné par le joueur
	 */
	Personnage* personnage;

	/**
	 * Liste des mobiles sur la map (personnage exclu)
	 */
	Mobiles_liste* mobiles_liste;

	/**
	 * Gestionnaire de texture
	 */
	Gestion_textures** gest_text;

	/* ****** ACTIONS DU JEU ************ */

	void lancer_projectile(Personnage* personnage);

	void poser_bloc();

	/* ****** GESTION DU CLAVIER ******** */

	typedef std::map<SDLKey,bool> KeyStates;

	/**
	 * Tableau de l'etat des touches
	 */
	KeyStates _keystates;

	typedef std::map<std::string,SDLKey> KeyConf;

	/**
	 * Tableau de configuration des touches
	 */
	KeyConf _keyconf;

	typedef std::map<std::string,Uint32> KeyWait;

	/**
	 * Tableau de l'attente entre chaque activation d'une touche
	 */
	KeyWait _keywait;

	/**
	 * sensibilité sourie
	 */
	double _sensivity;

	/**
	 * load the whole config of the graphics engine
	 */
	void get_config_data();

	/**
	 * Mets a jour le tableau keywait
	 */
	void majKeywait(Uint32 timestep);

};

#endif
