#ifndef BITMAP_H
#define BITMAP_H
#include <string>
#include <SDL.h>
#include <iostream>
class Bitmap{
private:
  Uint32* pixels;
  int w,h;
public:
  Bitmap(const char*);
  ~Bitmap(){
    std::cout << "destructor called" << std::endl;
  }
  int getWidth(){return w;}
  int getHeight(){return h;}
  Uint32* getPixels(){return pixels;}
};
#endif
