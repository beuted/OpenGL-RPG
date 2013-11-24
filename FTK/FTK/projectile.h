#ifndef _PROJECTILE_
#define _PROJECTILE_

/**
 * \file projectile.h
 * \brief Classe décrivant un projectile
 *
 * \version 0.1
 * \date 20/02/13
 */

#include "mobile.h"

class Projectile: public Mobile {

 public:
	
	Projectile(Vector3D _position, Vector3D _direction, double _speed);

	/**
	 * Fonction de collision renvoi true si la collision a lieu
	 * \param v : bloc rencontré (en cas de collision)
	 */
	bool collision(Carte* carte, Vector3D* &v);

	
};

#endif
