#include "vector3d.h"
#include <cmath>
#include <iostream> //PR MSG D'ERREUR

Vector3D::Vector3D()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Vector3D::Vector3D(GLfloat x,GLfloat y,GLfloat z)
{
    X = x;
    Y = y;
    Z = z;
}

Vector3D::Vector3D(const Vector3D & v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
}

Vector3D::Vector3D(const Vector3D & from,const Vector3D & to)
{
    X = to.X - from.X;
    Y = to.Y - from.Y;
    Z = to.Z - from.Z;
}

Vector3D & Vector3D::operator= (const Vector3D & v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
    return *this;
}

Vector3D & Vector3D::operator+= (const Vector3D & v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    return *this;
}

Vector3D Vector3D::operator+ (const Vector3D & v) const
{
    Vector3D t = *this;
    t += v;
    return t;
}

Vector3D & Vector3D::operator-= (const Vector3D & v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D & v) const
{
    Vector3D t = *this;
    t -= v;
    return t;
}

Vector3D & Vector3D::operator*= (const GLfloat a)
{
    X *= a;
    Y *= a;
    Z *= a;
    return *this;
}

Vector3D Vector3D::operator* (const GLfloat a)const
{
    Vector3D t = *this;
    t *= a;
    return t;
}

Vector3D operator* (const GLfloat a,const Vector3D & v)
{
    return Vector3D(v.X*a,v.Y*a,v.Z*a);
}

Vector3D & Vector3D::operator/= (const GLfloat a)
{
    X /= a;
    Y /= a;
    Z /= a;
    return *this;
}

Vector3D Vector3D::operator/ (const GLfloat a)const
{
    Vector3D t = *this;
    t /= a;
    return t;
}


 bool Vector3D::operator== (const Vector3D & v) const
 {
   return (X ==v.X && Y ==v.Y && Z ==v.Z);
 }

 bool Vector3D::operator== (GLfloat f) const
 {
   return (X ==f && Y ==f && Z ==f);
 }

double Vector3D::scalarProduct(const Vector3D & v)const
{
  return X*v.X + Y*v.Y + Z*v.Z;
}

Vector3D Vector3D::crossProduct(const Vector3D & v)const
{
    Vector3D t;
    t.X = Y*v.Z - Z*v.Y;
    t.Y = Z*v.X - X*v.Z;
    t.Z = X*v.Y - Y*v.X;
    return t;
}

double Vector3D::horizontalAngle(const Vector3D & v) const 
{
  Vector3D v_cpy(*this);
  Vector3D v_cpy2(v);
  Vector3D v_signe;
  v_cpy.Z = 0; v_cpy2.Z = 0;

  if (v_cpy == 0 || v_cpy2 == 0)
    return 0;

  v_signe = v_cpy.crossProduct(v_cpy2);
  if (v_signe.Z > 0.0001) {
	  //std::cout << "angle : " << -acos((v_cpy.normalize()).scalarProduct(v_cpy2.normalize()))*(180/M_PI) << std::endl;
    return -acos((v_cpy.normalize()).scalarProduct(v_cpy2.normalize()))*(180/M_PI);
  } else if (v_signe.Z < -0.0001) {
	  //std::cout << "angle : " << acos((v_cpy.normalize()).scalarProduct(v_cpy2.normalize()))*(180/M_PI) << std::endl;

    return acos((v_cpy.normalize()).scalarProduct(v_cpy2.normalize()))*(180/M_PI);
  } else {
    return 0;
  }
}

double Vector3D::length() const
{
    return sqrt( X*X + Y*Y + Z*Z);
}

Vector3D & Vector3D::normalize()
{
  (*this) /= length();
  return (*this);
}

Vector3D & Vector3D::operator= (const GLfloat a) {
  X = a;
  Y = a;
  Z = a;
  return *this;
}


