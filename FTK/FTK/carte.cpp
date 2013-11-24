#include "carte.h"

#include <math.h>
#include <iostream> //pr les msg d'erreur
#include <time.h>
#include <stdlib.h>

//#define LEAKS // Check les fuites memoires
//#include "leak_detector.h" // traque les fuites memoires


Carte::Carte(int _largx, int _largy, int _hauteur, int _taille_buffer) :
	largx(_largx), largy(_largy), hauteur(_hauteur) , tailleBuffer(_taille_buffer), posBuffer(-1,-1,-1) {
	// Clear les display list
	listNonTransp = 0;
	listTransp = 0;

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
	///////////////////////////////////////////
	// TESTS CONSTRUCTION MAP NON ALEATOIRE////
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
	
	(map[6][6][1]).setType(4);
	(map[6][5][1]).setType(4);
	(map[6][4][1]).setType(4);
	(map[5][6][1]).setType(4);
	(map[5][5][1]).setType(4);
	(map[5][4][1]).setType(4);
	(map[4][6][1]).setType(4);
	(map[4][5][1]).setType(4);
	(map[4][4][1]).setType(4);

	// bord piscine
	(map[7][7][1]).setType(2);
	(map[7][6][1]).setType(2);
	(map[7][5][1]).setType(2);
	(map[7][4][1]).setType(2);
	(map[7][3][1]).setType(2);
	(map[6][7][1]).setType(2);
	(map[5][7][1]).setType(2);
	(map[4][7][1]).setType(2);
	(map[3][7][1]).setType(2);
	(map[3][6][1]).setType(2);
	(map[3][5][1]).setType(2);
	(map[3][4][1]).setType(2);
	(map[3][3][1]).setType(2);
	(map[4][3][1]).setType(2);
	(map[5][3][1]).setType(2);
	(map[6][3][1]).setType(2);
	
	//Maison pour tester ombres
	for (int i = 9; i < 18; i++) {
		for (int j = 9; j < 18; j++) {
			(map[i][j][7]).setType(3);
		}
	}
	for (int i = 10; i < 17; i++) {
		for (int j = 10; j < 17; j++) {
			(map[i][j][8]).setType(3);
		}
	}
	for (int i = 10; i < 17; i++) {
		for (int j = 0; j < 7; j++) {
			(map[10][i][j]).setType(2);
		}
	}
	for (int i = 10; i < 17; i++) {
		for (int j = 0; j < 7; j++) {
			(map[i][10][j]).setType(2);
		}
	}
	for (int i = 10; i < 17; i++) {
		for (int j = 0; j < 7; j++) {
			(map[16][i][j]).setType(2);
		}
	}
	for (int i = 10; i < 17; i++) {
		for (int j = 0; j < 7; j++) {
			(map[i][16][j]).setType(2);
		}
	}

	for (int i = 12; i < 15; i++) {
		for (int j = 1; j < 5; j++) {
			(map[10][i][j]).setType(0);
		}
	}



	///////////////////////////////////
	// Place de l'eau partout        //
	for (int i = 20; i < largx; i++) {
		for (int j = 20; j < largy; j++) {
			(map[i][j][1]).setType(4);
			(map[i][j][2]).setType(4);
		}
	}

	///////////////////////////////////
	// Terrain généré aléatoirement ///

	/*
	 * L'idée ici est de générer des cercles aléatoirement qui vont s'empiler sur la carte
	 * fonction LARGEMENT ameliorable permet d'avoir un rendu agreable.
	 */
	for (int n_cercle = 0; n_cercle < 80; n_cercle ++) {
		//Emplacement du cercle
		int i = (rand()%largx-21)+40;
		int j = (rand()%largx-21)+40;
		//rayon du cercle
		int r = (rand()%10)+5;
		for (int i2=-r; i2<r; i2++) {
			for (int j2=-round(sqrt(r*r-i2*i2)); j2<round(sqrt(r*r-i2*i2)); j2++) {
				int k = 0;
						

				bool continuer = ((i+i2 >= 0) && (i+i2 < largx) && (j+j2 >= 0) && (j+j2 < largy) && (k >= 0) && (k <= hauteur));
				while (continuer) {
					if ((map[i+i2][j+j2][k]).getType() == 1) {
						k++;
					} else {
						break;
					}
					continuer = ( (i+i2 >= 0) && (i+i2 < largx) && (j+j2 >= 0) && ((j+j2) < largy) && (k >= 0) && (k <= hauteur) );
				}
				if((i+i2 >= 0) && (i+i2 < largx) && (j+j2 >= 0) && (j+j2 < largy) && (k >= 0) && (k <= hauteur))
					(map[i+i2][j+j2][k]).setType(1);
						
			}
		}
	}

	/////////////////////////////
	// Mise en place des faces
	for (int i = 0; i < largx; i++) {
		for (int j = 0; j < largy; j++) {
			for (int k = 0; k < hauteur; k++) {

				//CAS DES BLOCS NON-TRANSPARENTS
				if (!map[i][j][k].isTransparent()) {
					//OUEST
					if (i > 0) {
						if (map[i - 1][j][k].isTransparent())
							map[i][j][k].face_ouest = (new Face(false));
					} else {
						map[i][j][k].face_ouest = (new Face(false));
					}

					//EST
					if (i < largx - 1) {
						if (map[i + 1][j][k].isTransparent())
							map[i][j][k].face_est = (new Face(false));
					} else {
						map[i][j][k].face_est = (new Face(false));
					}

					//SUD
					if (j > 0) {
						if (map[i][j - 1][k].isTransparent())
							map[i][j][k].face_sud = (new Face(false));
					} else {
						map[i][j][k].face_sud = (new Face(false));
					}

					//NORD
					if (j < largy - 1) {
						if (map[i][j + 1][k].isTransparent())
							map[i][j][k].face_nord = (new Face(false));
					} else {
						map[i][j][k].face_nord = (new Face(false));
					}

					//BOT
					if (k > 0) {
						if (map[i][j][k - 1].isTransparent())
							map[i][j][k].face_bot = (new Face(false));
					} else {
						map[i][j][k].face_bot = (new Face(false));
					}

					//TOP
					if (k < hauteur - 1) {
						if (map[i][j][k + 1].isTransparent())
							map[i][j][k].face_top = (new Face(false));
					} else {
						map[i][j][k].face_top = (new Face(false));
					}
					// CAS DES BLOCS TRANSPARENTS
				} else {
					int myType = map[i][j][k].getType();
					//OUEST
					if (i > 0) {
						if (map[i - 1][j][k].getType() != myType)
							map[i][j][k].face_ouest = (new Face(false));
					} else {
						map[i][j][k].face_ouest = (new Face(false));
					}

					//EST
					if (i < largx - 1) {
						if (map[i + 1][j][k].getType() != myType)
							map[i][j][k].face_est = (new Face(false));
					} else {
						map[i][j][k].face_est = (new Face(false));
					}

					//SUD
					if (j > 0) {
						if (map[i][j - 1][k].getType() != myType)
							map[i][j][k].face_sud = (new Face(false));
					} else {
						map[i][j][k].face_sud = (new Face(false));
					}

					//NORD
					if (j < largy - 1) {
						if (map[i][j + 1][k].getType() != myType)
							map[i][j][k].face_nord = (new Face(false));
					} else {
						map[i][j][k].face_nord = (new Face(false));
					}

					//BOT
					if (k > 0) {
						if (map[i][j][k - 1].getType() != myType)
							map[i][j][k].face_bot = (new Face(false));
					} else {
						map[i][j][k].face_bot = (new Face(false));
					}

					//TOP
					if (k < hauteur - 1) {
						if (map[i][j][k + 1].getType() != myType)
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
			for (int k = hauteur - 1; k >= 0; k--) {
				// On illumine la partie superieur du cube
				if (map[i][j][k].face_top != NULL)
					map[i][j][k].face_top->setLum(true);

				// On illumine les cubes à coté
				if (i > 0 && map[i - 1][j][k].face_est != NULL)
					map[i - 1][j][k].face_est->setLum(true);
				if (i < largx - 1 && map[i + 1][j][k].face_ouest != NULL)
					map[i + 1][j][k].face_ouest->setLum(true);
				if (j > 0 && map[i][j - 1][k].face_nord != NULL)
					map[i][j - 1][k].face_nord->setLum(true);
				if (j < largy - 1 && map[i][j + 1][k].face_sud != NULL)
					map[i][j + 1][k].face_sud->setLum(true);
				//

				if (!map[i][j][k].isTransparent()) {
					break;
				}

			}
		}
	}
}

Carte::~Carte() {
	for (int i = 0; i < largx; i++) {
		for (int j = 0; j < largy; j++) {
			delete[] map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;

	//On libere les displays listes
	if (listNonTransp != 0)
		glDeleteLists(listNonTransp, 1);
	if (listTransp != 0)
		glDeleteLists(listTransp, 1);
}

void Carte::remplirListNonTransp() {
	//On libere la liste precedente
	if (listNonTransp != 0)
		glDeleteLists(listNonTransp, 1);	

	listNonTransp = glGenLists(1);
	if(listNonTransp == 0) {
		std::cerr << "erreur lors de la creation de la display liste Non Transp" << std::endl;
		exit(-1);
	}
	
	glNewList(listNonTransp, GL_COMPILE); /* start */

	int minX, maxX, minY, maxY, minZ, maxZ;

	minX = std::max(int(posBuffer.X-tailleBuffer/2),0);
	maxX = std::min(int(posBuffer.X+tailleBuffer/2),largx);
	minY = std::max(int(posBuffer.Y-tailleBuffer/2),0);
	maxY = std::min(int(posBuffer.Y+tailleBuffer/2),largy);
	minZ = std::max(int(posBuffer.Z-tailleBuffer/2),0);
	maxZ = std::min(int(posBuffer.Z+tailleBuffer/2),hauteur);

	int x;
	int y;
	int z;
	// dessine les blocs non transparents
	glPushMatrix();
	glTranslatef(minX, minY, minZ);
	for (x = minX; x < maxX; x++) {
		for (y = minY; y < maxY; y++) {
			for (z = minZ; z < maxZ; z++) {
				if ((map[x][y][z]).getType() != 4)
					(map[x][y][z]).afficherBloc();
				glTranslatef(0, 0, 1);
			}
			z = 0;
			glTranslatef(0, 0, -(maxZ-minZ));
			glTranslatef(0, 1, 0);
		}
		y = 0;
		glTranslatef(0, -(maxY-minY), 0);
		glTranslatef(1, 0, 0);
	}

	glPopMatrix();

	glEndList(); /* stop */
}

void Carte::dessinerCarte() {

	glCallList(listNonTransp);

}

void Carte::remplirListTransp() {
	//On libere la liste precedente
	if (listTransp != 0)
		glDeleteLists(listTransp, 1);	

	listTransp = glGenLists(1);
	if(listTransp == 0) {
		std::cerr << "erreur lors de la creation de la display liste Transp" << std::endl;
		exit(-1);
	}
	
	glNewList(listTransp, GL_COMPILE); /* start */

	int minX, maxX, minY, maxY, minZ, maxZ;

	minX = std::max(int(posBuffer.X-tailleBuffer/2),0);
	maxX = std::min(int(posBuffer.X+tailleBuffer/2),largx);
	minY = std::max(int(posBuffer.Y-tailleBuffer/2),0);
	maxY = std::min(int(posBuffer.Y+tailleBuffer/2),largy);
	minZ = std::max(int(posBuffer.Z-tailleBuffer/2),0);
	maxZ = std::min(int(posBuffer.Z+tailleBuffer/2),hauteur);

	int x;
	int y;
	int z;
	// dessine les blocs transparents
	glPushMatrix();
	glTranslatef(minX, minY, minZ);
	for (x = minX; x < maxX; x++) {
		for (y = minY; y < maxY; y++) {
			for (z = minZ; z < maxZ; z++) {
				if ((map[x][y][z]).getType() == 4)
					(map[x][y][z]).afficherBloc();
				glTranslatef(0, 0, 1);
			}
			z = 0;
			glTranslatef(0, 0, -(maxZ-minZ));
			glTranslatef(0, 1, 0);
		}
		y = 0;
		glTranslatef(0, -(maxY-minY), 0);
		glTranslatef(1, 0, 0);
	}

	glPopMatrix();

	glEndList(); /* stop */
}

void Carte::dessinerCarteTransparent() {
	
	glCallList(listTransp);
	
}

void Carte::remplirLists(Vector3D posPerso) {
	bool recharger = false;

	// La premiere fois on charge !
	if (posBuffer.X == -1) {
		recharger = true;
		posBuffer = posPerso;
	}

	if (posPerso.X >= posBuffer.X + tailleBuffer/4) {
		recharger = true;
		posBuffer.X += tailleBuffer/4;
	} else if (posPerso.X <= posBuffer.X - tailleBuffer/4) {
		recharger = true;
		posBuffer.X -= tailleBuffer/4;
	}
	if (posPerso.Y >= posBuffer.Y + tailleBuffer/4) {
		recharger = true;
		posBuffer.Y += tailleBuffer/4;
	} else if (posPerso.Y <= posBuffer.Y - tailleBuffer/4) {
		recharger = true;
		posBuffer.Y -= tailleBuffer/4;
	}
	if (posPerso.Z >= posBuffer.Z + tailleBuffer/4) {
		recharger = true;
		posBuffer.Z += tailleBuffer/4;
	} else if (posPerso.Z <= posBuffer.Z - tailleBuffer/4) {
		recharger = true;
		posBuffer.Z -= tailleBuffer/4;
	}

	// Si necessaire on recharge
	if (recharger) {
		std::cout << "recharg" << std::endl; //TRACAGE
		remplirListNonTransp();
		remplirListTransp();
	}
}

void Carte::modifierBloc(int x, int y, int z, int type) {
	(map[x][y][z]).setType(type);
	
	int minX = std::max(x-1,0);
	int maxX = std::min(x+1,largx);
	int minY = std::max(y-1,0);
	int maxY = std::min(y+1,largy);
	int minZ = std::max(z-1,0);
	int maxZ = std::min(z+1,hauteur);


	//TODO : plein de verif en trop ?
	/////////////////////////////
	// Mise en place des faces
	for (int i = minX; i <= maxX; i++) {
		for (int j = minY; j <= maxY; j++) {
			for (int k = minZ; k <= maxZ; k++) {

				//CAS DES BLOCS NON-TRANSPARENTS
				if (!map[i][j][k].isTransparent()) {
					//OUEST
					if (i > 0) {
						if (map[i - 1][j][k].isTransparent())
							map[i][j][k].face_ouest = (new Face(false));
					} else {
						map[i][j][k].face_ouest = (new Face(false));
					}

					//EST
					if (i < largx - 1) {
						if (map[i + 1][j][k].isTransparent())
							map[i][j][k].face_est = (new Face(false));
					} else {
						map[i][j][k].face_est = (new Face(false));
					}

					//SUD
					if (j > 0) {
						if (map[i][j - 1][k].isTransparent())
							map[i][j][k].face_sud = (new Face(false));
					} else {
						map[i][j][k].face_sud = (new Face(false));
					}

					//NORD
					if (j < largy - 1) {
						if (map[i][j + 1][k].isTransparent())
							map[i][j][k].face_nord = (new Face(false));
					} else {
						map[i][j][k].face_nord = (new Face(false));
					}

					//BOT
					if (k > 0) {
						if (map[i][j][k - 1].isTransparent())
							map[i][j][k].face_bot = (new Face(false));
					} else {
						map[i][j][k].face_bot = (new Face(false));
					}

					//TOP
					if (k < hauteur - 1) {
						if (map[i][j][k + 1].isTransparent())
							map[i][j][k].face_top = (new Face(false));
					} else {
						map[i][j][k].face_top = (new Face(false));
					}
					// CAS DES BLOCS TRANSPARENTS
				} else {
					int myType = map[i][j][k].getType();
					//OUEST
					if (i > 0) {
						if (map[i - 1][j][k].getType() != myType)
							map[i][j][k].face_ouest = (new Face(false));
					} else {
						map[i][j][k].face_ouest = (new Face(false));
					}

					//EST
					if (i < largx - 1) {
						if (map[i + 1][j][k].getType() != myType)
							map[i][j][k].face_est = (new Face(false));
					} else {
						map[i][j][k].face_est = (new Face(false));
					}

					//SUD
					if (j > 0) {
						if (map[i][j - 1][k].getType() != myType)
							map[i][j][k].face_sud = (new Face(false));
					} else {
						map[i][j][k].face_sud = (new Face(false));
					}

					//NORD
					if (j < largy - 1) {
						if (map[i][j + 1][k].getType() != myType)
							map[i][j][k].face_nord = (new Face(false));
					} else {
						map[i][j][k].face_nord = (new Face(false));
					}

					//BOT
					if (k > 0) {
						if (map[i][j][k - 1].getType() != myType)
							map[i][j][k].face_bot = (new Face(false));
					} else {
						map[i][j][k].face_bot = (new Face(false));
					}

					//TOP
					if (k < hauteur - 1) {
						if (map[i][j][k + 1].getType() != myType)
							map[i][j][k].face_top = (new Face(false));
					} else {
						map[i][j][k].face_top = (new Face(false));
					}
				}
			}
		}
	}

	int minX2 = std::max(x-2,0);
	int maxX2 = std::min(x+2,largx);
	int minY2 = std::max(y-2,0);
	int maxY2 = std::min(y+2,largy);

	/////////////////////////////
	// Mise en place de la lumiere
	for (int i = minX2; i < maxX2; i++) {
		for (int j = minY2; j < maxY2; j++) {
			for (int k = hauteur - 1; k >= 0; k--) {
				// On illumine la partie superieur du cube
				if (map[i][j][k].face_top != NULL)
					map[i][j][k].face_top->setLum(true);

				// On illumine les cubes à coté
				if (i > 0 && map[i - 1][j][k].face_est != NULL)
					map[i - 1][j][k].face_est->setLum(true);
				if (i < largx - 1 && map[i + 1][j][k].face_ouest != NULL)
					map[i + 1][j][k].face_ouest->setLum(true);
				if (j > 0 && map[i][j - 1][k].face_nord != NULL)
					map[i][j - 1][k].face_nord->setLum(true);
				if (j < largy - 1 && map[i][j + 1][k].face_sud != NULL)
					map[i][j + 1][k].face_sud->setLum(true);
				//

				if (!map[i][j][k].isTransparent()) {
					break;
				}

			}
		}
	}
}

bool Carte::inBounds(Vector3D v) {
	return (v.X >= 0 && v.X < largx && 
		v.Y >= 0 && v.Y < largy &&
		v.Z >= 0 && v.Z < hauteur);
}

int Carte::getLargx() {
  return largx;
}


int Carte::getLargy() {
  return largy;
}


int Carte::getHauteur() {
  return hauteur;
}
