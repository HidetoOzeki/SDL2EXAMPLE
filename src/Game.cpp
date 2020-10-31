#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "gfx/Vec3.h"
#include "gfx/Text.h"
Bitmap* bitmap;
Text* text;
class Ball{
  private :
  float x,y,z;
  float xv,yv,zv;
  float inc;
  bool land = false;
  public :
  Ball(float xp,float yp,float zp){
    x = xp;
    y = yp;
    z = zp;
  }
  void move(float xvel,float zvel){
    xv+=xvel;
    zv+=zvel;
  }
  void jump(){
    yv=-0.4f;land=false;
  }
  void render(Screen* screen){
    Vec3 v(x,y,z);
    int px = v.getpos2d().getx()+screen->getWidth()/2;
    int py = v.getpos2d().gety()+screen->getHeight()/2;
    int zbuf = v.getZBuffer();
    screen->render(bitmap,px,py,8*3,8*3,0,0,zbuf);
    screen->render(bitmap,px-8,py-8,8*2,8*2,0,0,zbuf);
    screen->render(bitmap,px-8,py,8*2,8*3,0,0,zbuf);
    screen->render(bitmap,px,py-8,8*3,8*2,0,0,zbuf);
  }
  void update(){
    x+=xv;
    y+=yv;
    z+=zv;
    xv*=0.9;
    zv*=0.9;
    yv+=0.02;
    if(y+yv > 0){
      yv=0;
      land = true;
    }
  }
};
void Game::putlevel(int x,int y,int z,int id){
  level[x+z*10+y*(10*10)] = id;
}
Game::Game(){}
Game::~Game(){}
Ball ball(1,-6,1);
Ball ball2(6,-6,1);
void Game::init(const int width,const int height,int scale){
  w = width;
  h = height;
  Game::scale = scale;
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("game",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            w*scale,
                            h*scale,
                            SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
  renderer = SDL_CreateRenderer(window,-1,
                                SDL_RENDERER_ACCELERATED);
  texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    width,
    height);
  bitmap = new Bitmap("../res/spritesheet.bmp");
  text = new Text(bitmap);
  pixels = new Uint32[w*h];
  screen = new Screen(w,h);
  //SDL_GL_SetSwapInterval(0);
  running = true;
}
bool swp = 0;
int xwindow,ywindow;
void Game::input(){
  SDL_GetWindowPosition(window,&xwindow,&ywindow);
  SDL_Event e;
  while(SDL_PollEvent(&e)){
    switch(e.type){
      case SDL_QUIT:
      running = false;
      break;
      case SDL_MOUSEMOTION:
      pxmouse = xmouse;pymouse = ymouse;
      SDL_GetGlobalMouseState(&xmouse,&ymouse);
      xmouse-=xwindow;ymouse-=ywindow;
      xmouse/=scale;ymouse/=scale;
      break;
      case SDL_MOUSEBUTTONDOWN:
      if(e.button.button==SDL_BUTTON_RIGHT)m_buttonright=true;
      if(e.button.button==SDL_BUTTON_LEFT)m_buttonleft=true;
      break;
      case SDL_MOUSEBUTTONUP:
      if(e.button.button==SDL_BUTTON_RIGHT)m_buttonright=false;
      if(e.button.button==SDL_BUTTON_LEFT)m_buttonleft=false;
      break;
    }
  }
  const Uint8* KEYS = SDL_GetKeyboardState(NULL);
  if(KEYS[SDL_SCANCODE_W])ball.move(0,-0.01);
  if(KEYS[SDL_SCANCODE_S])ball.move(0,0.01);
  if(KEYS[SDL_SCANCODE_A])ball.move(-0.01,0);
  if(KEYS[SDL_SCANCODE_D])ball.move(0.01,0);
  if(KEYS[SDL_SCANCODE_SPACE])ball.jump();
  if(KEYS[SDL_SCANCODE_R])swp=!swp;
}
int imgx = 0;
int imgy = 0;
void Game::update(){
  ball.update();
  ball2.update();
  imgx++;
  imgy++;
  Vec3 v3(xmouse-w/2,ymouse-h/2,0);
  Vec3 mouse3dpos = v3.getMousePos();
  //if(m_buttonleft)putlevel(mouse3dpos.getx(),8,mouse3dpos.getz(),4);
}
void Game::render(){
  screen->clear(0);
  screen->clearzbuffer();
  ball2.render(screen);
  ball.render(screen);
  if(swp)screen->swap();
  for(int i = 0;i < w*h;i++)pixels[i] = screen->getRaster()[i];
  SDL_UpdateTexture(texture,nullptr,pixels,4*w);
  SDL_RenderCopy(renderer,texture,nullptr,nullptr);
  SDL_RenderPresent(renderer);
}
void Game::close(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  //SDL_DestroyTexture(image);
  screen->clean();
  delete screen;
  delete bitmap;
  delete text;
}
