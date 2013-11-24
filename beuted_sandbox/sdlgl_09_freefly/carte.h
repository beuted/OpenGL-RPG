#ifndef CARTE_H
#define CARTE_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "bloc.h"

/**
 * Classe permettant la gestion et la creation de la Map
 *
 */
class Carte {
 public:
  /**
   * Constructeur
   */
  Carte(int _largx, int _largy, int _hauteur);

  /**
   * Destructeur : libere le tab 3D map
   */
  ~Carte();

  /**
   * Cree la map virtuellement dans l'univers
   */ 
  void dessinerCarte();

 private:
  int const largx;
  int const largy;
  int const hauteur;
  Bloc*** map;
};

#endif //CARTE_H
