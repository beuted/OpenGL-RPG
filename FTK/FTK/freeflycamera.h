#ifndef FREEFLYCAMERA_H
#define FREEFLYCAMERA_H

#include "vector3d.h"
#include <SDL/SDL.h>
#include <map>
#include <string>

/**
 * \class FreFlyCamera : Classe gérant un mode de vue de type "camera libre" soumis
 * à aucune contrainte. Dans ce type de camera c'est la camera qui gere les Inputs
 * puisqu'elle n'a pas besoin de communiqué avec le game_engine
 * (TODO : a terme à modifier pour mettre des contraintes : pas sortir d'une
 * certaine zone etc ... tout ca sera geré par game engine il n'existera plus qu'une
 * sorte de camera.)
 */
class FreeFlyCamera
{
public:
    FreeFlyCamera(double visionmax = 50.0, Vector3D position = Vector3D(0,0,0));

    virtual void OnMouseMotion(const SDL_MouseMotionEvent & event);
    virtual void OnMouseButton(const SDL_MouseButtonEvent & event);
    virtual void OnKeyboard(const SDL_KeyboardEvent & event);

    virtual void animate(Uint32 timestep);
    virtual void setSpeed(double speed);
    virtual void setSensivity(double sensivity);

    virtual void setPosition(const Vector3D & position);

    virtual void look();

    virtual ~FreeFlyCamera();
protected:
    double _speed;
    double _sensivity;

    //vertical motion stuffs
    Uint32 _timeBeforeStoppingVerticalMotion;
    bool _verticalMotionActive;
    int _verticalMotionDirection;

    typedef std::map<SDLKey,bool> KeyStates;
    KeyStates _keystates;
    typedef std::map<std::string,SDLKey> KeyConf;
    KeyConf _keyconf;

    Vector3D _position;
    Vector3D _target;
    Vector3D _forward;
    Vector3D _left;
    double _theta;
    double _phi;

    double _visionMin;
    double _visionMax;

    void VectorsFromAngles();
    //void Init();
};

#endif //FREEFLYCAMERA_H
