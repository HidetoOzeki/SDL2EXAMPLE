#include "Game.h"
Game* game;
int main(int arg,char* args[]){
  game = new Game();
  game->init(320,240,2);
  int fps = 0;
  int tps = 0;
  double ms = 1000.0/60.0;
  double delta = 0;
  double last = SDL_GetTicks();
  double timer = SDL_GetTicks();
  while(game->isRunning()){
    double now = SDL_GetTicks();
    delta+=(now-last)/ms;
    last = now;
    if(delta>=1){
      game->input();
      game->update();
      tps++;
      delta--;
    }else{
    game->render();
    fps++;
    }
    if(timer+1000 <= SDL_GetTicks()){
      timer+=1000;
      std::cout << "fps : " << fps << " tps : "<< tps << std::endl;
      tps = 0;
      fps = 0;
    }
  }
  game->close();
  return 0;
}
