#ifndef CARTE_H
#define CARTE_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "bloc.h"
#include "vector3d.h"

/**
 * Classe permettant la gestion et la creation de la Map
 *
 */
class Carte {
 public:
  /**
   * Constructeur
   */
	Carte(int _largx, int _largy, int _hauteur, int _taille_buffer);

  /**
   * Destructeur : libere le tab 3D map
   */
  ~Carte();
  
  /**
   * Remplit la Display list des objets non transparents en vu de l'affichage
   */
  void remplirListNonTransp();

  /**
   * Remplit la Display list des objets transparents en vu de l'affichage
   */
  void remplirListTransp();

  /**
   * Remplit les deux listes precedentes en modifiant la position
   * du buffer si necessaire (perso trop proche des bords)
   */
  void remplirLists(Vector3D posPerso);

  /**
   * Cree la map virtuellement dans l'univers
   */ 
  void dessinerCarte();

  /**
   * Cree la map virtuellement dans l'univers
   * pour les blocs transparents
   */
  void dessinerCarteTransparent();

  /**
   * Supprime un bloc de la carte en mettant a jour les faces et la lumiere au voisinage
   */
  void modifierBloc(int x, int y, int z, int type);
  

  /**
   * renvoie true si le vector est dans les limites de la carte false sinon
   */
  
  bool inBounds(Vector3D v);
  
  int getLargx();
  
  int getLargy();

  int getHauteur(); 


  /**
   * renvoi le bloc en position i, j ,k sur la carte
   */
  Bloc & getElemMap(int i, int j, int k) {
    return map[i][j][k];
  }

  Bloc & getElemMap(Vector3D v) {
	  return map[int(v.X)][int(v.Y)][int(v.Z)];
  }

 private:

  /**
   * DisplayList OpenGL des blocs non transparents de la carte
   * (optimisation OpenGL !)
   */
  GLuint listNonTransp;

  /**
   * DisplayList OpenGL des blocs transparents de la carte
   * (optimisation OpenGL !)
   */
  GLuint listTransp;
  /**
   * Dimensions de la carte
   */
  int const largx;
  int const largy;
  int const hauteur;

  /**
   * taille de la zone visible de la carte par le personnage
   */
  int tailleBuffer;

  /**
   * Position du buffer de carte
   */
  Vector3D posBuffer;

  Bloc*** map;
};

#endif //CARTE_H
