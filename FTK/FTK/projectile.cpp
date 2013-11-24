#include "projectile.h"
#include "brique_particulaire.h"

#include <math.h>

Projectile::Projectile(Vector3D _position, Vector3D _direction, double _speed) : Mobile(_position, Vector3D(0,0,0), Vector3D(0,0,0), _direction, _speed) {
	duree_vie == 200;
	poids = 0.0; // poids nul par défaut
	GLfloat position[3] = { 0, 0, 0 };
	GLfloat orientation[3] = { 0, 0, 0 };
	GLfloat dimension[3] = { 1.0,1.0,1.0 };
	GLfloat axe_rotation[3] = { 0.5,0.5,0.5};
	direction = _direction;
		
	Brique_particulaire* b = new Brique_particulaire(dimension, position, orientation, axe_rotation, 1);
	arbre_briques = b;

	std::vector<Brique_gene*>* parcour;
	parcour = &(arbre_briques->getListSuivants());

	// corps dur
	position[0] = -0.15;
	position[1] = -0.15;
	position[2] = -0.15;
	axe_rotation[0] = 0.15;
	axe_rotation[1] = 0.15;
	axe_rotation[2] = 0.15;
	dimension[0] = 0.3;
	dimension[1] = 0.3;
	dimension[2] = 0.3;

	Brique* b2 = (new Brique(dimension, position, orientation, axe_rotation, NULL, NULL));
	parcour->push_back(b2);
}

// TODO : A AMELIORER AC COLLISION PONCTUELLE CARTE !
bool Projectile::collision(Carte* carte, Vector3D* &v) {

	if (position.X < 0 || position.X >= carte->getLargx()-1 ||
	    position.Y < 0 || position.Y >= carte->getLargy()-1 ||
	    position.Z < 0 || position.Z >= carte->getHauteur()-1 ) {
		v = NULL;
		return true;
	}
	if (carte->getElemMap(int(position.X), int(position.Y), int(position.Z)).getType() != 0) {
		v = new Vector3D(int(position.X),int(position.Y), int(position.Z));
		return true;
	}
	v = NULL;
	return false;
}
