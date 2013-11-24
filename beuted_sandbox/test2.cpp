#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <cmath>
#include <iostream> // Pour les msg d'erreur

using namespace std;
 
void Dessiner();
 
double angleY = 0;
double angleX = 0;
double x = 0;
double z = 0;
double y = 0;
 
int main(int argc, char *argv[])
{
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);
 
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,1,1000);
 
    glEnable(GL_DEPTH_TEST);
 
    SDL_EnableKeyRepeat(100,100);

    Dessiner();
 
    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time,ellapsed_time;
    Uint32 start_time;
 
    for (;;)
    {
      start_time = SDL_GetTicks();

      current_time = SDL_GetTicks();
      ellapsed_time = current_time - last_time;
      last_time = current_time;

      while (SDL_PollEvent(&event)) {
 
	switch(event.type) {
	case SDL_QUIT:
	  exit(0);
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym) {
	  case SDLK_UP:
	    if (angleX < M_PI-0.05)
	      angleX += 0.05;
	    break;
	  case SDLK_DOWN:
	    if (angleX > 0.05)
	      angleX -= 0.05;
	    break;
	  case SDLK_LEFT: angleY += 0.05; break;
	  case SDLK_RIGHT: angleY -= 0.05; break;
	  case SDLK_z:
	    x += 0.5*cos(angleY)*sin(angleX);
	    y += 0.5*sin(angleY)*sin(angleX);
	    z += 0.5*cos(angleX);
	    break;
	  case SDLK_s:
	    x -= 0.5*cos(angleY)*sin(angleX);
	    y -= 0.5*sin(angleY)*sin(angleX);
	    z -= 0.5*cos(angleX);
	    break;
	  case SDLK_q: z -= 0.5; break;
	  case SDLK_d: z += 0.5; break;
	  default: break;
	  }
	  break;

	}
      }
 
 
        //angleZ += 0.05 * ellapsed_time;
        //angleX += 0.05 * ellapsed_time;
 
        Dessiner();
	ellapsed_time = SDL_GetTicks() - start_time;
        if (ellapsed_time < 10) {
	  SDL_Delay(10 - ellapsed_time);
        }
    }
 
    return 0;
}
 
void Dessiner()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
 
    gluLookAt(x,y,z,x+cos(angleY)*sin(angleX),y+sin(angleY)*sin(angleX),z+cos(angleX),0,0,1);
 
    //glRotated(angleZ,0,0,1);
    //glRotated(angleX,1,0,0);
 
    // Le cube //////////////////////////
    glBegin(GL_QUADS);
 
    glColor3ub(255,0,0); //face rouge
    glVertex3d(1,1,1);
    glVertex3d(1,1,-1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,1,1);
 
    glColor3ub(0,255,0); //face verte
    glVertex3d(1,-1,1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,1,-1);
    glVertex3d(1,1,1);
 
    glColor3ub(0,0,255); //face bleue
    glVertex3d(-1,-1,1);
    glVertex3d(-1,-1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,-1,1);
 
    glColor3ub(255,255,0); //face jaune
    glVertex3d(-1,1,1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,-1,1);
 
    glColor3ub(0,255,255); //face cyan
    glVertex3d(1,1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(-1,-1,-1);
    glVertex3d(-1,1,-1);
 
    glColor3ub(255,0,255); //face magenta
    glVertex3d(1,-1,1);
    glVertex3d(1,1,1);
    glVertex3d(-1,1,1);
    glVertex3d(-1,-1,1);
 

    // La sphere ////////////////////////////
    GLUquadric* params = gluNewQuadric();
    //glTranslated(4,4,4);
    gluQuadricDrawStyle(params,GLU_FILL);
    gluCylinder(params,1,1,2,20,1);
    
    glTranslated(0,0,2);
    //gluQuadricDrawStyle(params,GLU_FILL);
    gluCylinder(params,1,0,1,20,1);

    glTranslated(0,0,12);
    glColor3ub(230,230,230);
    //gluQuadricDrawStyle(params,GLU_FILL);
    gluSphere(params,0.75,20,20);
 
    gluDeleteQuadric(params);

    /////////////////////////////////////////

    glEnd();

    glFlush();
    SDL_GL_SwapBuffers();
}
