#ifndef _PERSONNAGE_
#define _PERSONNAGE_

/**
 * \file personnage.h
 * \brief Classe décrivant un personnage
 *
 * \version 0.1
 * \date 20/02/13
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "gestion_textures.h"
#include "mobile.h"
#include "vector3d.h"

/**
 * \class Personnage personnage.h
 * \brief Décrit un personnage
 */

class Personnage: public Mobile {

private:

  	enum EtatMarche{
	        ETAT0,
		ETAT1,
		ETAT2,
		ETAT3,
		ETAT4
	};
	/**
	 * Etat de la marche (pour l'animation)
	 */
	EtatMarche etatMarche;


public:

	/**
	 * angle verticale de la tete (mouvement "oui")
	 */
	double phi;

	/**
	 * angle horizontale de la tete (mouvement "non")
	 */
	double theta;

	/**
	 * Vecteur direction de la caméra
	 */
	Vector3D forward;

	/**
	 * Direction pas-chassés sur la gauche
	 */
	Vector3D left;

	/**
	 * \brief Constructeur
	 *
	 * Constructeur d'un personnage
	 */
	Personnage();

	/**
	 * \brief Destructeur
	 *
	 * Destructeur d'un personnage
	 */
	~Personnage();


	/**
	 * Initialise le personnage, ses briques, ses textures ...
	 */
	void initialize(Gestion_textures** _gest_text);

	/**
	 * Fonction deplacant le personnage dans la bonne direction
	 */
	void deplacer(Uint32 timestep);

	// FONCTIONS GRAPHIQUES

	/**
	 * Fonction jouant l'animation de la marche à la vitesse v
	 */
	void marcher(double vitesse);

	/**
	 * Fonction repositionnant le personnag au repos
	 */
	void stopper();

	/**
	 * Fonction determinant s'il y une collision entre le personnage
	 * et la carte
	 */
	bool collision(Carte* carte, Vector3D* &v) {return false;}

};

#endif
