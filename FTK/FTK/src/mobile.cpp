/*
 * mobile.cpp
 *
 *  Created on: 11 mars 2013
 *      Author: benoit
 */
#include <vector>

#include "mobile.h"

#include <stdio.h>  //TRACAGE
#include <iostream> //TRACAGE
void Mobile::dessinerMobile() {
	//TODO : devrait dependre des fps !
	if (duree_vie > 0)
		duree_vie--;
	glPushMatrix();

	glTranslatef(position.X, position.Y, position.Z);

	glRotatef(orientation.X, 1, 0, 0);
	glRotatef(orientation.Y, 0, 1, 0);
	glRotatef(orientation.Z, 0, 0, 1);

	//dessine le premier element de l'arbre
	arbre_briques->dessinerBrique();
	//dessine le reste de l'arbre
	arbre_briques->dessinerBriqueRec();

	glPopMatrix();
}

void Mobile::deplacerMobile() {
	position.X += direction.X*speed;
	position.Y += direction.Y*speed;
	position.Z += direction.Z*speed;
}

bool Mobile::collisionModeleToBloc(int i, int j, int k) {
  
  return hitbox->collisionArbreBriquesToBloc(i,j,k);
}
