#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "gfx/Vec3.h"
#include "gfx/Text.h"
Bitmap* bitmap;
Text* text;
Game::Game(){}
Game::~Game(){}
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
  SDL_GL_SetSwapInterval(0);
  running = true;
}
int xwindow,ywindow;
bool wpressed = false;
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
  if(KEYS[SDL_SCANCODE_W]){
    std::cout << "W key pressed" << std::endl;
    wpressed = !wpressed;
  }
}
void Game::update(){
}
void Game::render(){
  screen->clear(0);
  screen->clearzbuffer();
  text->render("this is a text rendering (1337)",screen,32,h/2);
  if(wpressed)text->render("wpressed",screen,32,h/3);
  for(int i = 0;i < w*h;i++)pixels[i] = screen->getRaster()[i];
  SDL_UpdateTexture(texture,nullptr,pixels,4*w);
  SDL_RenderCopy(renderer,texture,nullptr,nullptr);
  SDL_RenderPresent(renderer);
}
void Game::close(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  screen->clean();
  delete screen;
  delete bitmap;
  delete text;
}
