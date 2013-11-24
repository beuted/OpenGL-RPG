#include "personnage.h"
#include "sdlglutils.h"

#include <iostream>

//#include "sdlglutils.h"
//#include "util_fig.h"


/*GLuint text_face[2];
 GLuint text_corps[2];
 GLuint text_default[2];
 GLuint text_bras[2];*/

Personnage::Personnage() :
	Mobile(), forward(), left() {
	phi = 0;
	theta = 0;

	etatMarche = ETAT0;

	speed = 7;
	
	dimension.X = 0.8;
	dimension.Y = 0.8;
	dimension.Z = 2.6;

	direction.X = 0;
	direction.Y = 0;
	direction.Z = 0;

	poids = 67;
}


void Personnage::initialize(Gestion_textures** _gest_text) {
	// Ici on construit le modele de l'objet personnage
	GLfloat position[3] = { 0, 0, 0 };
	GLfloat orientation[3] = { 0, 0, 0 };
	GLfloat dimension[3] = { 0.4,0.8,1.0 };
	GLfloat axe_rotation[3] = { 0.2,0.4,0.6 };

	//Chargement des textures :

	// La tete
	int textTete[6];
	textTete[0] = 19;
	textTete[1] = 19;
	textTete[2] = 19;
	textTete[3] = 19;
	textTete[4] = 19;
	textTete[5] = 19;


	//std::cout<< textTete[1] << std::endl;
	// CONSTRCUTION DU NIVEAU 0

	//Corps
	Brique_gene* b = new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text);
	arbre_briques = b;

	std::vector<Brique_gene*>* parcour;
	parcour = &(arbre_briques->getListSuivants());

	// CONSTRUCTION DU NIVEAU 1

	//Tete
	position[0] = -0.2;
	position[1] = 0;
	position[2] = 1.0;
	axe_rotation[0] = 0.4;
	axe_rotation[1] = 0.4;
	axe_rotation[2] = 0.4;
	dimension[0] = 0.8;
	dimension[1] = 0.8;
	dimension[2] = 0.8;

	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	parcour->push_back(b);
	//parcour = &(parcour->front().getListSuivants());

	//Bras droit haut
	axe_rotation[0] = 0.2;
	axe_rotation[1] = 0.2;
	axe_rotation[2] = 0.4;
	position[0] = 0.05;
	position[1] = -0.4;
	position[2] = 0.4;
	dimension[0] = 0.4;
	dimension[1] = 0.4;
	dimension[2] = 0.6;
	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	parcour->push_back(b);

	//Bras gauche haut
	position[0] = 0.05;
	position[1] = 0.8;
	position[2] = 0.4;
	dimension[0] = 0.4;
	dimension[1] = 0.4;
	dimension[2] = 0.6;
	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	parcour->push_back(b);

	//Bas Corps
	position[0] = 0.0;
	position[1] = 0.0;
	position[2] = -0.2;
	dimension[0] = 0.4;
	dimension[1] = 0.8;
	dimension[2] = 0.2;
	axe_rotation[0] = 0.2;
	axe_rotation[1] = 0.4;
	axe_rotation[2] = 0.1;
	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	parcour->push_back(b);

	// CONSTRUCTION DU NIVEAU 2
	std::vector<Brique_gene*>::iterator it = (parcour->begin());
	// > Tete
	++it;
	// > bras droit haut

	//Bras droit bas
	position[0] = 0;
	position[1] = 0;
	position[2] = -0.6;
	axe_rotation[0] = 0.2;
	axe_rotation[1] = 0.2;
	axe_rotation[2] = 0.4;
	orientation[1] = -40;
	dimension[0] = 0.4;
	dimension[1] = 0.4;
	dimension[2] = 0.6;
	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	(*it)->getListSuivants().push_back(b);

	++it;
	// > bras gauche haut

	//Bras gauche bas
	position[0] = 0;
	position[1] = 0;
	position[2] = -0.6;
	axe_rotation[0] = 0.2;
	axe_rotation[1] = 0.2;
	axe_rotation[2] = 0.4;
	orientation[1] = -40;
	dimension[0] = 0.4;
	dimension[1] = 0.4;
	dimension[2] = 0.6;
	b = new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text);
	(*it)->getListSuivants().push_back(b);
	
	++it;
	// > Bas corps >>>>>>>>>>>>>>>>>>>>>>>>>>

	// > jambe droite haut
	position[0] = 0;
	position[1] = 0.0;
	position[2] = -0.6;
	axe_rotation[0] = 0.2;
	axe_rotation[1] = 0.2;
	axe_rotation[2] = 0.4;
	dimension[0] = 0.4;
	dimension[1] = 0.4;
	dimension[2] = 0.6;
	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	(*it)->getListSuivants().push_back(b);

	// > jambe gauche haut
	position[0] = 0;
	position[1] = 0.4;
	position[2] = -0.6;
	axe_rotation[0] = 0.2;
	axe_rotation[1] = 0.2;
	axe_rotation[2] = 0.4;
	dimension[0] = 0.4;
	dimension[1] = 0.4;
	dimension[2] = 0.6;
	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	(*it)->getListSuivants().push_back(b);

	std::vector<Brique_gene*>::iterator it_bas_corps = (*it)->getListSuivants().begin();

	//Jambe droite bas
	position[0] = 0;
	position[1] = 0;
	position[2] = -0.6;
	axe_rotation[0] = 0.2;
	axe_rotation[1] = 0.2;
	axe_rotation[2] = 0.4;
	orientation[1] = 40;
	dimension[0] = 0.4;
	dimension[1] = 0.4;
	dimension[2] = 0.6;
	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	(*it_bas_corps)->getListSuivants().push_back(b);

	++it_bas_corps;

	//Jambe gauche bas
	position[0] = 0;
	position[1] = 0;
	position[2] = -0.6;
	axe_rotation[0] = 0.2;
	axe_rotation[1] = 0.2;
	axe_rotation[2] = 0.4;
	orientation[1] = 0;
	dimension[0] = 0.4;
	dimension[1] = 0.4;
	dimension[2] = 0.6;
	b = (new Brique(dimension, position, orientation, axe_rotation, textTete, _gest_text));
	(*it_bas_corps)->getListSuivants().push_back(b);

	// Position INITIALE du personnage
	this->position.X = 8;
	this->position.Y = 8;
	this->position.Z = 10;	
}

void Personnage::deplacer(Uint32 timestep) {
  position += direction * timestep;
}


void Personnage::marcher(double vitesse) {
  //On se positionne sur le bras droit
  std::vector<Brique_gene*> *niv_1 = &(arbre_briques->getListSuivants());
  std::vector<Brique_gene*> *niv_2 = &((*niv_1)[3]->getListSuivants());

  // dirige le bassin vers la direction du vecteur direction
  int angle = direction.horizontalAngle(forward);
  if (angle > 90)
	  angle -= 180;
  else if(angle < -90 )
  angle += 180;
  (*niv_1)[3]->orientation[2] = angle;

  // On preprend la marche
  if(etatMarche == ETAT0) {
    //preparation des bras
      (*niv_1)[1]->orientation[1] = 0;
      (*niv_1)[2]->orientation[1] = 0;
      (*niv_1)[1]->getListSuivants()[0]->orientation[1] = -40;
      (*niv_1)[2]->getListSuivants()[0]->orientation[1] = -40;
      (*niv_2)[0]->orientation[1] = 0;
      (*niv_2)[1]->orientation[1] = 0;
      (*niv_2)[0]->getListSuivants()[0]->orientation[1] = 40;
      (*niv_2)[1]->getListSuivants()[0]->orientation[1] = 0;
      
      etatMarche = ETAT1;
  }

  switch(etatMarche) {
  case ETAT1 : 
    //BRAS HAUT
    (*niv_1)[1]->orientation[1] += 2*vitesse;
    (*niv_1)[2]->orientation[1] -= 2*vitesse;
    //BRAS BAS
    (*niv_1)[1]->getListSuivants()[0]->orientation[1] += 2*vitesse;
    (*niv_1)[2]->getListSuivants()[0]->orientation[1] -= 2*vitesse;
    //JAMBES HAUT
    (*niv_2)[0]->orientation[1] -= 2*vitesse;
    (*niv_2)[1]->orientation[1] += 2*vitesse;
    //JAMBES BAS
    (*niv_2)[0]->getListSuivants()[0]->orientation[1] += 2*vitesse;
    if ((*niv_1)[1]->orientation[1] >= 0)
      etatMarche = ETAT2;
    break;
  case ETAT2 :
    //BRAS HAUT
    (*niv_1)[1]->orientation[1] += 2*vitesse;
    (*niv_1)[2]->orientation[1] -= 2*vitesse;
    //BRAS BAS
    (*niv_1)[1]->getListSuivants()[0]->orientation[1] += 2*vitesse;
    (*niv_1)[2]->getListSuivants()[0]->orientation[1] -= 2*vitesse;
    //JAMBES HAUT
    (*niv_2)[0]->orientation[1] -= 2*vitesse;
    (*niv_2)[1]->orientation[1] += 2*vitesse;
    //JAMBES BAS
    (*niv_2)[0]->getListSuivants()[0]->orientation[1] -= 2*vitesse;
    if ((*niv_1)[1]->orientation[1] >= 40)
      etatMarche = ETAT3;
    break;
  case ETAT3 :
    //BRAS HAUT
    (*niv_1)[1]->orientation[1] -= 2*vitesse;
    (*niv_1)[2]->orientation[1] += 2*vitesse;
     //BRAS BAS
    (*niv_1)[1]->getListSuivants()[0]->orientation[1] -= 2*vitesse;
    (*niv_1)[2]->getListSuivants()[0]->orientation[1] += 2*vitesse;
    //JAMBES HAUT
    (*niv_2)[0]->orientation[1] += 2*vitesse;
    (*niv_2)[1]->orientation[1] -= 2*vitesse;
    //JAMBES BAS
    (*niv_2)[1]->getListSuivants()[0]->orientation[1] += 2*vitesse;
    if ((*niv_1)[1]->orientation[1] <= 0)
      etatMarche = ETAT4;
    break;
  case ETAT4 :
     //BRAS HAUT
    (*niv_1)[1]->orientation[1] -= 2*vitesse;
    (*niv_1)[2]->orientation[1] += 2*vitesse;
     //BRAS BAS
    (*niv_1)[1]->getListSuivants()[0]->orientation[1] -= 2*vitesse;
    (*niv_1)[2]->getListSuivants()[0]->orientation[1] += 2*vitesse;
    //JAMBES HAUT
    (*niv_2)[0]->orientation[1] += 2*vitesse;
    (*niv_2)[1]->orientation[1] -= 2*vitesse;
    //JAMBES BAS
    (*niv_2)[1]->getListSuivants()[0]->orientation[1] -= 2*vitesse;
    if ((*niv_1)[1]->orientation[1] <= -40)
      etatMarche = ETAT1;
    break;
    }
  
     
}

void Personnage::stopper() {

  std::vector<Brique_gene*> *niv_1 = &(arbre_briques->getListSuivants());
  std::vector<Brique_gene*> *niv_2 = &((*niv_1)[3]->getListSuivants());

  // BASSIN
  if ((*niv_1)[3]->orientation[2] < 0)
	  (*niv_1)[3]->orientation[2] += 2;
  else if ((*niv_1)[3]->orientation[2] > 0)
	  (*niv_1)[3]->orientation[2] -= 2;

  //BRAS HAUT
  if ((*niv_1)[1]->orientation[1] > 0)
    (*niv_1)[1]->orientation[1] -- ;
  else if ((*niv_1)[1]->orientation[1] < 0)
    (*niv_1)[1]->orientation[1] ++ ;

  if ((*niv_1)[2]->orientation[1] > 0)
    (*niv_1)[2]->orientation[1] -- ;
  else if ((*niv_1)[2]->orientation[1] < 0)
    (*niv_1)[2]->orientation[1] ++ ;

  //BRAS BAS
  if ((*niv_1)[1]->getListSuivants()[0]->orientation[1] > 0)
    (*niv_1)[1]->getListSuivants()[0]->orientation[1] --;
  else if ((*niv_1)[1]->getListSuivants()[0]->orientation[1] < 0)
    (*niv_1)[1]->getListSuivants()[0]->orientation[1] ++;
  
  if ((*niv_1)[2]->getListSuivants()[0]->orientation[1] > 0)
    (*niv_1)[2]->getListSuivants()[0]->orientation[1] --;
  else if ((*niv_1)[2]->getListSuivants()[0]->orientation[1] < 0)
    (*niv_1)[2]->getListSuivants()[0]->orientation[1] ++;

  //JAMBES HAUT
  if ((*niv_2)[0]->orientation[1] > 0)
    (*niv_2)[0]->orientation[1] -- ;
  else if ((*niv_2)[0]->orientation[1] < 0)
    (*niv_2)[0]->orientation[1] ++ ;

  if ((*niv_2)[1]->orientation[1] > 0)
    (*niv_2)[1]->orientation[1] -- ;
  else if ((*niv_2)[1]->orientation[1] < 0)
    (*niv_2)[1]->orientation[1] ++ ;

  //JAMBES BAS
  if ((*niv_2)[0]->getListSuivants()[0]->orientation[1] > 0)
    (*niv_2)[0]->getListSuivants()[0]->orientation[1] --;
  else if ((*niv_2)[0]->getListSuivants()[0]->orientation[1] < 0)
    (*niv_2)[0]->getListSuivants()[0]->orientation[1] ++;

  if ((*niv_2)[1]->getListSuivants()[0]->orientation[1] > 0)
    (*niv_2)[1]->getListSuivants()[0]->orientation[1] --;
  else if ((*niv_2)[1]->getListSuivants()[0]->orientation[1] < 0)
    (*niv_2)[1]->getListSuivants()[0]->orientation[1] ++;
  
    etatMarche = ETAT0;
}

Personnage::~Personnage() {
	//delete &position;
}
