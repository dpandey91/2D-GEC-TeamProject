#include <iostream>
#include <cmath>
#include "multibullet.h"
#include "gamedata.h"
#include "collisionStrategy.h"

MultiBullet::MultiBullet(const std::string name, const Vector2f& pos, const Vector2f& vel):
  TwoWayMultiSprite(name, pos, vel),
  maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")),
  tooFar(false),
  strategy()
{ }

MultiBullet::MultiBullet(const MultiBullet& mb):
  TwoWayMultiSprite(mb),
  maxDistance(mb.maxDistance),
  tooFar(mb.tooFar),
  strategy(mb.strategy)
{}

MultiBullet::~MultiBullet()
{}
 
void MultiBullet::reset(){
  tooFar = false;
}

void MultiBullet::update(Uint32 ticks, const Vector2f& pPos) {
  
  Vector2f position = getPosition();
  if(Y()+frameHeight < 0 || Y() > worldHeight || X() < 0 || X() > worldWidth || position[0] > pPos[0] + maxDistance)
    tooFar = true;

  MultiSprite::update(ticks);
}

bool MultiBullet::collidedWith(const Drawable* d) {
  return strategy.execute(*this, *d);
}

void MultiBullet::advanceFrame(Uint32 ticks) {
}

void MultiBullet::increaseFrame(int cFrame){
  if(velocityX() >= 0){
    currentFrame = (currentFrame+1) % (numberOfFrames/2);
  }
  else {
    if(currentFrame > numberOfFrames/2){
      currentFrame =  (currentFrame+1) % numberOfFrames;
    }
    if(currentFrame < numberOfFrames/2){
      currentFrame = (currentFrame + (numberOfFrames/2) + 1) % numberOfFrames;
    }
  }
}