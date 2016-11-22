#include <iostream>
#include <cmath>
#include "multibullet.h"
#include "gamedata.h"
#include "collisionStrategy.h"

MultiBullet::MultiBullet(const std::string& name, const Vector2f& pos, const Vector2f& vel):
  MultiSprite(name, pos, vel),
  maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")),
  tooFar(false),
  strategy(new MidPointCollisionStrategy())
{ }

MultiBullet::MultiBullet(const MultiBullet& mb):
  MultiSprite(mb),
  maxDistance(mb.maxDistance),
  tooFar(mb.tooFar),
  strategy(new MidPointCollisionStrategy())
{ }

MultiBullet::~MultiBullet(){
  if(strategy){
    delete strategy;
    strategy = NULL;
  }
}
 
void MultiBullet::reset(){
  tooFar = false;
}

void MultiBullet::setStrategy(CollisionStrategy* aStrategy){
    strategy = aStrategy;
}

void MultiBullet::update(Uint32 ticks, const Vector2f& pPos) {
  
  Vector2f position = getPosition();
  if(Y()+frameHeight < 0 || Y() > worldHeight || X() < 0 || X() > worldWidth || position[0] > pPos[0] + maxDistance)
    tooFar = true;

  MultiSprite::update(ticks);
}

bool MultiBullet::collidedWith(const Drawable* d) {
  bool bRet = false;
  if(strategy){
    bRet = strategy->execute(*this, *d);
  }
  return bRet;
}
