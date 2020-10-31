#ifndef VEC3_H
#define VEC3_H
#include "Vec2.h"
class Vec3{
  private :
  float x,y,z;
  public :
  Vec3(float x,float y,float z);
  int getZBuffer();
  Vec2 getpos2d();
  Vec3 getMousePos();
  float getx(){return x;}
  float gety(){return y;}
  float getz(){return z;}
};
#endif
