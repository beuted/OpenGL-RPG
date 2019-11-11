#include "playercamera.h"

#include <cmath>
#include <GL/glu.h>
#include <iostream> // Pour les messages d'erreur

#include "vector3d.h"

PlayerCamera::PlayerCamera(double visionMax) :
	_visionMin(1.0), _visionMax(visionMax), distanceCamera(4) {
	typeVue = TEM_PERSONNE;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	skybox.initialize();
}

void PlayerCamera::look(const Personnage* personnage) {
	//On positionne la tete qui va voir selon le type de vue choisit
	
	// On choisit la direction ou se porte le regard
	Vector3D _target;
	switch (typeVue) {

	case (PERE_PERSONNE) :
		_head = personnage->position + personnage->dimension.X*personnage->forward + 0.5*personnage->dimension.Y*personnage->left + Vector3D(0,0,0.8*personnage->dimension.Z);
		_target = _head + personnage->forward;
		//Affichage skybox
	  	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(50.0, 1.0, _visionMin, _visionMax);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(_head.X, _head.Y, _head.Z, _target.X, _target.Y,
				  _target.Z, 0, 0, 1);
		skybox.render(-personnage->phi,-personnage->orientation.Z);
		break;
	case (TEM_PERSONNE) :
		_head = personnage->position - distanceCamera*personnage->forward + 0.5*personnage->dimension.Y*personnage->left + Vector3D(0,0,1.5*personnage->dimension.Z);
		_target = _head + personnage->forward;
		//Affichage skybox
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(50.0, 1.0, _visionMin, _visionMax);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(_head.X, _head.Y, _head.Z, _target.X, _target.Y,
				  _target.Z, 0, 0, 1);
		skybox.render(-personnage->phi,-personnage->orientation.Z);
		break;
	case (TEM_PERSONNE_INV) :
		_head = personnage->position + (6+distanceCamera)*personnage->forward + 0.5*personnage->dimension.X*personnage->left + Vector3D(0,0,1.5*personnage->dimension.Z);
		_target = _head - personnage->forward;
		//Affichage skybox
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(50.0, 1.0, _visionMin, _visionMax);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(_head.X, _head.Y, _head.Z, _target.X, _target.Y,
				  _target.Z, 0, 0, 1);
		skybox.render(personnage->phi,-personnage->orientation.Z);
		break;
	default :
		std::cout<<"Erreur : Type de vue choisie inexistant !" <<std::endl;
		exit(-1);
	}

}

Vector3D PlayerCamera::getBlocPrec(Carte *carte, Personnage *personnage) {
	Vector3D v = _head;
	Vector3D vPrec = _head;
	while(carte->inBounds(v)) {
		if(carte->getElemMap(v).getType() != 0)
			return vPrec;
		vPrec = v;
		v += personnage->forward;
	}
}

PlayerCamera::~PlayerCamera() {
  SDL_WM_GrabInput(SDL_GRAB_OFF);
  SDL_ShowCursor(SDL_ENABLE);	
}
