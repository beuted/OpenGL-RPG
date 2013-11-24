#include "brique_particulaire.h"

Brique_particulaire::Brique_particulaire(GLfloat* _dimension, GLfloat* _position, GLfloat* _orientation, GLfloat* _axe_rotation, double _puissance) : Brique_gene( _dimension, _position, _orientation, _axe_rotation, NULL, NULL) {

	puissance = _puissance;

	srand(time(NULL));
	for(int i=0; i<MAX_PARTICLES; i++) {
		particle[i].active = true;   // On rend la particule active
		particle[i].life = double(rand()%100)/100;      // Maximum de vie
		particle[i].fade = double(rand()%400+100)/10000;   // Vitesse de disparition aléatoire


		particle[i].r=double(rand()%100)/200;  // Quantité aléatoire de Rouge
		particle[i].g=0;                       // Quantité aléatoire de Vert
		particle[i].b=particle[i].r;           // Quantité aléatoire de Bleu
		particle[i].xi = puissance*double(rand()%200-100)/1000;   // Vitesse aléatoire
		particle[i].yi = puissance*double(rand()%200-100)/1000;
		particle[i].zi = puissance*double(rand()%200-100)/1000;

		particle[i].x = 0;   // Vitesse aléatoire
		particle[i].y = 0;
		particle[i].z = 0;
 
		particle[i].xg = 0.0;       // Gravité dirigée selon l'axe -Z
		particle[i].yg = 0.0;
		particle[i].zg = -1.0;
 
	}
}

void Brique_particulaire::dessinerBrique() {
		glTranslatef(position[0], position[1], position[2]);
		for(int i=0; i<MAX_PARTICLES; i++) {// Pour chaque particule
			if(particle[i].active)  {        // Si elle est active
				float x = particle[i].x;   // On récupère sa position
				float y = particle[i].y;
				float z = particle[i].z;
 
				/* Couleur de la particule; transparence = vie */
				GLfloat mcolor[4];
				mcolor[0] = particle[i].r*(particle[i].life);
				mcolor[1] = particle[i].g*(particle[i].life);
				mcolor[2] = particle[i].b*(particle[i].life);
				mcolor[3] = 1.0f;
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mcolor);
 
				glPushMatrix();
				//glRotatef(45,particle[i].x, particle[i].y, particle[i].z);
				// get the current modelview matrix
				float modelview[16];
				glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

				// undo all rotations
				// beware all scaling is lost as well 
				for(int I=0; I<3; I++ ) 
					for(int J=0; J<3; J++ ) {
						if ( I==J )
							modelview[I*4+J] = 1.0;
						else
							modelview[I*4+J] = 0.0;
					}

				// set the modelview with no rotations and scaling
				glLoadMatrixf(modelview);

				/* Dessin de carrés à partir de deux triangles (plus rapide pour la carte video */

				glBegin(GL_TRIANGLE_STRIP);
				glVertex3d(x-0.1*particle[i].life,y-0.1*particle[i].life,z); // Nord-Ouest
				glVertex3d(x+0.1*particle[i].life,y-0.1*particle[i].life,z); // Nord-Est
				glVertex3d(x-0.1*particle[i].life,y+0.1*particle[i].life,z); // Sud-Est
				glVertex3d(x+0.1*particle[i].life,y+0.1*particle[i].life,z); // Sud-Ouest
				glEnd();
			
				glPopMatrix();
 
				/* Déplacement */
				particle[i].x += particle[i].xi;
				particle[i].y += particle[i].yi;
				particle[i].z += particle[i].zi;
 
				/* Gravité */
				particle[i].xi += particle[i].xg/100;
				particle[i].yi += particle[i].yg/100;
				particle[i].zi += particle[i].zg/100;
 
				/* "Vie" */
				particle[i].life -= particle[i].fade;
				/* Si la particule est "morte" on la régénère */
				if (particle[i].life < 0.0)
					{   particle[i].life = 1.0;    // Maximum de vie
						particle[i].fade = double(rand()%400+100)/10000;
 
						particle[i].x = 0; // On renvoie la particule au centre
						particle[i].y = 0;
						particle[i].z = 0;
 
						particle[i].xi = puissance*double(rand()%200-100)/1000;   // Vitesse aléatoire
						particle[i].yi = puissance*double(rand()%200-100)/1000;
						particle[i].zi = puissance*double(rand()%200-100)/1000;
 
						particle[i].r=double(rand()%100)/100;  // Quantité aléatoire de Rouge
						particle[i].g=0;//double(rand()%100)/100;  // Quantité aléatoire de Vert
						particle[i].b=particle[i].r;//double(rand()%100)/100;  // Quantité aléatoire de Bleu
					}
			}
		}
	}
