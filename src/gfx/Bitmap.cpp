#include "Bitmap.h"
Bitmap::Bitmap(const char* filename){
  SDL_Surface* img = SDL_LoadBMP(filename);
  std::cout << SDL_GetError() << std::endl;
  w = img->w;
  h = img->h;
  pixels = (Uint32*)img->pixels;
  SDL_FreeSurface(img);
  std::cout << "bitmap initialized" << std::endl;
}
