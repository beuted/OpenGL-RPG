#include "srcParticules.h"

// TODO : A RASSEMBLER A UN SEUL ENDROIT ///
const uint time_per_frame = 1000/50;      //
////////////////////////////////////////////

SrcParticules::SrcParticules() {
  // Set all particles to dead
   for(int Index=0;Index!=NUM_PARTICLES;Index++)
    {
     Spr[Index].life=0.0f;
     Spr[Index].r=1.0f;
     Spr[Index].b=0.0f;
    }
}

// Update particles, generating new if required
void SrcParticules::update() {
  int Spread, Angle = 0;
  

  // Seed the randomiser
 

  for(int Index=0;Index!=MaxParticles;Index++) {
    // Seed the randomiser
    srand(time(NULL));
    if(Spr[Index].life>0.0f) {
      Spr[Index].xPos+=(Spr[Index].xVec*time_per_frame);
      Spr[Index].yPos+=(Spr[Index].yVec*time_per_frame);
      Spr[Index].zPos+=(Spr[Index].zVec*time_per_frame);
      Spr[Index].yVec-=(SPEED_DECAY*time_per_frame);  
 
      // 'Bounce' particle if on the floor square
      if(Spr[Index].xPos>-10.0f && Spr[Index].xPos<10.0f &&
	 Spr[Index].zPos>-10.0f && Spr[Index].zPos<10.0f) {
	if(Spr[Index].yPos<PARTICLE_SIZE) {
	  Spr[Index].yPos=PARTICLE_SIZE;
	  Spr[Index].life-=0.01f;
	  Spr[Index].yVec*=-0.6f;
	}
      }
      Spr[Index].life-=(0.0001f*time_per_frame);
    } else { // Spawn a new particle
      // Reset position
      Spr[Index].xPos=0.0f;
      Spr[Index].yPos=PARTICLE_SIZE;
      Spr[Index].zPos=0.0f;
 
      // Get a random spread and direction
      Spread=(float)(rand()%MaxSpread)/10000.0f;
      Angle=(float)(rand()%157)/100.0f; // Quarter circle
 
      // Calculate X and Z vectors
      Spr[Index].xVec=cos(Angle)*Spread;
      Spr[Index].zVec=sin(Angle)*Spread;
 
      // Randomly reverse X and Z vector to complete the circle
      if(rand()%2)
	Spr[Index].xVec= - Spr[Index].xVec;
 
      if(rand()%2)
	Spr[Index].zVec= - Spr[Index].zVec;
 
      // Get a random initial speed
      Spr[Index].yVec=(float)(rand()%500)/10000.0f;
 
      // Get a random life and 'yellowness'
      Spr[Index].life=(float)(rand()%100)/100.0f;
      Spr[Index].g=0.2f+((float)(rand()%50)/100.0f);
    }
  }
}

 // Draw the particles
void SrcParticules::draw() {

  //glBindTexture(GL_TEXTURE_2D,textures[0]);
  glEnable(GL_BLEND);
  //glDepthMask(GL_FALSE);

  for(int Index=0;Index!=MaxParticles;Index++) {
      glPushMatrix();
 
      // Place the quad and rotate to face the viewer
      glColor4f(Spr[Index].r,Spr[Index].g,Spr[Index].b,Spr[Index].life);
      glTranslatef(Spr[Index].xPos,Spr[Index].yPos,Spr[Index].zPos);
      glRotatef(20/*ViewAngle1*/,0.0f,1.0f,0.0f);
      glRotatef(0/*ViewAngle2*/,1.0f,0.0f,0.0f);
 
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f); glVertex3f(-PARTICLE_SIZE, PARTICLE_SIZE,0.0f);
      glTexCoord2f(0.0f,1.0f); glVertex3f(-PARTICLE_SIZE,-PARTICLE_SIZE,0.0f);
      glTexCoord2f(1.0f,1.0f); glVertex3f( PARTICLE_SIZE,-PARTICLE_SIZE,0.0f);
      glTexCoord2f(1.0f,0.0f); glVertex3f( PARTICLE_SIZE, PARTICLE_SIZE,0.0f);
      glEnd();
 
      glPopMatrix();
    }
}
