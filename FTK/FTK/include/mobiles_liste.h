/*
 * mobile_liste.h
 *
 *  Created on: 11 mars 2013
 *      Author: benoit
 */

#ifndef MOBILES_LISTE_H_
#define MOBILES_LISTE_H_

#include <list>

#include "mobile.h"
#include "projectile.h"
#include "explosion.h"
#include "carte.h"

/**
 * \class Mobiles_liste : Classe liste de tout les mobiles utile pour
 * l'affichage et la gestion des interactions (amélioration du container :
 *  Map selon l'emplacement de l'objet)
 */
class Mobiles_liste {
 private:
	std::list<Mobile*>* liste_mobiles;

 public : 
	/**
	 * Constructeur
	 */
	Mobiles_liste() {
		liste_mobiles =  new std::list<Mobile*>();
	}

	~Mobiles_liste() {
		delete liste_mobiles;
	}
	/**
	 * Fonction affichant tout les mobiles
	 */
	void draw();
	/**
	 * Applique les deplacement necessaire sur tout les mobiles de la map
	 * TODO : depend des fps ! ! 
	 */
	void deplacerMobiles();

	/**
	 * Fonction ajoutant un mobile à la liste
	 */
	void push_front(Mobile* m);

	/**
	 * Fonction retirant un mobile à la liste en fonction de sa valeur
	 * (retire toutes ses instances s'il est plusieurs fois dans la liste)
	 */
	void remove(Mobile* m);

	/**
	 * Compute the collision of all mobile in the map
	 */
	void computeCollisions(Carte* carte);

	/**
	 * Supprime les mobiles dont la duree de vie est arrivee a 0
	 */
	void supprMobilesMorts();
};

#endif
