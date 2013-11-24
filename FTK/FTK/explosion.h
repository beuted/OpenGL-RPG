#ifndef _EXPLOSION_
#define _EXPLOSION_

/**
 * \file projectile.h
 * \brief Classe décrivant une explosion
 *
 * \version 0.1
 * \date 20/02/13
 */

#include "mobile.h"

class Explosion: public Mobile {

 public:
	
	Explosion(Vector3D _position, Vector3D _direction, double _speed);

	/**
	 * Fonction de collision renvoie true si la collision a lieu
	 */
	bool collision(Carte* carte, Vector3D* &v);

	
};

#endif
