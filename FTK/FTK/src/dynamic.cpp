#include "mobile.h"
#include "personnage.h"
#include "dynamic.h"

Dynamic::Dynamic() {
  gravity = {0.0, 0.0, -9.81};
  viscosite = 1.0;
  dt = 1/60; // fps
  handleCollisions = true;

  rebound = 0.7;
}

Dynamic::~Dynamic() {
}

void Dynamic::handleCollisions_PersoMap(Mobile* perso, Carte* carte) {
}
