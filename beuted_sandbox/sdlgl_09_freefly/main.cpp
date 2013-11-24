#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include "sdlglutils.h"
#include "freeflycamera.h"
#include "carte.h"
#include "util_fig.h"
#include "personnage.h"

#define FPS 50
#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 640

#define DEBUG

void DrawGL(Carte* carte);

FreeFlyCamera * camera;
Carte* carte = new Carte(20,20,20);
Personnage* personnage = new Personnage();

GLfloat light0_position [] = {-4.0f, -5.0f, 10.0f, 0.0f}; // Position du soleil
GLfloat ambient[] = {0.15f,0.15f,0.15f,1.0f};             // couleur
GLfloat diffuse[] = {0.5f,0.5f,0.5f,1.0f};                // diffusivite du soleil

void stop()
{
  // ICI IL EST IMPERATIF DE TOUT DETRUIRE
  delete camera;
  delete carte;
  SDL_Quit();
}

int main(int argc, char *argv[]) {

    SDL_Event event;
    const Uint32 time_per_frame = 1000/FPS;
    unsigned int width = LARGEUR_FENETRE;
    unsigned int height = HAUTEUR_FENETRE;

    Uint32 last_time,current_time,elapsed_time; //for time animation
    Uint32 start_time,stop_time; //for frame limit

    SDL_Init(SDL_INIT_VIDEO);
    atexit(stop);

    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
    //initFullScreen(&width,&height);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(70,(double)width/height,0.001,1000);

    glEnable(GL_DEPTH_TEST);     // Active le test de profondeur
    glEnable(GL_LIGHTING); 	 // Active l'éclairage
    glEnable(GL_COLOR_MATERIAL); // Active la couleur des materiaux

    // Activations des parametres de la lumiere //
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    //////////////////////////////////////////////
        
    glEnable(GL_LIGHT0); 	// Allume la lumière n°1
    
    glEnable(GL_TEXTURE_2D);

    chargerTextures();
    personnage->chargerTextures();

    camera = new FreeFlyCamera(Vector3D(0,0,2));

    last_time = SDL_GetTicks();
    for (;;)
    {

        start_time = SDL_GetTicks();

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
		  exit(0);
                break;
                case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_p:
                    takeScreenshot("test.bmp");
                    break;
                    case SDLK_ESCAPE:
                    exit(0);
                    break;
                    default :
                    camera->OnKeyboard(event.key);
                }
                break;
                case SDL_KEYUP:
                camera->OnKeyboard(event.key);
                break;
                case SDL_MOUSEMOTION:
                camera->OnMouseMotion(event.motion);
                break;
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN:
                camera->OnMouseButton(event.button);
                break;
            }
        }

        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_time;
        last_time = current_time;

        camera->animate(elapsed_time);

        DrawGL(carte);

        stop_time = SDL_GetTicks();
        if ((stop_time - last_time) < time_per_frame)
        {
            SDL_Delay(time_per_frame - (stop_time - last_time));
        }

    }
    return 0;
}

void DrawGL(Carte* carte)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    camera->look();
    
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    
    // Le positionnement des lumiere vient apres le placement de la camera
    carte->dessinerCarte();
    //personnage->dessinerPerso();

    glFlush();
    SDL_GL_SwapBuffers();
}


