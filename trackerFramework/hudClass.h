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
  static HudClass& getInstance();
  ~HudClass();
  
  void drawHud(SDL_Surface* const, const IOManager&, int seconds, int fps) const;

private:
  const int hudWidth;
  const int hudHeight;
  int xPos;
  int yPos;
  color rgbVal;
  
  HudClass();
  HudClass(const HudClass&);
  HudClass& operator=(const HudClass&);
};
#endif
