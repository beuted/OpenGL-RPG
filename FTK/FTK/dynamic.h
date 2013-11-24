#ifndef __DYNAMIC_H
#define __DYNAMIC_H

#include <map>

#include "mobile.h"

class Dynamic {

  // stocke les forces sur chaque mobile.
  std::map<const Mobile*, Vector3D> forces;

  // System parameters (common)
  Vector3D gravity;
  double viscosite;
  double dt;			// time step
  bool handleCollisions;
	
  double rebound;	// 0 = pure absorption; 1 = pure elastic impact

  Dynamic();
  ~Dynamic();
  
  void handleCollisions_PersoMap(Mobile* perso, Carte* carte);
  void handleForces_Perso(Mobile* perso);
  
};

#endif
