#include "carte.h"
#include "util_fig.h"  // Juste pour dessiner le perso pour tester
#include <iostream> //pr les msg d'erreur


Carte::Carte(int _largx, int _largy, int _hauteur) : largx(_largx), largy(_largy), hauteur(_hauteur) {
#ifdef DEBUG
  std::cout << "<CONSTRUCTEUR CARTE>" << std::endl; // TRACE
#endif
  ////////////////////////////////////
  // Initilisation d'un tableau 3D
  map = new Bloc**[largx];
  for (int i = 0; i < largx; i++) {
    map[i] = new Bloc*[largy];
    for (int j = 0; j < largy; j++) {
      map[i][j] = new Bloc[hauteur];
      for (int k = 0; k < hauteur; k++) {
	map[i][j][k].setType(0);
      }
    }
  }
  ////////////////////////////////////
  // TESTS CONSTRUCTION MAP //////////
  for (int i = 1; i < largx; i++) {
    for (int j = 1; j < largy; j++) {
      (map[i][j][0]).setType(1);
    }
  }
  for (int i = 1; i < 4; i++) {
    for (int j = 1; j < 4; j++) {
      (map[i][j][3]).setType(3);
    }
  }
  (map[1][1][1]).setType(2);
  (map[1][1][2]).setType(2);

  // eau
  (map[5][5][1]).setType(4);
  (map[5][4][1]).setType(4);
  (map[4][5][1]).setType(4);
  (map[4][4][1]).setType(4);

  // bord piscine
  (map[6][6][1]).setType(2);
  (map[5][6][1]).setType(2);
  (map[4][6][1]).setType(2);
  (map[3][6][1]).setType(2);
  (map[3][5][1]).setType(2);
  (map[3][4][1]).setType(2);
  (map[3][3][1]).setType(2);
  (map[4][3][1]).setType(2);
  (map[5][3][1]).setType(2);
  (map[6][3][1]).setType(2);
  (map[6][4][1]).setType(2);
  (map[6][5][1]).setType(2);
  
  //truc moche en bois pour tester ombres
  for (int i = 10; i < 16; i++) {
    for (int j = 10; j < 16; j++) {
      (map[i][j][10]).setType(3);
    }
  }
  for (int i = 10; i < 16; i++) {
    for (int j = 0; j < 6; j++) {
      (map[10][i][j]).setType(3);
    }
  }
  for (int i = 10; i < 16; i++) {
    for (int j = 0; j < 6; j++) {
      (map[i][10][j]).setType(3);
    }
  }
  for (int i = 10; i < 16; i++) {
    for (int j = 0; j < 6; j++) {
      (map[16][i][j]).setType(3);
    }
  }
  for (int i = 10; i < 16; i++) {
    for (int j = 0; j < 6; j++) {
      (map[i][16][j]).setType(3);
    }
  }

  // truc au fond du truc moche
  (map[14][14][1]).setType(2);
  (map[14][14][2]).setType(2);

  // trou dans un mur
  (map[16][16][2]).setType(0);


  /////////////////////////////
  // Mise en place des faces
   for (int i = 0; i < largx; i++) {
    for (int j = 0; j < largy; j++) {
      for (int k = 0; k < hauteur; k++) {
	
	//CAS DES BLOCS NON-TRANSPARENTS
	if (!map[i][j][k].isTransparent()) { 
	  //OUEST
	  if (i > 0) {
	    if (map[i-1][j][k].isTransparent())
	      map[i][j][k].face_ouest = (new Face(false));
	  } else {
	    map[i][j][k].face_ouest = (new Face(false));
	  }

	  //EST
	  if (i < largx-1) {
	    if (map[i+1][j][k].isTransparent())
	      map[i][j][k].face_est = (new Face(false));
	  } else {
	    map[i][j][k].face_est = (new Face(false));
	  }
	
	  //SUD
	  if (j > 0) {
	    if (map[i][j-1][k].isTransparent())
	      map[i][j][k].face_sud = (new Face(false));
	  } else {
	    map[i][j][k].face_sud = (new Face(false));
	  }

	  //NORD
	  if (j < largy-1) {
	    if (map[i][j+1][k].isTransparent())
	      map[i][j][k].face_nord = (new Face(false));
	  } else {
	    map[i][j][k].face_nord = (new Face(false));
	  }

	  //BOT
	  if (k > 0) {
	    if (map[i][j][k-1].isTransparent())
	      map[i][j][k].face_bot = (new Face(false));
	  } else {
	    map[i][j][k].face_bot = (new Face(false));
	  }

	  //TOP
	  if (k < hauteur-1) {
	    if (map[i][j][k+1].isTransparent())
	      map[i][j][k].face_top = (new Face(false));
	  } else {
	    map[i][j][k].face_top = (new Face(false));
	  }
	  // CAS DES BLOCS TRANSPARENTS
	} else {
	  int myType = map[i][j][k].getType();
	  //OUEST
	  if (i > 0) {
	    if (map[i-1][j][k].getType() != myType)
	      map[i][j][k].face_ouest = (new Face(false));
	  } else {
	    map[i][j][k].face_ouest = (new Face(false));
	  }

	  //EST
	  if (i < largx-1) {
	    if (map[i+1][j][k].getType() != myType)
	      map[i][j][k].face_est = (new Face(false));
	  } else {
	    map[i][j][k].face_est = (new Face(false));
	  }
	
	  //SUD
	  if (j > 0) {
	    if (map[i][j-1][k].getType() != myType)
	      map[i][j][k].face_sud = (new Face(false));
	  } else {
	    map[i][j][k].face_sud = (new Face(false));
	  }

	  //NORD
	  if (j < largy-1) {
	    if (map[i][j+1][k].getType() != myType)
	      map[i][j][k].face_nord = (new Face(false));
	  } else {
	    map[i][j][k].face_nord = (new Face(false));
	  }

	  //BOT
	  if (k > 0) {
	    if (map[i][j][k-1].getType() != myType)
	      map[i][j][k].face_bot = (new Face(false));
	  } else {
	    map[i][j][k].face_bot = (new Face(false));
	  }

	  //TOP
	  if (k < hauteur-1) {
	    if (map[i][j][k+1].getType() != myType)
	      map[i][j][k].face_top = (new Face(false));
	  } else {
	    map[i][j][k].face_top = (new Face(false));
	  }
	}
      }
    }
  }


  /////////////////////////////
  // Mise en place de la lumiere
  for (int i = 0; i < largx; i++) {
    for (int j = 0; j < largy; j++) {
      for (int k = hauteur-1; k >= 0; k--) {
	// On illumine la partie superieur du cube
	if (map[i][j][k].face_top !=NULL)
	  map[i][j][k].face_top->setLum(true);

	// On illumine les cubes à coté
	if (i > 0 && map[i-1][j][k].face_est !=NULL)
	  map[i-1][j][k].face_est->setLum(true);
	if (i < largx-1 && map[i+1][j][k].face_ouest !=NULL)
	  map[i+1][j][k].face_ouest->setLum(true);
	if (j > 0 && map[i][j-1][k].face_nord !=NULL)
	  map[i][j-1][k].face_nord->setLum(true);
	if (j < largy-1 && map[i][j+1][k].face_sud !=NULL)
	  map[i][j+1][k].face_sud->setLum(true);
	//

	if (!map[i][j][k].isTransparent()) {
	  break;
	}
	
      }
    }
  }
}

Carte::~Carte() {
#ifdef DEBUG
  std::cout << "<DESTRUCTEUR CARTE>" << std::endl; // TRACE
#endif
  for (int i = 0; i < largx; i++) {
    for (int j = 0; j < largy; j++) {
      delete [] map[i][j];
    }
    delete [] map[i];
  }
  delete [] map;
}

void Carte::dessinerCarte() {
  int x = 0;
  int y = 0;
  int z = 0;

  for (x = 0; x < largx; x++) {
    for (y = 0; y < largy; y++) {
      for (z = 0; z < hauteur; z++) {
	if ((map[x][y][z]).getType() != 4)
	  (map[x][y][z]).afficherBloc();
	glTranslatef(0,0,1);
      }
      z = 0;
      glTranslatef(0,0,-hauteur);
      glTranslatef(0,1,0);
    }
    y = 0;
    glTranslatef(0,-largy,0);
    glTranslatef(1,0,0);
  }
  glTranslatef(-largx,0,0);

for (x = 0; x < largx; x++) {
    for (y = 0; y < largy; y++) {
      for (z = 0; z < hauteur; z++) {
	if ((map[x][y][z]).getType() == 4)
	  (map[x][y][z]).afficherBloc();
	glTranslatef(0,0,1);
      }
      z = 0;
      glTranslatef(0,0,-hauteur);
      glTranslatef(0,1,0);
    }
    y = 0;
    glTranslatef(0,-largy,0);
    glTranslatef(1,0,0);
  }
  glTranslatef(-largx,0,0);
  
  /*SrcParticules* srcParticules = new SrcParticules();
  srcParticules->update();
  srcParticules->draw();*/
}
