#ifndef _PERSONNAGE_
#define _PERSONNAGE_

/**
 * \file personnage.h
 * \brief Classe décrivant un personnage
 *
 * \version 0.1
 * \date 20/02/13
 */

#include <GL/gl.h>
#include <GL/glu.h>

/**
 * \class Personnage personnage.h
 * \brief Décrit un personnage
 */

class Personnage {
  
 private :

  GLfloat position[3];
  
 public :

  /**
   * \brief Constructeur
   *
   * Constructeur d'un personnage
   */
  Personnage();

  /**
   * \brief Destructeur
   *
   * Destructeur d'un personnage
   */
  ~Personnage();

  /**
   * Fonction permettant de charger les textures pour le dessin du personnage
   */
  void chargerTextures();

  /**
   * Fonction dessinant le personnage dans sa position
   */
  void dessinerPerso();
  
};

#endif
