#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <GL/gl.h>

/* Impl�mentation intuitive d'une classe Vector3D pour les lecteurs du cours
d'OpenGL, d�butants en C++. Il est �vident qu'une approche template est �
privil�gier pour favoriser la r�utilisabilit� et l'inlinisme. */

class Vector3D
{
public:
    GLfloat X;
    GLfloat Y;
    GLfloat Z;

    Vector3D();
    Vector3D(GLfloat x,GLfloat y,GLfloat z);
    Vector3D(const Vector3D & v);
    Vector3D(const Vector3D & from,const Vector3D & to);

    Vector3D & operator= (const Vector3D & v);

    Vector3D & operator+= (const Vector3D & v);
    Vector3D operator+ (const Vector3D & v) const;

    Vector3D & operator-= (const Vector3D & v);
    Vector3D operator- (const Vector3D & v) const;

    Vector3D & operator*= (const GLfloat a);
    Vector3D operator* (const GLfloat a)const;
    friend Vector3D operator* (const GLfloat a,const Vector3D & v);

    Vector3D & operator/= (const GLfloat a);
    Vector3D operator/ (const GLfloat a)const;

    bool operator== (const Vector3D & v) const;
    bool operator== (GLfloat f) const;

    /**
     * Produit vectorielle
     */
    Vector3D crossProduct(const Vector3D & v)const;

    /**
     * Produit scalaire
     */
    double scalarProduct(const Vector3D & v)const;

    /**
     * donne l'angle que formes les vecteurs dans le plan (Oxy)
     */
    double horizontalAngle(const Vector3D & v)const;

    double length()const;
    Vector3D & normalize();

    Vector3D & operator= (const GLfloat a);
};

#endif //VECTOR3D_H
