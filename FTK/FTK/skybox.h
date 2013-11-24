#ifndef H__skybox__
#define H__skybox__

#include <GL/gl.h>
#include "sdlglutils.h"

/**
 * \class skybox : gere la skybox, ses textures et son affichage
 */
class Skybox {
 public :
        /**
	 * Constructeur
	 */
        Skybox(){} // Mettre des trucs de initialize dedant ?
	~Skybox(){} // A FAIRE !

	void initialize();
	void render( float camera_yaw, float camera_pitch );
 private :
	void draw( float camera_yaw, float camera_pitch );

	GLuint texture_image[6];
};

#endif


