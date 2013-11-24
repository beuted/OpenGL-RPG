/*
 * mobile.h
 *
 *  Created on: 11 mars 2013
 *      Author: benoit
 */

#ifndef MOBILE_H_
#define MOBILE_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "brique.h"
#include "vector3d.h"
#include "carte.h"

/**
 * Classe représentant tout objet mobile sur la carte
 * (personnage, objet, fleche, boule de feu...).
 * Elle sera heritée par la suite
 */
class Mobile {

protected:

	/**
	 * Arbre des briques de ce modele.
	 */
	Brique_gene* arbre_briques;

public:
	/**
	 * int determinant si le mobile doit etre retirer du plateau (lorqu'il
	 * atteint 0) si infini vaut -1
	 */
	int duree_vie;

	/**
	 * Vitesse du mobile
	 */
	double speed;
	
	/**
	 * Vecteur de direction du mobile (norme 1 !)
	 */
	Vector3D direction;

	/**
	 * Hitbox du modèle
	 * A priori une seule brique, sauf si besoin de raffinement
	 */
	Brique* hitbox;

	/**
	 * Dimensions de l'objet
	 */
	Vector3D dimension;

	/**
	 * position x, y, z
	 */
	Vector3D position;

	/**
	 * angles d'inclinaison a_x, a_y, a_z
	 */
	Vector3D orientation;
	
	/**
	 * Poids du mobile
	 */
	float poids;

	/**
	 * \brief Constructeur
	 *
	 * Constructeur d'un mobile par default
	 */
 Mobile() : duree_vie(200), direction() {
		position.X = 0.0f;
		position.Y = 0.0f;
		position.Z = 0.0f;
		orientation.X = 0.0f;
		orientation.Y = 0.0f;
		orientation.Z = 0.0f;
		dimension.X = 0.0f;
		dimension.Y = 0.0f;
		dimension.Z = 0.0f;
		poids = 0.1; // poids non nul par défaut

		// initialisation de la HITBOX pour tous les mobiles
		GLfloat dim[] = {0.6, 0.8, 2.2};
		GLfloat pos[] = {0.0, 0.0, -0.8};
		GLfloat orient[] = {0.0, 0.0, 0.0};
		GLfloat axe_rot[] = {0.0, 0.0, 0.0};
		hitbox = new Brique(dim, pos, orient, axe_rot, NULL, NULL);
	}

	/**
	 * \brief Constructeur
	 *
	 * Constructeur d'un mobile 
	 */
 Mobile(Vector3D _position, Vector3D _orientation, Vector3D _dimension, Vector3D direction, float _speed) : duree_vie(200) {
		speed = _speed;
		position = _position;
		orientation = _orientation;
		dimension = _dimension;
		poids = 0.1; // poids non nul par défaut

		// initialisation de la HITBOX pour tous les mobiles
		GLfloat dim[] = {_dimension.X, _dimension.Y, _dimension.Z};
		GLfloat pos[] = {0.0, 0.0, 0.0};
		GLfloat orient[] = {0.0, 0.0, 0.0};
		GLfloat axe_rot[] = {0.0, 0.0, 0.0};
		hitbox = new Brique(dim, pos, orient, axe_rot, NULL, NULL);
	}

	/**
	 * \brief Destructeur
	 *
	 * Destructeur d'un mobile
	 */
	~Mobile() {
		//delete &dimension;
		//delete &position;
		//delete &orientation;
		delete arbre_briques;
		delete hitbox;
	}

	/**
	 * Dessine le mobile en parcourant son arbre de briques.
	 */
	void dessinerMobile();

	/**
	 * Deplace le mobile dans la direction souhaité
	 * TDO : depend des fps ! ! 
	 */
	void deplacerMobile();

	/**
	 * Fonction determinant s'il y une collsion entre le mobile et la carte
	 * \param v : bloc rencontré (en cas de collision)
	 */
	virtual bool collision(Carte* carte, Vector3D* &v) {return true;};

	/**
	 * Fonction determinant s'il y a une collision et effectuant
	 * les actions necessaire dans le cas ou il y en a une
	 */
	virtual void computeCollision(Carte* carte){};

	/**
	 * Test la collision entre le modele et un bloc de la carte
	 */
	bool collisionModeleToBloc(int i, int j, int k);
};

#endif /* MOBILE_H_ */
