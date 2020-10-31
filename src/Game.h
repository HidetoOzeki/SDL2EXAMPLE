#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include "gfx/Bitmap.h"
#include "gfx/Screen.h"
class Game {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  bool running;
  Uint32* pixels;
  Screen* screen;
  int w,h;
  int xmouse,ymouse;
  int pxmouse,pymouse;
  bool m_buttonright,m_buttonleft;
  int scale = 2;
  int level[10*10*10];
public:
  Game();
  ~Game();
  void init(const int width,const int height,int scale);
  void input();
  void update();
  void render();
  void close();
  void test1(int x,int y,int xo,int yo);
  void putlevel(int x,int y,int z,int id);

  bool isRunning(){return running;}
};
#endif
