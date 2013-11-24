#include "bloc.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "sdlglutils.h"
#include "gestion_textures.h"

Gestion_textures* gest_text;

void chargerTextures() {

  gest_text = new Gestion_textures();
}

void supprimerTextures() {
	delete gest_text;
}

void dessinerCarre(const Bloc &bloc) {

  //différents paramètres
  float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float scolor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  float tcolor[] = { 1.0f, 1.0f, 1.0f, 0.6f };

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scolor);

  switch (bloc.getType()) {
  case 1 : // herbe
    glBindTexture(GL_TEXTURE_2D, gest_text->getTexture(14));
    glBegin(GL_QUADS);
    break;
  case 2 : // BRICK
    glBindTexture(GL_TEXTURE_2D, gest_text->getTexture(7));
    glBegin(GL_QUADS);
    break;
  case 3 : //BOIS
    glBindTexture(GL_TEXTURE_2D, gest_text->getTexture(8));
    glBegin(GL_QUADS);
    break;
  case 4 : //EAU
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glDepthMask(GL_FALSE); // IMPORTANT LORSQU'ON TRACE DES TRANSPARENCES
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //glColor4fv(tcolor);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, gest_text->getTexture(15));
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tcolor);
    glBegin(GL_QUADS);
 
    break;
  }

  // Cas des blocs opaques
  if (!bloc.isTransparent()) {

    // NORD
    if (bloc.face_nord !=NULL) {
      if (bloc.face_nord->getLum())
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

      glNormal3f(0, 1, 0);
      glTexCoord2d(1,1);  glVertex3d(1,1,1);
      glTexCoord2d(1,0);  glVertex3d(1,1,0);
      glTexCoord2d(0,0);  glVertex3d(0,1,0);
      glTexCoord2d(0,1);  glVertex3d(0,1,1);

      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scolor);
    }

    // EST
    if (bloc.face_est !=NULL) {
      if (bloc.face_est->getLum())
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

      glNormal3f(1, 0, 0);
      glTexCoord2d(0,1);  glVertex3d(1,0,1);
      glTexCoord2d(0,0);  glVertex3d(1,0,0);
      glTexCoord2d(1,0);  glVertex3d(1,1,0);
      glTexCoord2d(1,1);  glVertex3d(1,1,1);

      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scolor);
    }

    // SUD
    if (bloc.face_sud !=NULL) {
      if (bloc.face_sud->getLum())
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

      glNormal3f(0, -1, 0);
      glTexCoord2d(0,1);  glVertex3d(0,0,1);
      glTexCoord2d(0,0);  glVertex3d(0,0,0);
      glTexCoord2d(1,0);  glVertex3d(1,0,0);
      glTexCoord2d(1,1);  glVertex3d(1,0,1);

      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scolor);
    }

    // OUEST
    if (bloc.face_ouest !=NULL) {
      if (bloc.face_ouest->getLum())
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

      glNormal3f(-1, 0, 0);
      glTexCoord2d(1,1);  glVertex3d(0,1,1);
      glTexCoord2d(1,0);  glVertex3d(0,1,0);
      glTexCoord2d(0,0);  glVertex3d(0,0,0);
      glTexCoord2d(0,1);  glVertex3d(0,0,1);
 
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scolor);
    }

    //BOT
    if (bloc.face_bot !=NULL) {

      glNormal3f(0, 0, -1);
      glTexCoord2d(1,1);  glVertex3d(1,1,0);
      glTexCoord2d(1,0);  glVertex3d(1,0,0);
      glTexCoord2d(0,0);  glVertex3d(0,0,0);
      glTexCoord2d(0,1);  glVertex3d(0,1,0);

      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scolor);
    } 

    //TOP
    if (bloc.face_top !=NULL) {
      if (bloc.face_top->getLum())
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

      glNormal3f(0, 0, 1);
      glTexCoord2d(1,0);  glVertex3d(1,0,1);
      glTexCoord2d(1,1);  glVertex3d(1,1,1);
      glTexCoord2d(0,1);  glVertex3d(0,1,1);
      glTexCoord2d(0,0);  glVertex3d(0,0,1);

      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scolor);
    }

    glEnd();
  
    // Cas des blocs transparents
  } else {

    //glBegin(GL_QUADS);
    // NORD
    if (bloc.face_nord != NULL) {
      glNormal3f(0, 1, 0);
      glTexCoord2d(1,1);  glVertex3d(1,1,1);
      glTexCoord2d(1,0);  glVertex3d(1,1,0);
      glTexCoord2d(0,0);  glVertex3d(0,1,0);
      glTexCoord2d(0,1);  glVertex3d(0,1,1);
    }

    // EST
    if (bloc.face_est != NULL) {
      glNormal3f(1, 0, 0);
      glTexCoord2d(0,1);  glVertex3d(1,0,1);
      glTexCoord2d(0,0);  glVertex3d(1,0,0);
      glTexCoord2d(1,0);  glVertex3d(1,1,0);
      glTexCoord2d(1,1);  glVertex3d(1,1,1);
    }
 
    // SUD
    if (bloc.face_sud != NULL) {
      glNormal3f(0, -1, 0);
      glTexCoord2d(0,1);  glVertex3d(0,0,1);
      glTexCoord2d(0,0);  glVertex3d(0,0,0);
      glTexCoord2d(1,0);  glVertex3d(1,0,0);
      glTexCoord2d(1,1);  glVertex3d(1,0,1);
    }
      
    // OUEST
    if (bloc.face_ouest != NULL) {
      glNormal3f(-1, 0, 0);
      glTexCoord2d(1,1);  glVertex3d(0,1,1);
      glTexCoord2d(1,0);  glVertex3d(0,1,0);
      glTexCoord2d(0,0);  glVertex3d(0,0,0);
      glTexCoord2d(0,1);  glVertex3d(0,0,1);
    }

    // BOT
    if (bloc.face_bot != NULL) {
      glNormal3f(0, 0, -1);
      glTexCoord2d(1,1);  glVertex3d(1,1,0);
      glTexCoord2d(1,0);  glVertex3d(1,0,0);
      glTexCoord2d(0,0);  glVertex3d(0,0,0);
      glTexCoord2d(0,1);  glVertex3d(0,1,0);
    }

    // TOP
    if (bloc.face_top != NULL) {
      glNormal3f(0, 0, 1);
      glTexCoord2d(1,0);  glVertex3d(1,0,1);
      glTexCoord2d(1,1);  glVertex3d(1,1,1);
      glTexCoord2d(0,1);  glVertex3d(0,1,1);
      glTexCoord2d(0,0);  glVertex3d(0,0,1);
    }
   
    glEnd();

    glDepthMask(GL_TRUE); // IDEM	
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);

  }
}

// IDEE : Faire une structure pour les tab de textures ac nb de textures

void dessinerRectangle(float a, float b, float c, GLuint* textures) {
  float scolor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLubyte shiny_obj = 50;// Sert a adoucir la transition eclairé/pas eclairé 96

  GLUquadric* params;

  params = gluNewQuadric();
  gluQuadricTexture(params,GL_TRUE);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scolor);
  glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);

  //glGenTextures(2,textures);

  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glBegin(GL_POLYGON);
  glNormal3f(1, 0, 0);
  glTexCoord2d(0,1);  glVertex3d(a,0,c);
  glTexCoord2d(0,0);  glVertex3d(a,0,0);
  glTexCoord2d(1,0);  glVertex3d(a,b,0);
  glTexCoord2d(1,1);  glVertex3d(a,b,c);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glBegin(GL_POLYGON);
  glNormal3f(0, 1, 0);
  glTexCoord2d(1,1);  glVertex3d(a,b,c);
  glTexCoord2d(1,0);  glVertex3d(a,b,0);
  glTexCoord2d(0,0);  glVertex3d(0,b,0);
  glTexCoord2d(0,1);  glVertex3d(0,b,c);
  glEnd();


  glBegin(GL_POLYGON);
  glNormal3f(0, -1, 0);
  glTexCoord2d(0,1);  glVertex3d(0,0,c);
  glTexCoord2d(0,0);  glVertex3d(0,0,0);
  glTexCoord2d(1,0);  glVertex3d(a,0,0);
  glTexCoord2d(1,1);  glVertex3d(a,0,c);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glTexCoord2d(1,1);  glVertex3d(0,b,c);
  glTexCoord2d(1,0);  glVertex3d(0,b,0);
  glTexCoord2d(0,0);  glVertex3d(0,0,0);
  glTexCoord2d(0,1);  glVertex3d(0,0,c);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, 0, -1);
  glTexCoord2d(1,1);  glVertex3d(a,b,0);
  glTexCoord2d(1,0);  glVertex3d(a,0,0);
  glTexCoord2d(0,0);  glVertex3d(0,0,0);
  glTexCoord2d(0,1);  glVertex3d(0,b,0);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(0, 0, 1);
  glTexCoord2d(1,0);  glVertex3d(a,0,c);
  glTexCoord2d(1,1);  glVertex3d(a,b,c);
  glTexCoord2d(0,1);  glVertex3d(0,b,c);
  glTexCoord2d(0,0);  glVertex3d(0,0,c);   
  glEnd();

}
