#include "personnage.h"
//#include "sdlglutils.h"
#include "util_fig.h"

GLuint text_face[2];
GLuint text_corps[2];
GLuint text_default[2];
GLuint text_bras[2];

Personnage::Personnage() {
  for (int i=0; i < 3; i++)
    position[i] = 2.0f;
}

Personnage::~Personnage() {
  delete [] position ;
}

void Personnage::chargerTextures() {
   /* TEXTURES PERSO */
}

void Personnage::dessinerPerso() {

  glTranslatef(position[0],position[1], position[2]);

  glPushMatrix(); 

  //Tete
  dessinerRectangle(1,1,1, text_face);

  glTranslatef(0.15,-0.25,-2);
  //Corps
  glPushMatrix();
  dessinerRectangle(0.7,1.5,2,text_corps); 
  glTranslatef(0,0,-1.5);
  //Jambe gauche
  dessinerRectangle(0.7,0.7,1.5,text_default);
  glTranslatef(0,0.8,0);
  //Jambe droite
  dessinerRectangle(0.7,0.7,1.5,text_default);
  glTranslatef(0,0.8,0);
  glPopMatrix();
  //Bras droit
  glTranslatef(0.15,-0.65,-1.6);
  dessinerRectangle(0.6,0.4,1.5,text_bras);
  //Bras gauche
  glTranslatef(0,1.9,0);
  dessinerRectangle(0.6,0.4,1.5,text_bras);


  glPopMatrix();
}
