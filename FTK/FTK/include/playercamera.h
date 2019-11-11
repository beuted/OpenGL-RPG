#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H

#include "vector3d.h"
#include "personnage.h"
#include "skybox.h"

#include <SDL/SDL.h>
#include <map>
#include <string>

/**
 * Differents type de vue pour le joueur
 */
enum TypeVue {
	PERE_PERSONNE, TEM_PERSONNE, TEM_PERSONNE_INV
};

/**
 * Classe gérant un mode de vue de type "camera libre" soumis à aucune
 * contrainte
 */
class PlayerCamera {
public:
	PlayerCamera(double visionmax = 50.0);

	~PlayerCamera();

	/**
	 * fait appel à gluLookAt pour creer la vision
	 */
	virtual void look(const Personnage* personnage);

	/* ******** GETTERS SETTERS ************ */
	/**
	 * Modifie typeVue
	 */
	inline void setTypeVue(TypeVue _typeVue) {	typeVue = _typeVue;}

	/**
	 * \return typeVue
	 */
	inline const TypeVue getTypeVue() const { return typeVue ;}

	/**
	 * Modifie distanceCamera
	 */
	inline void chgDistanceCamera(double i) { distanceCamera += i;}

	/**
	 * renvoi les coord du Bloc de la carte regardé
	 */
	Vector3D getBlocPrec(Carte *carte, Personnage *personnage);

protected:
	
	/**
	 * Skybox
	 */
	Skybox skybox;

	double _sensivity;

	/**
	 * Position de la camera
	 * (regarde dans la direction forward)
	 */
	Vector3D _head;

	double _visionMin;
	double _visionMax;

	/**
	 * Type de vue selectionné
	 */
	TypeVue typeVue;

	/**
	 * Distance de la camera par rapport au perso
	 */
	double distanceCamera;

	//void Init();
};

#endif //PLAYERFLYCAMERA_H
