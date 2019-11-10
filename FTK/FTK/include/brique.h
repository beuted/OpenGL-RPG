/*
 * brique.h
 *
 *  Created on: 11 mars 2013
 *      Author: benoit
 */

#ifndef BRIQUE_H_
#define BRIQUE_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <stdio.h>  //TRACAGE
#include <iostream> //TRACAGE

#include "gestion_textures.h"
#include "brique_gene.h"

/**
 * Classe représentant l'entité de base de la représentation des mobiles. Ces entitées
 * sont lié dans une structure d'abres les unes aux autres pour former un mobile.
 * expl : la brique Tete est lié à la brique corps du personnage qui est lié aux briques
 * bras etc ...
 *
 * TODO : Pour l'instant uniquement des "rectangles 3D" 
 * 	Mais il faudra généraliser ca si on veut des cercles etc...
 */
class Brique : public Brique_gene {
 public:
 Brique(GLfloat* _dimension, GLfloat* _position, GLfloat* _orientation, GLfloat* _axe_rotation, int* textures, Gestion_textures** _gest_text) : Brique_gene(_dimension, _position, _orientation, _axe_rotation, textures, _gest_text) {
	}

	/**
	 * \brief Destructeur
	 *
	 * Destructeur d'un mobile
	 */
	~Brique(){}

	/**
	 * Dessine la brique;
	 */
	void dessinerBrique();

	/**
	 * Fonction de collision pour une brique (rectangle 3d)
	 */
	bool collision() {return false;};


};

#endif /* BRIQUE_H_ */
