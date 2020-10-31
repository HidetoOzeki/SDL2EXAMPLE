#ifndef SCREEN_H
#define SCREEN_H
#include <SDL.h>
#include <iostream>
#include "Bitmap.h"
#include "Vec2.h"
class Screen{
private:
  int w,h;
  int xoffset,yoffset;
  Uint32* pixels;
  int* zbuffer;
public:
  Screen(int width,int height);
  void clear(int color);
  void swap();
  void clearzbuffer();
  void setoffset(int x,int y);
  void render(Bitmap* bitmap,int x,int y,int xo,int yo);
  void render(Bitmap* bitmap,int x,int y,int xo,int yo,bool xflip,bool yflip);
  void render(Bitmap* bitmap,int x,int y,int xo,int yo,bool xflip,bool yflip,int zb);
  void putpixel(int x,int y,int c);
  void polygon(Vec2 v1,Vec2 v2,Vec2 v3);
  Uint32* getRaster(){ return pixels;}
  int getWidth(){return w;};
  int getHeight(){return h;};
  void clean(){
  std::cout << "Screen Destructor Called!" << std::endl;
  delete zbuffer;
  delete pixels;
  }
};
#endif
