#ifndef HEALTH__H
#define HEALTH__H

#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"

class Health {
public:
  static Health& getInstance();
  
  void draw() const;
  void update();
  void reset() { currentLength = totalLength; }
  int getHealth() { return currentLength; }
  
private:
  SDL_Surface* screen;
  Vector2f start;
  int totalLength;
  int currentLength;
  int thick;
  int increments;
  float interval;
  int deltaTime;
  const Uint32 GREEN;
  const Uint32 GRAY;
  const Uint32 BLACK;
  const Uint32 color;
  void drawBox() const;
  
  Health();
  Health(int sx, int sy, int tl, int cl, 
         float t, int inc, Uint32 c, float sp);
  Health(const Health&);
  Health& operator=(const Health&);
};

#endif
