#include "Vec3.h"
Vec3::Vec3(float x,float y,float z){
  Vec3::x = x;
  Vec3::y = y;
  Vec3::z = z;
}
int Vec3::getZBuffer(){
  return x+z-y;
}
Vec2 Vec3::getpos2d(){
  float px = x-z;
  float py = (z+x);
  px*=8;
  py*=8;
  py/=2;
  return Vec2(px,py+(y*8));
}
Vec3 Vec3::getMousePos(){
  float dx = x;
  float dy = y;
  dx/=2;
  float destx = dx+dy;
  float destz = dy-dx;
  destx/=8;
  destz/=8;
  return Vec3(destx,0,destz);
}
