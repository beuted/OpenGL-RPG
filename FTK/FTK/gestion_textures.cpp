/*
 * textures.cpp
 *
 *  Created on: 8 mars 2013
 *      Author: benoit
 */
#include "gestion_textures.h"
#include "sdlglutils.h"
#include <iostream> //pr les msg d'erreur


Gestion_textures::Gestion_textures() {
	/* TEXTURES MURS */
		textures = new GLuint[20];

		textures[0] = loadTexture("textures/metal091.jpg");
		//pour la roquette
		textures[1] = loadTexture("textures/metal091.jpg");
		textures[2] = loadTexture("textures/metal091.jpg");
		textures[3] = loadTexture("textures/metal091.jpg");
		textures[4] = loadTexture("textures/metal091.jpg");
		//autre texture
		textures[5] = loadTexture("textures/concrete001.jpg");
		textures[6] = loadTexture("textures/floor032.jpg");
		textures[7] = loadTexture("textures/brick009.jpg");
		textures[8] = loadTexture("textures/wood002.jpg");
		textures[9] = loadTexture("textures/wood006.jpg");
		//porte
		textures[10] = loadTexture("textures/door009.jpg");
		//pour les caisse
		textures[11] = loadTexture("textures/crate03.jpg");
		//toit
		textures[12] = loadTexture("textures/roof05.jpg");
		//fenetre
		textures[13] = loadTexture("textures/metal091.jpg");
		//Herbe
		textures[14] = loadTexture("textures/veg008.jpg");
		//Eau de la piscine
		textures[15] = loadTexture("textures/eau.jpg");
		// Dalle de la piscine
		textures[16] = loadTexture("textures/floor006b.jpg");
		// Fond du puit
		textures[17] = loadTexture("textures/veg010.jpg");
		// puit
		textures[18] = loadTexture("textures/brick077.jpg");
		// Face perso
		textures[19] = loadTexture("textures/perso/tete_face_2.jpeg");

}

Gestion_textures::~Gestion_textures() {
	glDeleteTextures(20, textures );
	delete[] textures;
}

GLuint Gestion_textures::getTexture(unsigned int i) {
	if (i >= 20) {
		std::cerr << "Erreur : cette texture n'existe pas" << std::endl;
		exit(-1);
	}
	return textures[i];
}
