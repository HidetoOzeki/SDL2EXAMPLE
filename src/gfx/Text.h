#ifndef TEXT_H
#define TEXT_H
#include "Screen.h"
#include <iostream>
#include <string>
#include "Bitmap.h"
class Text{
  private :
  std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,;:()[]+-=!? ";
  Bitmap* sprite;
  public :
  Text(Bitmap* bitmap);
  ~Text();
  void test(std::string text,Screen* screen,int x,int y);
};
#endif
