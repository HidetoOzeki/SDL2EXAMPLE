#include <iostream>
#include <string>
#include "Text.h"
Text::Text(Bitmap* bitmap){
  sprite = bitmap;
}
Text::~Text(){
  delete sprite;
}
void Text::render(std::string text,Screen* screen,int x,int y){
  for(int i = 0;i < text.length();i++){
    text[i] = std::toupper(text[i]);
  }
  int length = text.length();
  for(int i = 0;i < length;i++){
    int xoffset = str.find(text.at(i));
    int yoffset = 10;
    if(xoffset>=26){
      yoffset=11;
      xoffset-=26;
    }
      screen->render(sprite,x+i*8,y,xoffset*8,yoffset*8);
  }
}
