/*
 * brique.cpp
 *
 *  Created on: 11 mars 2013
 *      Author: benoit
 */
#include "brique.h"
#include "vector3d.h"

#include <stdio.h>  //TRACAGE
#include <iostream> //TRACAGE
#include <cmath>

void Brique::dessinerBrique() {
	GLfloat a = dimension[0];
	GLfloat b = dimension[1];
	GLfloat c = dimension[2];

	glTranslatef(position[0], position[1], position[2]);

	glTranslatef(axe_rotation[0], axe_rotation[1], axe_rotation[2]);
	glRotatef(orientation[0],1 ,0 ,0);
	glRotatef(orientation[1],0 ,1 ,0);
	glRotatef(orientation[2],0 ,0 ,1);
	glTranslatef(-axe_rotation[0], -axe_rotation[1], -axe_rotation[2]);

	if (gest_text != NULL) {
		if (*gest_text != NULL) {
			glBindTexture(GL_TEXTURE_2D, (*gest_text)->getTexture(texture_image[0]));
		}
	}
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3d(a, 0, c);
	glTexCoord2d(0, 0);
	glVertex3d(a, 0, 0);
	glTexCoord2d(1, 0);
	glVertex3d(a, b, 0);
	glTexCoord2d(1, 1);
	glVertex3d(a, b, c);
	glEnd();

	if (gest_text != NULL)
		if (*gest_text != NULL)
			glBindTexture(GL_TEXTURE_2D, (*gest_text)->getTexture(texture_image[1]));
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glTexCoord2d(1, 1);
	glVertex3d(a, b, c);
	glTexCoord2d(1, 0);
	glVertex3d(a, b, 0);
	glTexCoord2d(0, 0);
	glVertex3d(0, b, 0);
	glTexCoord2d(0, 1);
	glVertex3d(0, b, c);
	glEnd();

	if (gest_text != NULL)
		glBindTexture(GL_TEXTURE_2D, (*gest_text)->getTexture(texture_image[2]));
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glTexCoord2d(0, 1);
	glVertex3d(0, 0, c);
	glTexCoord2d(0, 0);
	glVertex3d(0, 0, 0);
	glTexCoord2d(1, 0);
	glVertex3d(a, 0, 0);
	glTexCoord2d(1, 1);
	glVertex3d(a, 0, c);
	glEnd();

	if (gest_text != NULL)
		if (*gest_text != NULL)
			glBindTexture(GL_TEXTURE_2D, (*gest_text)->getTexture(texture_image[3]));
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glTexCoord2d(1, 1);
	glVertex3d(0, b, c);
	glTexCoord2d(1, 0);
	glVertex3d(0, b, 0);
	glTexCoord2d(0, 0);
	glVertex3d(0, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3d(0, 0, c);
	glEnd();

	if (gest_text != NULL)
		if (*gest_text != NULL)
			glBindTexture(GL_TEXTURE_2D, (*gest_text)->getTexture(texture_image[4]));
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glTexCoord2d(1, 1);
	glVertex3d(a, b, 0);
	glTexCoord2d(1, 0);
	glVertex3d(a, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(0, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3d(0, b, 0);
	glEnd();

	if (gest_text != NULL)
		if (*gest_text != NULL)
			glBindTexture(GL_TEXTURE_2D, (*gest_text)->getTexture(texture_image[5]));
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glTexCoord2d(1, 0);
	glVertex3d(a, 0, c);
	glTexCoord2d(1, 1);
	glVertex3d(a, b, c);
	glTexCoord2d(0, 1);
	glVertex3d(0, b, c);
	glTexCoord2d(0, 0);
	glVertex3d(0, 0, c);
	glEnd();

}



  
  
