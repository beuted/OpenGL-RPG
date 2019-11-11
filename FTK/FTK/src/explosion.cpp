#include "explosion.h"
#include "brique_particulaire.h"

Explosion::Explosion(Vector3D _position, Vector3D _direction, double _speed) : Mobile(_position, Vector3D(0,0,0), Vector3D(0,0,0), _direction, _speed) {
	duree_vie = 10;
	poids = 0.0; // poids nul par défaut
	GLfloat position[3] = { 0, 0, 0 };
	GLfloat orientation[3] = { 0, 0, 0 };
	GLfloat dimension[3] = { 1.0,1.0,1.0 };
	GLfloat axe_rotation[3] = { 0.5,0.5,0.5};
	direction = _direction;
		
	Brique_particulaire* b = new Brique_particulaire(dimension, position, orientation, axe_rotation,3);
	arbre_briques = b;
}

// TODO : A AMELIORER AC COLLISION PONCTUELLE CARTE !
bool Explosion::collision(Carte* carte, Vector3D* &v) {

	if (position.X < 0 || position.X > carte->getLargx() ||
	    position.Y < 0 || position.Y > carte->getLargy() ||
	    position.Z < 0 || position.Z > carte->getHauteur() )
		return true;

	return false;
}
