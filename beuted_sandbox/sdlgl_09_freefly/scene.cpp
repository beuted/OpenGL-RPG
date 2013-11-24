#include "scene.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "sdlglutils.h"

void roquette();
void caisse();

void maisonde42();
void jardindeDeadMaster();

GLuint texture[19];

void chargerTextures()
{
    texture[0] = loadTexture("metal091.jpg");
    //pour la roquette
    texture[1] = loadTexture("rocket_motor.jpg");
    texture[2] = loadTexture("rocket_bottom.jpg");
    texture[3] = loadTexture("rocket_middle.jpg");
    texture[4] = loadTexture("rocket_top.jpg");
    //autre texture
    texture[5] = loadTexture("concrete001.jpg");
    texture[6] = loadTexture("floor032.jpg");
    texture[7] = loadTexture("brick009.jpg");
    texture[8] = loadTexture("wood002.jpg");
    texture[9] = loadTexture("wood006.jpg");
    //porte
    texture[10] = loadTexture("door009.jpg");
    //pour les caisse
    texture[11] = loadTexture("crate03.jpg");
    //toit
    texture[12] = loadTexture("roof05.jpg");
    //fenetre
    texture[13] = loadTexture("window031_alpha.png");
    //Herbe
    texture[14] = loadTexture("veg008.jpg");
    //Eau de la piscine
    texture[15] = loadTexture("eau.jpg");
    // Dalle de la piscine
    texture[16] = loadTexture("floor006b.jpg");
    // Fond du puit
    texture[17] = loadTexture("veg010.jpg");
    // puit
    texture[18] = loadTexture("brick077.jpg");
}

void dessinerScene()
{
    maisonde42();
    jardindeDeadMaster();
}

void maisonde42()
{
    GLUquadric* params;
    params = gluNewQuadric();
    gluQuadricTexture(params,GL_TRUE);

    // sol
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glBegin(GL_QUADS);
    glTexCoord2d(-5,10);
    glVertex3d(-5,10,0);
    glTexCoord2d(-5,-5);
    glVertex3d(-5,-5,0);
    glTexCoord2d(5,-5);
    glVertex3d(5,-5,0);
    glTexCoord2d(5,10);
    glVertex3d(5,10,0);
    glEnd();

    //mur droite
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2d(11,0);
    glVertex3d(-5,6,0);
    glTexCoord2d(0,0);
    glVertex3d(-5,-5,0);
    glTexCoord2d(0,5);
    glVertex3d(-5,-5,5);
    glTexCoord2d(11,5);
    glVertex3d(-5,6,5);

    glTexCoord2d(1,0);
    glVertex3d(-5,10,0);
    glTexCoord2d(0,0);
    glVertex3d(-5,9,0);
    glTexCoord2d(0,5);
    glVertex3d(-5,9,5);
    glTexCoord2d(1,5);
    glVertex3d(-5,10,5);

    glTexCoord2d(3,0);
    glVertex3d(-5,9,5);
    glTexCoord2d(0,0);
    glVertex3d(-5,6,5);
    glTexCoord2d(0,0.5);
    glVertex3d(-5,6,4.5);
    glTexCoord2d(3,0.5);
    glVertex3d(-5,9,4.5);

    glTexCoord2d(3,0);
    glVertex3d(-5,9,1.5);
    glTexCoord2d(0,0);
    glVertex3d(-5,6,1.5);
    glTexCoord2d(0,1.5);
    glVertex3d(-5,6,0);
    glTexCoord2d(3,1.5);
    glVertex3d(-5,9,0);
    glEnd();



    //mur face (trou pour porte)
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2d(0,5);
    glVertex3d(-5,-5,0);
    glTexCoord2d(0,0);
    glVertex3d(-5,-5,5);
    glTexCoord2d(2,0);
    glVertex3d(-3,-5,5);
    glTexCoord2d(2,5);
    glVertex3d(-3,-5,0);

    glTexCoord2d(0,5);
    glVertex3d(-1,-5,0);
    glTexCoord2d(0,0);
    glVertex3d(-1,-5,5);
    glTexCoord2d(6,0);
    glVertex3d(5,-5,5);
    glTexCoord2d(6,5);
    glVertex3d(5,-5,0);

    glTexCoord2d(0,1);
    glVertex3d(-3,-5,4);
    glTexCoord2d(0,0);
    glVertex3d(-3,-5,5);
    glTexCoord2d(2,0);
    glVertex3d(-1,-5,5);
    glTexCoord2d(2,1);
    glVertex3d(-1,-5,4);

    glEnd();

    //mur gauche
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex3d(5,-5,0);
    glTexCoord2d(3.5,0);
    glVertex3d(5,-1.5,0);
    glTexCoord2d(3.5,5);
    glVertex3d(5,-1.5,5);
    glTexCoord2d(0,5);
    glVertex3d(5,-5,5);

    glTexCoord2d(3,0);
    glVertex3d(5,-1.5,5);
    glTexCoord2d(0,0);
    glVertex3d(5,1.5,5);
    glTexCoord2d(0,0.5);
    glVertex3d(5,1.5,4.5);
    glTexCoord2d(3,0.5);
    glVertex3d(5,-1.5,4.5);

    glTexCoord2d(3,1.5);
    glVertex3d(5,-1.5,0);
    glTexCoord2d(0,1.5);
    glVertex3d(5,1.5,0);
    glTexCoord2d(0,0);
    glVertex3d(5,1.5,1.5);
    glTexCoord2d(3,0);
    glVertex3d(5,-1.5,1.5);

    glTexCoord2d(0,0);
    glVertex3d(5,1.5,0);
    glTexCoord2d(8.5,0);
    glVertex3d(5,10,0);
    glTexCoord2d(8.5,5);
    glVertex3d(5,10,5);
    glTexCoord2d(0,5);
    glVertex3d(5,1.5,5);
    glEnd();


    //porte milieu
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glBegin(GL_QUADS);
    glTexCoord2d(0,5);
    glVertex3d(-5,5,0);
    glTexCoord2d(0,0);
    glVertex3d(-5,5,5);
    glTexCoord2d(4,0);
    glVertex3d(-1,5,5);
    glTexCoord2d(4,5);
    glVertex3d(-1,5,0);

    glTexCoord2d(0,5);
    glVertex3d(1,5,0);
    glTexCoord2d(0,0);
    glVertex3d(1,5,5);
    glTexCoord2d(4,0);
    glVertex3d(5,5,5);
    glTexCoord2d(4,5);
    glVertex3d(5,5,0);

    glTexCoord2d(0,1);
    glVertex3d(-1,5,4);
    glTexCoord2d(0,0);
    glVertex3d(-1,5,5);
    glTexCoord2d(2,0);
    glVertex3d(1,5,5);
    glTexCoord2d(2,1);
    glVertex3d(1,5,4);
    glEnd();


    //pour boucher entre toit et mur
    glBegin(GL_TRIANGLES);
    glTexCoord2d(0,2);
    glVertex3d(5,5,5);
    glTexCoord2d(5,0.5);
    glVertex3d(0,5,6.5); //6.5 hauteur du toit
    glTexCoord2d(10,2);
    glVertex3d(-5,5,5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_TRIANGLES);
    glTexCoord2d(0,2);
    glVertex3d(5,-5,5);
    glTexCoord2d(5,0.5);
    glVertex3d(0,-5,6.5); //6.5 hauteur du toit
    glTexCoord2d(10,2);
    glVertex3d(-5,-5,5);
    glEnd();

    glPushMatrix();
    //roquette
    glPushMatrix();
    glTranslatef(-4.5,5.5,0);
    glScalef (0.5,0.5,0.5 );
    roquette();
    glRotated(80,0,1,0);
    glTranslatef(-0.3,1.5,0);
    roquette();
    glPopMatrix();

    //table
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTranslatef(2,7.5,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);
    glTranslatef(-1,0,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);
    glTranslatef(0,1,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);
    glTranslatef(1,0,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);

    glBindTexture(GL_TEXTURE_2D, texture[9]);
    glTranslatef(-0.5,-0.5,1.5);
    gluDisk(params,0,1.5,20,1);


    //caisse
    caisse();
    glTranslatef(0,-4,-1.5);
    caisse();
    glTranslatef(-5.5,-8,0);
    caisse();


    //porte
    glTranslatef(3,-1,0);
    glBindTexture(GL_TEXTURE_2D, texture[10]);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex3d(-2,0,4);
    glTexCoord2d(1,0);
    glVertex3d(0,0,4);
    glTexCoord2d(1,1);
    glVertex3d(0,0,0);
    glTexCoord2d(0,1);
    glVertex3d(-2,0,0);
    glEnd();

    //toit
    glTranslatef(-0.5,0,0.01);
    glBindTexture(GL_TEXTURE_2D, texture[12]);
    glBegin(GL_QUADS);
    glTexCoord2d(10,0);
    glVertex3d(-5,0,4.55); //4.55 pour pas que ca coupe le mur
    glTexCoord2d(10,3);
    glVertex3d(1.5,0,6.5);
    glTexCoord2d(0,3);
    glVertex3d(1.5,15,6.5);
    glTexCoord2d(0,0);
    glVertex3d(-5,15,4.55);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2d(10,0);
    glVertex3d(8,0,4.55);
    glTexCoord2d(10,3);
    glVertex3d(1.5,0,6.5);
    glTexCoord2d(0,3);
    glVertex3d(1.5,15,6.5);
    glTexCoord2d(0,0);
    glVertex3d(8,15,4.55);
    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[13]);
    glBegin(GL_QUADS);
    glTexCoord2d(1,0);
    glVertex3d(-5,6,1.5);
    glTexCoord2d(0,0);
    glVertex3d(-5,9,1.5);
    glTexCoord2d(0,1);
    glVertex3d(-5,9,4.5);
    glTexCoord2d(1,1);
    glVertex3d(-5,6,4.5);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[13]);
    glBegin(GL_QUADS);
    glTexCoord2d(1,0);
    glVertex3d(5,-1.5,1.5);
    glTexCoord2d(0,0);
    glVertex3d(5,1.5,1.5);
    glTexCoord2d(0,1);
    glVertex3d(5,1.5,4.5);
    glTexCoord2d(1,1);
    glVertex3d(5,-1.5,4.5);
    glEnd();

    gluDeleteQuadric(params);
}

void roquette()
{

    glPushMatrix();


    GLUquadric* params;
    params = gluNewQuadric();

    gluQuadricDrawStyle(params,GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    gluQuadricTexture(params,GL_TRUE);
    gluDisk(params,0,0.30,20,1);

    glBindTexture(GL_TEXTURE_2D,texture[2]);
    gluCylinder(params,0.30,0.15,0.25,20,1);

    glTranslatef(0,0,0.15);
    glBindTexture(GL_TEXTURE_2D,texture[3]);
    gluCylinder(params,0.15,0.50,1.05,20,1);

    glTranslatef(0,0,1.05);
    glBindTexture(GL_TEXTURE_2D,texture[4]);
    gluCylinder(params,0.50,0,1.60,20,1);

    gluDeleteQuadric(params);

    glPopMatrix();
}

void caisse()
{

    glBindTexture(GL_TEXTURE_2D, texture[11]);

    glBegin(GL_QUADS);
    //par terre
    glTexCoord2d(0,0);
    glVertex3d(-0.5,-0.5,0);
    glTexCoord2d(1,0);
    glVertex3d(0.5,-0.5,0);
    glTexCoord2d(1,1);
    glVertex3d(0.5,0.5,0);
    glTexCoord2d(0,1);
    glVertex3d(-0.5,0.5,0);

    //face droite
    glTexCoord2d(0,0);
    glVertex3d(-0.5,-0.5,1);
    glTexCoord2d(1,0);
    glVertex3d(-0.5,0.5,1);
    glTexCoord2d(1,1);
    glVertex3d(-0.5,0.5,0);
    glTexCoord2d(0,1);
    glVertex3d(-0.5,-0.5,0);

    //face gauche
    glTexCoord2d(0,0);
    glVertex3d(0.5,-0.5,1);
    glTexCoord2d(1,0);
    glVertex3d(0.5,0.5,1);
    glTexCoord2d(1,1);
    glVertex3d(0.5,0.5,0);
    glTexCoord2d(0,1);
    glVertex3d(0.5,-0.5,0);

    //face face
    glTexCoord2d(0,0);
    glVertex3d(-0.5,0.5,1);
    glTexCoord2d(1,0);
    glVertex3d(0.5,0.5,1);
    glTexCoord2d(1,1);
    glVertex3d(0.5,0.5,0);
    glTexCoord2d(0,1);
    glVertex3d(-0.5,0.5,0);

    //face derriere
    glTexCoord2d(0,0);
    glVertex3d(-0.5,-0.5,1);
    glTexCoord2d(1,0);
    glVertex3d(0.5,-0.5,1);
    glTexCoord2d(1,1);
    glVertex3d(0.5,-0.5,0);
    glTexCoord2d(0,1);
    glVertex3d(-0.5,-0.5,0);
    //face au ciel
    glTexCoord2d(0,0);
    glVertex3d(-0.5,-0.5,1);
    glTexCoord2d(1,0);
    glVertex3d(0.5,-0.5,1);
    glTexCoord2d(1,1);
    glVertex3d(0.5,0.5,1);
    glTexCoord2d(0,1);
    glVertex3d(-0.5,0.5,1);

    glEnd();

}

void jardindeDeadMaster()
{
    int i = 0;
    GLUquadric* params;
    params = gluNewQuadric();
    gluQuadricDrawStyle(params,GLU_FILL);
    gluQuadricTexture(params,GL_TRUE);


    //
    //Sol Extérieur partie maison > bord piscine
    //

    glBindTexture(GL_TEXTURE_2D, texture[14]);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(-10.5,-20,-0.015);
    glTexCoord2i(10,0);
    glVertex3d(20,-20,-0.015);
    glTexCoord2i(10,10);
    glVertex3d(20,20,-0.015);
    glTexCoord2i(0,10);
    glVertex3d(-10.5,20,-0.015);
    glEnd();


    glPushMatrix();
    glTranslated(-10.5,-5,0);

    glBindTexture(GL_TEXTURE_2D, texture[14]);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(0,0,-0.015);
    glTexCoord2i(3,0);
    glVertex3d(-6,0,-0.015);
    glTexCoord2i(3,3);
    glVertex3d(-6,-15,-0.015);
    glTexCoord2i(0,3);
    glVertex3d(0,-15,-0.015);
    glEnd();



    //
    //  Piscine
    //

    glTranslated(-0.5,5,-0.015);

    //Dalle Piscine gauche

    glBindTexture(GL_TEXTURE_2D, texture[16]);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(-0.5,-5,0);
    glTexCoord2i(1,0);
    glVertex3d(0.5,-5,0);
    glTexCoord2i(1,10);
    glVertex3d(0.5,5,0);
    glTexCoord2i(0,10);
    glVertex3d(-0.5,5,0);
    glEnd();

    glTranslated(-5,0,0);

    //Dalle Piscine Droite

    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(-0.5,-4,0);
    glTexCoord2i(1,0);
    glVertex3d(0.5,-4,0);
    glTexCoord2i(1,8);
    glVertex3d(0.5,4,0);
    glTexCoord2i(0,8);
    glVertex3d(-0.5,4,0);
    glEnd();

    glTranslated(-0.5,5,0);

    // Bordure piscine

    glBegin(GL_QUADS);
    glTexCoord2i(5,1);
    glVertex3d(0,0,0);
    glTexCoord2i(5,0);
    glVertex3d(0,-1,0);
    glTexCoord2i(0,0);
    glVertex3d(5,-1,0);
    glTexCoord2i(0,1);
    glVertex3d(5,0,0);
    glEnd();

    glTranslated(0,-9,0);

    // Bordure piscine

    glBegin(GL_QUADS);
    glTexCoord2i(5,1);
    glVertex3d(0,0,0);
    glTexCoord2i(5,0);
    glVertex3d(0,-1,0);
    glTexCoord2i(0,0);
    glVertex3d(5,-1,0);
    glTexCoord2i(0,1);
    glVertex3d(5,0,0);
    glEnd();

    glTranslated(1,0,0);

    // Bordure piscine

    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(0,0,0);
    glTexCoord2i(0,5);
    glVertex3d(0,0,-5);
    glTexCoord2i(8,5);
    glVertex3d(0,8,-5);
    glTexCoord2i(8,0);
    glVertex3d(0,8,0);
    glEnd();

    // Bordure piscine

    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(0,0,0);
    glTexCoord2i(0,5);
    glVertex3d(0,0,-5);
    glTexCoord2i(4,5);
    glVertex3d(4,0,-5);
    glTexCoord2i(4,0);
    glVertex3d(4,0,0);
    glEnd();

    glTranslated(4,0,0);

    // Bordure piscine

    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(0,0,0);
    glTexCoord2i(0,5);
    glVertex3d(0,0,-5);
    glTexCoord2i(8,5);
    glVertex3d(0,8,-5);
    glTexCoord2i(8,0);
    glVertex3d(0,8,0);
    glEnd();

    glTranslated(0,8,0);

    // Bordure piscine

    glBindTexture(GL_TEXTURE_2D, texture[16]);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(0,0,0);
    glTexCoord2i(0,5);
    glVertex3d(0,0,-5);
    glTexCoord2i(4,5);
    glVertex3d(-4,0,-5);
    glTexCoord2i(4,0);
    glVertex3d(-4,0,0);
    glEnd();

    // Fond piscine

    glBindTexture(GL_TEXTURE_2D, texture[16]);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(0,0,-5);
    glTexCoord2i(4,0);
    glVertex3d(-4,0,-5);
    glTexCoord2i(4,8);
    glVertex3d(-4,-8,-5);
    glTexCoord2i(0,8);
    glVertex3d(0,-8,-5);
    glEnd();


    // Eau picine

    glPushMatrix();

    //Sol extérieur partie devant picine > puit

    glTranslated(1,1,0);


    glBindTexture(GL_TEXTURE_2D, texture[14]);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(0,0,0);
    glTexCoord2i(3,0);
    glVertex3d(-6,0,0);
    glTexCoord2i(3,3);
    glVertex3d(-6,6,0);
    glTexCoord2i(0,3);
    glVertex3d(0,6,0);
    glEnd();

    // herbe autour du puit
    glTranslated(-2,8,-0.015); // petit fintage pour évité un bug d'affichage avec l'herbe

    gluDisk(params,2,3,20,1);


    glTranslated(0,0,-5);

    // Puit partie extérieur
    glBindTexture(GL_TEXTURE_2D, texture[18]);

    gluCylinder(params,2,2,7,20,1);


    // Puit partie intérieur
    gluCylinder(params,1.5,1.5,7,20,1);

    // Fond du puits

    glBindTexture(GL_TEXTURE_2D, texture[17]);
    gluDisk(params,0,2,20,1);

    // Eau du puit

    glTranslated(0,0,6); //TODO : virer, je l'ai laissé pour pas tout casser ton dessin

    // bordure haut du puit
    glTranslated(0,0,1);

    glBindTexture(GL_TEXTURE_2D, texture[18]);
    gluDisk(params,1.5,2,20,1);

    glTranslated(-4,-2,-1.985);

    //herbe
    glBindTexture(GL_TEXTURE_2D, texture[14]);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex3d(0,0,0);
    glTexCoord2d(5,0);
    glVertex3d(0,9,0);
    glTexCoord2d(5,1);
    glVertex3d(2,9,0);
    glTexCoord2d(0,1);
    glVertex3d(2,0,0);
    glEnd();

    glTranslated(2,9,0);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex3d(0,0,0);
    glTexCoord2d(2,0);
    glVertex3d(0,-5,0);
    glTexCoord2d(2,3);
    glVertex3d(4,-5,0);
    glTexCoord2d(0,3);
    glVertex3d(4,0,0);
    glEnd();


    glTranslated(-2,0,0);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex3d(0,0,0);
    glTexCoord2d(30,0);
    glVertex3d(0,-40,0);
    glTexCoord2d(30,1);
    glVertex3d(-3,-40,0);
    glTexCoord2d(0,1);
    glVertex3d(-3,0,0);
    glEnd();

    glTranslated(15,-30,0.015);

    //table
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(4,-1,1.5);
    glTexCoord2i(2,0);
    glVertex3d(4,1,1.5);
    glTexCoord2i(2,1);
    glVertex3d(-4,1,1.5);
    glTexCoord2i(0,1);
    glVertex3d(-4,-1,1.5);
    glEnd();

    glTranslated(-4,0,1.5);

    // Bout table
    gluPartialDisk(params,0,1,20,1,180,180);

    glTranslated(8,0,0);

    //Bout table
    gluPartialDisk(params,0,1,20,1,0,180);

    glTranslated(0,-0.5,-1.5);

    // Pied table
    gluCylinder(params,0.1,0.1,1.5,20,1);

    // Pied table
    glTranslated(0,1,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);

    // Pied table
    glTranslated(-4,0,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);

    // Pied table
    glTranslated(-4,0,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);

    // Pied table
    glTranslated(0,-1,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);

    // Pied table
    glTranslated(4,0,0);
    gluCylinder(params,0.1,0.1,1.5,20,1);


    //roquette table rangé 1
    glPushMatrix();
    glScalef (0.5,0.5,0.5 );
    glTranslated(-10.7,0,3.01);

    for ( i = 0; i < 9; i++ )
    {
        glTranslated(2,0,0);
        roquette();
    }

    glTranslated(1,0,0.3);

    glRotated(80,-1,1,0);
    roquette();

    glPopMatrix();

    //roquette table rangé 2
    glScalef (0.5,0.5,0.5 );
    glTranslated(-10.7,2,3.01);

    for ( i = 0; i < 4; i++ )
    {
        glTranslated(2,0,0);
        roquette();
    }

    glTranslated(2,0,0);

    for ( i = 0; i < 5; i++ )
    {
        glTranslated(2,0,0);
        roquette();
    }

    glTranslated(-9.5,1.5,-1);

    glRotated(150,-8,1,0);
    roquette();

    glPopMatrix(); // remet l'état d'avant les roquettes
    glPopMatrix(); //Remet l'état d'origine

    glPushMatrix();
    glTranslated(-11.5,4,0);

    glColor4ub(255,255,255,128);
    glBindTexture(GL_TEXTURE_2D, texture[15]);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3d(0,0,-0.3);
    glTexCoord2i(3,0);
    glVertex3d(-4,0,-0.3);
    glTexCoord2i(3,2);
    glVertex3d(-4,-8,-0.3);
    glTexCoord2i(0,2);
    glVertex3d(0,-8,-0.3);
    glEnd();


    glPopMatrix();

    // Eau du puit
    glPushMatrix();
    glTranslated(-12.5,13,1.5);

    glBindTexture(GL_TEXTURE_2D, texture[15]);
    gluDisk(params,0,1.5,20,1);
    glColor4ub(255,255,255,255);
    glDisable(GL_BLEND);

    glPopMatrix();

    gluDeleteQuadric(params);
}
