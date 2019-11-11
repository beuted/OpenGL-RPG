/*
 * brique_particulaire.h
 *
 *  Created on: 11 mars 2013
 *      Author: benoit
 */

#ifndef BRIQUE_PARTICULAIRE_H_
#define BRIQUE_PARTICULAIRE_H_

#define MAX_PARTICLES 100

#include "brique_gene.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>  //TRACAGE
#include <iostream> //TRACAGE

typedef struct // Création de la structure
{  bool active; // Active (1=Oui/0=Non)
   double life; // Durée de vie
   double fade; // Vitesse de disparition
   double r, g, b; // Valeurs RGB pour la couleur
   double x, y, z; // Position
   double xi, yi, zi; // Vecteur de déplacement
   double xg, yg, zg; // Gravité
}particles;

/**
 * \class Brique particulaire : classe derivant de brique.
 * Zone de generation de particules.
 */
class Brique_particulaire: public Brique_gene {
 protected:

	double puissance;

	/* Tableau de stockage des particules */
	particles particle[MAX_PARTICLES];

 public:


	/**
	 * Constructeur :
	 */
	Brique_particulaire(GLfloat* _dimension, GLfloat* _position, GLfloat* _orientation, GLfloat* _axe_rotation, double puissance);

	/**
	 * Dessine les particules constituant la brique
	 */
	void dessinerBrique();

		/**
	 * Fonction de collision pour une brique_particulaire (point)
	 */
	bool collision() {return false;};

};
#endif
