/*
 * textures.h : Fichier permettant l'organisation et la gestion des textures
 *
 *  Created on: 8 mars 2013
 *      Author: benoit
 */

#ifndef TEXTURES_H_
#define TEXTURES_H_

#include <GL/gl.h>
#include <GL/glu.h>

class Gestion_textures {
private:
	GLuint* textures;

public:
	/**
	 * Constructeur : charge les textures
	 */
	Gestion_textures();

	/**
	 * Destructeur : detruit le tableau des textures
	 */
	~Gestion_textures();

	/**
	 * @return la texture num i
	 */
	GLuint getTexture(unsigned int i);
};

#endif /* TEXTURES_H_ */
