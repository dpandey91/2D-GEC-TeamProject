#include "health.h"

Health& Health::getInstance(){
    static Health instance;
    return instance;
}

Health::Health() :
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(Gamedata::getInstance().getXmlInt("healthBar/startLoc/x"), Gamedata::getInstance().getXmlInt("healthBar/startLoc/x"))), 
  totalLength(Gamedata::getInstance().getXmlInt("healthBar/length")), 
  currentLength(Gamedata::getInstance().getXmlInt("healthBar/length")), 
  thick(Gamedata::getInstance().getXmlInt("healthBar/thick")), 
  increments(Gamedata::getInstance().getXmlInt("healthBar/increment")),
  interval(1000),
  deltaTime(0),
  GREEN( SDL_MapRGB(screen->format, 0x00, 0xff, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xce, 0xb4, 0xb4) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
  color(GREEN) {
}

Health::Health(int sx, int sy, int tl, int cl,
               float t, int inc, Uint32 c, float sp):
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(sx, sy)), 
  totalLength(tl), 
  currentLength(cl), 
  thick(t), 
  increments(inc),
  interval(sp),
  deltaTime(0),
  GREEN( SDL_MapRGB(screen->format, 0x00, 0xff, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xff, 0xff, 0xff) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
  color(c) {
}

void Health::drawBox() const {
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+totalLength, start[1], 
                      thick, GRAY);
  // Two Horizontal lines
  Draw_AALine(screen, start[0], start[1]-8, 
                      start[0]+totalLength, start[1]-8, 
                      1.0, BLACK);
  Draw_AALine(screen, start[0], start[1]+8, 
                      start[0]+totalLength, start[1]+8, 
                      1.0, BLACK);
  // Two Vertical lines
  Draw_AALine(screen, start[0]-1, start[1]-8, 
                      start[0]-1, start[1]+8, 
                      2.0, BLACK);
  Draw_AALine(screen, start[0]+totalLength+1, start[1]-8, 
                      start[0]+totalLength+1, start[1]+8, 
                      2.0, BLACK);
}

void Health::draw() const {
  drawBox();
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+currentLength, start[1], 
                      thick, color);
}

void Health::update() {
  
  if ( currentLength > 0) {
    deltaTime = 0;
    currentLength -= increments;
  }
}
