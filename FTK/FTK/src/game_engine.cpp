#include <fstream>
#include <ctime>
#include <iostream> // Messages erreur AVIRER

#include "game_engine.h"
#include "graphics_engine.h"

/**
 * constructor
 */
game_engine::game_engine(game *g, Gestion_textures** _gest_text) :
	engine(g) {
	srand(time(NULL));

	engine_name = "game engine";
	gest_text = _gest_text;
	carte = new Carte(100, 100, 20, 20); //60
	personnage = new Personnage();
	personnage->initialize(gest_text);
	mobiles_liste = new Mobiles_liste();
	
	// Etat initial des touches
	_keystates[_keyconf["forward"]] = false;
	_keystates[_keyconf["backward"]] = false;
	_keystates[_keyconf["strafe_left"]] = false;
	_keystates[_keyconf["strafe_right"]] = false;
	_keystates[_keyconf["change_vue"]] = false;
	_keystates[_keyconf["jump"]] = false;

	// mise a zero du timer des touches
	_keywait["change_vue"] = 0;

	// On reccupère les config
	get_config_data();

	SDL_WM_GrabInput(SDL_GRAB_ON); // Permet de traiter les inputs clavier

	//- cons.reset(new console(this));

	//- map_path="./data/maps/";

	// let's collect all the available maps, players, data ...
	//- collect_available_maps();

}

/**
 * destructor
 */
game_engine::~game_engine() {
	delete carte;
	delete mobiles_liste;
	delete personnage;
	SDL_WM_GrabInput(SDL_GRAB_OFF);
}

/**
 * main function, processes a received event
 */
void game_engine::process_event(engine_event& e) {
}

bool game_engine::touchGround() {
	if (std::floor(personnage->position.X) > 0 && std::floor(personnage->position.X) <= carte->getLargx()) {
		if (std::floor(personnage->position.Y) > 0 && std::floor(personnage->position.Y) <= carte->getLargy()) {
			if (std::floor(personnage->position.Z) > 0 && std::floor(personnage->position.Z) <= carte->getHauteur()) {
				return !(carte->getElemMap(std::floor(personnage->position.X),std::floor(personnage->position.Y),std::floor(personnage->position.Z-1.2)).isTransparent());
			}
		}
	}

	return (personnage->position.Z <= 0);
}

bool game_engine::detectCollision(Brique hitbox) {
	bool detect = false;

	// Détection Voisins
	for(int i = std::max(1.0,floor(hitbox.position[0] - hitbox.dimension[0]/3)); i <= std::min((double)carte->getLargx()-1,ceil(hitbox.position[0] + hitbox.dimension[0]/3)); i++) {
		for(int j = std::max(1.0,floor(hitbox.position[1] - hitbox.dimension[1]/3)); j <= std::min((double)carte->getLargy()-1,ceil(hitbox.position[1] + hitbox.dimension[1]/3)); j++) {
			for(int k = std::max(0.0,floor(hitbox.position[2])+0.6); k <= std::min((double)carte->getHauteur()-1,ceil(hitbox.position[2] + hitbox.dimension[2])); k++) {
				if (!carte->getElemMap(i-1,j-1,k).isTransparent()) {
					//détection collision	      
					if (!detect) {
						if(hitbox.collisionBriqueToBloc(i-1,j-1,k)) {
							detect = true;
						}
					}
				}
			}
		}
	}
  
	return detect;
}
	

/**
 * called at each frame
 */
void game_engine::frame() {
	process_queue();

	// Chargement des display liste de la carte pour l'affichage
	carte->remplirLists(personnage->position);

	// Deplacement des mobiles sur la map
	mobiles_liste->deplacerMobiles();
	mobiles_liste->computeCollisions(carte);
	mobiles_liste->supprMobilesMorts();

	// MOTEUR PHYSIQUE ////////////////////
	Vector3D gravity(0,0,-100);

	double viscosity = 0.1;
	Vector3D forces = (gravity*personnage->poids - personnage->direction*viscosity)*1;
	const double dt = double(get_graphics_engine()->getElapsed_time())/1000.0;
	Vector3D newpos;
	// Nouvelle position : sert à "tester" la collision avant qu'elle n'ai lieu
	newpos = personnage->position;

	newpos += personnage->direction*dt + forces*(1/(2*personnage->poids))*dt*dt;

	Brique hitbox2 = *(personnage->hitbox);
	hitbox2.position[0] = newpos.X;
	hitbox2.position[1] = newpos.Y;
	hitbox2.position[2] = newpos.Z-1;
	hitbox2.orientation[0] = newpos.X;
	hitbox2.orientation[1] = newpos.Y;
	hitbox2.orientation[2] = newpos.Z;


	personnage->position.X = newpos.X;
	personnage->position.Y = newpos.Y;
	if (!detectCollision(hitbox2)) {
		personnage->position.Z = newpos.Z;
		personnage->direction += forces*(1/(double)personnage->poids)*dt;
	} else {
		personnage->direction.Z = 0;
	}

	// process the players
}

void game_engine::get_config_data() {
	//TODO : Ici on charge le fichier de config
	_keyconf["forward"] = SDLK_z;
	_keyconf["backward"] = SDLK_s;
	_keyconf["strafe_left"] = SDLK_q;
	_keyconf["strafe_right"] = SDLK_d;
	_keyconf["jump"] = SDLK_SPACE;
	_keyconf["change_vue"] = SDLK_a;
	_sensivity = 0.3;
}

// TODO : Attention dépend des FPS !!
/*bool game_engine::deplacerMobile(Mobile &m, Vector3D direction, GLfloat vitesse) {
  m.deplacerMobile(direction, vitesse);
  return true;
  }*/

void game_engine::keyboardInput(const SDL_KeyboardEvent & event) {
	for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end(); it++) {
		if (event.keysym.sym == it->first) {
			it->second = (event.type == SDL_KEYDOWN);
			break;
		}
	}
}

void game_engine::mouseMotion(const SDL_MouseMotionEvent & event) {
	personnage->orientation.Z-= event.xrel * _sensivity;
	personnage->phi -= event.yrel * _sensivity;

	// recalcul de forward et left
	static const Vector3D up(0, 0, 1);
	if (personnage->phi > 89)
		personnage->phi = 89;
	else if (personnage->phi < -89)
		personnage->phi = -89;
	double r_temp = cos(personnage->phi * M_PI / 180);
	personnage->forward.Z = sin(personnage->phi * M_PI / 180);
	personnage->forward.X = r_temp * cos(personnage->orientation.Z * M_PI / 180);
	personnage->forward.Y = r_temp * sin(personnage->orientation.Z * M_PI / 180);

	personnage->left = up.crossProduct(personnage->forward);
	personnage->left.normalize();
}

void game_engine::gestionInputs(Uint32 timestep) {

	/* Maj le tableau des temps d'attente de touches */
	majKeywait(timestep);
	Vector3D composanteMarche(0,0,0);
	personnage->direction.X = 0;
	personnage->direction.Y = 0;

	// Actions de deplacements
	//GLfloat speed = personnage->speed;

	if (_keystates[_keyconf["forward"]]) {
		//personnage->position += personnage->forward * (speed * timestep);
		composanteMarche += personnage->forward;
		// TODO: Fonction "orienter" pour orienter le corps indpdment de la tete
	}
	if (_keystates[_keyconf["backward"]]) {
		//personnage->position -= personnage->forward * (speed * timestep);
		composanteMarche -= personnage->forward;
	}
	if (_keystates[_keyconf["strafe_left"]]) {
		//personnage->position += personnage->left * (speed * timestep);
		composanteMarche += personnage->left;
	}
	if (_keystates[_keyconf["strafe_right"]]) {
		//personnage->position -= personnage->left * (speed * timestep);
		composanteMarche -= personnage->left;
	}
	if (_keystates[SDLK_p]) {
		takeScreenshot("screenshot.bmp");
	}

	composanteMarche.Z = 0;

	if (!(composanteMarche == 0)) {
		composanteMarche.normalize();
	}

	Brique hitbox2 = *(personnage->hitbox);
	hitbox2.position[0] = personnage->position.X;
	hitbox2.position[1] = personnage->position.Y;
	hitbox2.position[2] = personnage->position.Z-1;
	hitbox2.orientation[0] = personnage->orientation.X;
	hitbox2.orientation[1] = personnage->orientation.Y;
	hitbox2.orientation[2] = personnage->orientation.Z;
	hitbox2.position[0] += composanteMarche.X;
	hitbox2.position[1] += composanteMarche.Y;
	hitbox2.position[2] += composanteMarche.Z;


	if (_keystates[SDLK_SPACE]) {
		if (touchGround()) {
			Vector3D jump (0,0,30);
			personnage->direction = jump;

		}
    
	} 
	if(!detectCollision(hitbox2)) {
		personnage->direction += composanteMarche*personnage->speed;
	}
 

	// Animations
	if (!_keystates[_keyconf["strafe_right"]] && !_keystates[_keyconf["strafe_left"]]
	    && !_keystates[_keyconf["backward"]] && !_keystates[_keyconf["forward"]]) {
		personnage->stopper();
	} else {
		personnage->marcher(3);
	}


	// Actions liées au moteur graphique :
	if (_keystates[_keyconf["change_vue"]]) {
		if (_keywait["change_vue"] <= 0) {
			get_graphics_engine()->changerTypeVue();
			_keywait["change_vue"] += 300;
		}
	}
}

void game_engine::OnMouseButton(const SDL_MouseButtonEvent & event)
{
	// GESTION DU ZOOM/DEZOOM CAMERA
	if ((event.button == SDL_BUTTON_WHEELUP)&&(event.type == SDL_MOUSEBUTTONDOWN)) { //coup de molette vers le haut
		get_graphics_engine()->changerDistanceCamera(1);
	}
	else if ((event.button == SDL_BUTTON_WHEELDOWN)&&(event.type == SDL_MOUSEBUTTONDOWN)) { //coup de molette vers le bas
		get_graphics_engine()->changerDistanceCamera(-1);
	}

	if ((event.button == SDL_BUTTON_LEFT)&&(event.type == SDL_MOUSEBUTTONDOWN)) { //click
		lancer_projectile(personnage);
	} else if((event.button == SDL_BUTTON_RIGHT)&&(event.type == SDL_MOUSEBUTTONDOWN)) {
		poser_bloc();
	}
}


void game_engine::majKeywait(Uint32 timestep) {
	for (std::map<std::string,Uint32>::iterator it = _keywait.begin() ; it != _keywait.end(); ++it){
		if (it->second >= timestep)
			it->second -= timestep;
		else
			it->second = 0;
	}
}

// ACTIONS DU JEU

void game_engine::lancer_projectile(Personnage* personnage) {
	Projectile *m = new Projectile(personnage->position + 0.5*personnage->dimension.Y*personnage->left
				       + Vector3D(0,0,0.7*personnage->dimension.Z), personnage->forward,1);
				       mobiles_liste->push_front(m);
}

void game_engine::poser_bloc() {
	Vector3D v = get_graphics_engine()->getPlayerCamera()->getBlocPrec(carte, personnage);
	carte->modifierBloc(int(v.X), int(v.Y), int(v.Z),3);
	carte->remplirListNonTransp();
	carte->remplirListTransp();
}
