#ifndef BLOC_H
#define BLOC_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "face.h"

/**
 * \class Bloc : classe représentant un bloc sur la carte (vide ou non)
 */
class Bloc {
 public:

  /**
   * Constructeurs
   */
  Bloc(int _type, Face* _face_top, Face* _face_bot, Face* _face_sud, Face* _face_nord, Face* _face_ouest, Face* _face_est);

  Bloc();

  /**
   * Destructeur
   */
  ~Bloc();

  /**
   * Affiche le bloc avec ses caractéristiques
   */
  void afficherBloc();

  /**
   * Indique si le bloc est transparent (depends de l'enum de type)
   */
  bool isTransparent();

  /**
   * Getters :
   */
  int getType() const {return type;};

  /**
   * Setters :
   */
  void setType(int _type) {type = _type;}

  // faces
  Face* face_top;
  Face* face_bot;
  Face* face_sud;
  Face* face_nord;
  Face* face_est;
  Face* face_ouest;

 private:
  int type; // Il faudrait faire un enum de types

};


#endif //BLOC_H
