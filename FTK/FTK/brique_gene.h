/*
 * brique_gene.h
 *
 *  Created on: 5 may 2013
 *      Author: benoit
 */

#ifndef BRIQUE_GENE_H_
#define BRIQUE_GENE_H_

#include "gestion_textures.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <stdio.h>  //TRACAGE
#include <iostream> //TRACAGE

/**
 * Classe représentant l'entité de base de la représentation des mobiles. Ces entitées
 * sont lié dans une structure d'abres les unes aux autres pour former un mobile.
 * expl : la brique Tete est lié à la brique corps du personnage qui est lié aux briques
 * bras etc ...
 *
 * TODO : Pour l'instant uniquement des "rectangles 3D" 
 * 	Mais il faudra généraliser ca si on veut des cercles etc...
 */
class Brique_gene {

 protected:

	/**
	 * Liste des suivant du noeud brique actuel.
	 * (si = null ce noeud est une feuille)
	 */
	std::vector<Brique_gene*> suivants;

	/**
	 * Textures du cube (numéros)
	 */
	int texture_image[6];

	/**
	 * Gestionnaire de texture
	 */
	Gestion_textures** gest_text;

 public:

	/**
	 * longeur x, y, z
	 */
	GLfloat dimension[3];

	/**
	 * position x, y, z
	 */
	GLfloat position[3];

	/**
	 * angles d'inclinaison a_x, a_y, a_z
	 */
	GLfloat orientation[3];

	/**
	 * axe de rotation pour rotations
	 */
	GLfloat axe_rotation[3];

	/**
	 * \brief Constructeur
	 *
	 * Constructeur d'un mobile
	 */
	Brique_gene() : suivants() {
		dimension[0] = 1; dimension[1] = 1; dimension[2] = 1;
		position[0] = 0; position[1] = 0; position[2] = 0;
		orientation[0] = 0; orientation[1] = 0; orientation[2] = 0;
	}

	/**
	 * Constructeur de Brique.
	 * \param dimension, orientation, position : GLfloat[3]
	 */
	Brique_gene(GLfloat* _dimension, GLfloat* _position, GLfloat* _orientation, GLfloat* _axe_rotation, int* textures, Gestion_textures** _gest_text) {
		dimension[0] = _dimension[0];
		dimension[1] = _dimension[1];
		dimension[2] = _dimension[2];
		position[0] = _position[0];
		position[1] = _position[1];
		position[2] = _position[2];
		orientation[0] = _orientation[0];
		orientation[1] = _orientation[1];
		orientation[2] = _orientation[2];
		axe_rotation[0] = _axe_rotation[0];
		axe_rotation[1] = _axe_rotation[1];
		axe_rotation[2] = _axe_rotation[2];

		gest_text = _gest_text;

		if (textures != NULL) {
			for (int i = 0; i < 6; i++) {
				texture_image[i] = textures[i];
			}
		}
	}

	/**
	 * \brief Destructeur
	 *
	 * Destructeur d'un mobile
	 */
	~Brique_gene(){
		for(size_t i = 0; i < suivants.size(); i++)
     delete(suivants[i]);
	}

	/**
	 * Permet de dessiner une brique et ses suivants
	 */
	void dessinerBriqueRec();

	/**
	 * Dessine la brique fonction d heritage
	 */
	virtual void dessinerBrique(){};

	/**
	 * Reccupere la liste de Briques
	 */
	std::vector<Brique_gene*>& getListSuivants();// {return std::list<Brique*>;}

	/**
	 * Fonction de collision générale avec la carte
	 */
	virtual bool collision(){return true;};

	/**
	 * Collision Brique to Bloc
	 */
	bool collisionArbreBriquesToBloc(int i, int j, int k);

	/**
	 * Collision Brique to Bloc
	 */
	bool collisionBriqueToBloc(int i, int j, int k);

	/**
	 * Fonction affiche carct d'une brique
	 * !FONCTION DE DEBUG!
	 */
	void afficher() {
	  std::cout << "dimension :" << dimension[0] <<  dimension[1]<< dimension[2]<< std::endl;
	  std::cout << "position :"  << position[0] <<  position[1] << position[2] << std::endl;
	  std::cout << "orientation :" << orientation[0] <<  orientation[1] << orientation[2] << std::endl;
	}

};
#endif
