#ifndef HUDCLASS__H
#define HUDCLASS__H
#include <string>
#include <SDL.h>
#include "ioManager.h"

typedef struct colorCode{
  int red;
  int green;
  int blue;

  colorCode() : red(255), green(255), blue(255) {}
  colorCode(int r, int g, int b) : red(r), green(g), blue(b) {}
} color;


class HudClass {
public:
  HudClass();
  void drawHud(SDL_Surface * const&, const IOManager&, int seconds, int fps, int health) const;

  void drawLose(SDL_Surface * const& screen, const IOManager& io) const;
  void drawWin(SDL_Surface * const& screen, const IOManager& io) const;
  
private:
  const int hudWidth;
  const int hudHeight;
  int xPos;
  int yPos;
  color rgbVal;
};
#endif
