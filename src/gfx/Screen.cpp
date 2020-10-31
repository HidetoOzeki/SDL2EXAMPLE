#include "Screen.h"
Screen::Screen(int width,int height){
  w = width;
  h = height;
  pixels = new Uint32[w*h];
  zbuffer = new int[w*h];
}
void Screen::setoffset(int x,int y){
xoffset = x;
yoffset = y;
}
void Screen::render(Bitmap* bitmap,int x,int y,int xo,int yo,bool xflip,bool yflip){
  render(bitmap,x,y,xo,yo,xflip,yflip,0);
}
void Screen::render(Bitmap* bitmap,int x,int y,int xo,int yo,bool xflip,bool yflip,int zb){
  x-=xoffset;
  y-=yoffset;
  for(int j = 0;j < 8;j++){
    int py = y+j;
    if(py < 0||py >= h)continue;
    for(int i = 0;i < 8;i++){
      int px = x+i;
      if(px < 0||px >= w)continue;
      int tx = xo+i;
      int ty = yo+j;
      if(xflip)tx = (xo+7)-i;
      if(yflip)ty = (yo+7)-j;
      if(zbuffer[px+py*w]<=zb){
      int c = bitmap->getPixels()[tx+ty*bitmap->getWidth()];
      if(c!=0xff000000){
        pixels[px+py*w] = c;
        zbuffer[px+py*w] = zb;
      }
      }
  }
 }
}
void Screen::swap(){
  for(int i = 0;i < w*h;i++){
    int zz = zbuffer[i]*10;
    pixels[i] = zz<<16|zz<<8|zz;
  }
}
void Screen::render(Bitmap* bitmap,int x,int y,int xo,int yo){
  render(bitmap,x,y,xo,yo,false,false,0);
}
void Screen::putpixel(int x,int y,int c){
  pixels[x+y*w] = c;
}
void Screen::polygon(Vec2 v1,Vec2 v2,Vec2 v3){
}

void Screen::clear(int color){
  for(int i = 0;i < w*h;i++){
    pixels[i] = color;
  }
}
void Screen::clearzbuffer(){
  for(int i = 0;i < w*h;i++){
    zbuffer[i] = -1;
  }
}
