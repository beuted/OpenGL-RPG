#ifndef _SRCPARTICULE_
#define _SRCPARTICULE_

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct
{
  float xPos,yPos,zPos;
  float xVec,yVec,zVec;
  float r,g,b,life;
}SpriteInfo;

const float PARTICLE_SIZE = 0.5f;
const int NUM_PARTICLES = 10000;
const int INITIAL_PARTICLE_SPREAD = 100;
const float SPEED_DECAY = 0.00005f; // (Gravity)

const int MaxSpread = INITIAL_PARTICLE_SPREAD;
const int MaxParticles = NUM_PARTICLES/2;

class SrcParticules {

 private :
  SpriteInfo Spr[NUM_PARTICLES];
 public :
  SrcParticules();
  // Mets a jour la position es particules
  void update();
  // Affiche les particules
  void draw();
};

#endif
