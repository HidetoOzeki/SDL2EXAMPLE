#include <iostream>
#include <string>
#include "Text.h"
Text::Text(Bitmap* bitmap){
  sprite = bitmap;
}
Text::~Text(){
  delete sprite;
}
void Text::test(std::string text,Screen* screen,int x,int y){
  for(int i = 0;i < text.length();i++){
    text[i] = std::toupper(text[i]);
  }
  int length = text.length();
  for(int i = 0;i < length;i++){
    int offset = str.find(text.at(i));
      screen->render(sprite,x+i*8,y,offset*8,10*8);
  }
}
