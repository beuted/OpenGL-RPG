//http://raptor.developpez.com/tutorial/opengl/skybox/

#include "skybox.h"

#include <stdio.h>  
#include <GL/gl.h>

void Skybox::initialize()
{

  // Chargement des six textures
  texture_image[0] = loadTexture( "textures/skybox/XN.bmp", false );
  texture_image[1] = loadTexture( "textures/skybox/XP.bmp", false );
  texture_image[2] = loadTexture( "textures/skybox/YN.bmp", false );
  texture_image[3] = loadTexture( "textures/skybox/YP.bmp", false );
  texture_image[4] = loadTexture( "textures/skybox/ZN.bmp", false );
  texture_image[5] = loadTexture( "textures/skybox/ZP.bmp", false );
	
}

void Skybox::render( float camera_yaw, float camera_pitch )
{
	// Configuration des états OpenGL
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	// Désactivation de l'écriture dans le DepthBuffer
	glDepthMask(GL_FALSE);

	// Rendu de la SkyBox
	draw( camera_yaw, camera_pitch );

	// Réactivation de l'écriture dans le DepthBuffer
	glDepthMask(GL_TRUE);

	// Réinitialisation des états OpenGL
	glEnable(GL_LIGHTING);
}

void Skybox::draw( float camera_yaw, float camera_pitch )
{
	// Taille du cube
	float t =4.0f;

	// Réglage de l'orientation
	glPushMatrix();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity(); // On se place sur la camera
	glRotatef(camera_yaw, 1.0f, 0.0f, 0.0f );
	glRotatef(camera_pitch, 0.0f, 1.0f, 0.0f );
	glRotatef(-90, 1.0f, 0.0f, 0.0f );

	glTranslatef( -t/2, -t/2, -t/2 );
	
	glBegin(GL_POINTS);
	       glVertex3f(0,0,0);
	       glEnd();
	// Rendu de la géométrie
	glBindTexture(GL_TEXTURE_2D, texture_image[0]);
	glBegin(GL_QUADS);			// X Négatif		
		glTexCoord2d(0,1); glVertex3f(0,0,0);
		glTexCoord2d(0,0); glVertex3f(0,0,t);
		glTexCoord2d(1,0); glVertex3f(t,0,t);
		glTexCoord2d(1,1); glVertex3f(t,0,0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_image[1]);
	glBegin(GL_QUADS);			// X Positif	
		glTexCoord2d(1,1); glVertex3f(0,t,0);
		glTexCoord2d(0,1); glVertex3f(t,t,0); 
		glTexCoord2d(0,0); glVertex3f(t,t,t);
		glTexCoord2d(1,0); glVertex3f(0,t,t); 	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_image[2]);
	glBegin(GL_QUADS);			// Y Négatif	
		glTexCoord2d(0,1); glVertex3f(0,0,0);
		glTexCoord2d(0,0); glVertex3f(t,0,0);
		glTexCoord2d(1,0); glVertex3f(t,t,0);
		glTexCoord2d(1,1); glVertex3f(0,t,0); 
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_image[3]);
	glBegin(GL_QUADS);			// Y Positif		
		glTexCoord2d(0,0); glVertex3f(0,0,t);
		glTexCoord2d(1,0); glVertex3f(0,t,t);
		glTexCoord2d(1,1); glVertex3f(t,t,t);
		glTexCoord2d(0,1); glVertex3f(t,0,t); 
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_image[4]);
	glBegin(GL_QUADS);			// Z Négatif
		glTexCoord2d(1,1); glVertex3f(0,0,0); 	
		glTexCoord2d(0,1); glVertex3f(0,t,0);
		glTexCoord2d(0,0); glVertex3f(0,t,t);
		glTexCoord2d(1,0); glVertex3f(0,0,t);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_image[5]);
	glBegin(GL_QUADS);			// Z Positif	
    	        glTexCoord2d(0,1); glVertex3f(t,0,0);
		glTexCoord2d(0,0); glVertex3f(t,0,t);
		glTexCoord2d(1,0); glVertex3f(t,t,t); 
		glTexCoord2d(1,1); glVertex3f(t,t,0); 
	glEnd();

	// Réinitialisation de la matrice ModelView
	glPopMatrix();
}
