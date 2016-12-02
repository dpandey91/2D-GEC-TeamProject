#include <cmath>
#include "viewport.h"
#include "smartSprite.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

SmartSprite::SmartSprite(const Ghost& ghost, Player& p) :
 Ghost(ghost), 
 player(p), 
 currentMode(NORMAL),
 bulletName("ghostb"),
 bulletSpeed(Gamedata::getInstance().getXmlInt(bulletName+"/bulletSpeed")),
 bullets(bulletName),
 safeDistance(Gamedata::getInstance().getXmlInt(bulletName+"/safeDistance")),
 bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/bulletInterval")),
 timeSinceLastBullet(0)
{ }

void SmartSprite::goLeft()  { 
  if (X() > 0) velocityX( -abs(velocityX()) ); 
}
void SmartSprite::goRight() { velocityX( fabs(velocityX()) ); }
void SmartSprite::goUp()    { velocityY( -fabs(velocityY()) ); }
void SmartSprite::goDown()  { velocityY( fabs(velocityY()) ); }

void SmartSprite::draw() const {
  Ghost::draw();
  bullets.draw();
}

void SmartSprite::update(Uint32 ticks) {
    
  Vector2f playerPos = getPosition();
  Vector2f ghostPos = player.getPosition();
  
  bool bShoot = true;
  if(abs(ghostPos[0] - playerPos[0]) < 200 && (abs(ghostPos[1] - playerPos[1]) || abs(ghostPos[1] - (playerPos[1] + player.getFrame()->getHeight())) < 30)){
     bShoot = true;
  }
  
  if  ( currentMode == NORMAL ) {
    if(bShoot) {currentMode = SHOOT;}
  }
  else if  ( currentMode == SHOOT ) {
    if(!bShoot) currentMode = NORMAL;
  }
  
  Ghost::update(ticks);
  bullets.update(ticks, getPosition());
  
  if(currentMode == SHOOT && (timeSinceLastBullet > bulletInterval) && !static_cast<Drawable*>(&player)->isObjExploded()){
       shoot();
       //manageEnemy();
  }  
  
  timeSinceLastBullet +=ticks;
}

void SmartSprite::shoot(){
    Vector2f vel = getVelocity();
    Vector2f pos = getPosition();
    float x;
    float y = Y()+ frameHeight/2 - 20;
    //std::cout << "Vel: " << vel[0] << std::endl;
    if(X() < player.X()) {     
      x = X() + frameWidth - 40;
      vel[0] += bulletSpeed;
    }
    else {
      x=X();
      vel[0] -= bulletSpeed;
    }
    vel[1] *=0;
  
    bullets.shoot(Vector2f(x,y), vel);
    timeSinceLastBullet = 0;
}

int getAbs(int x1, int x2){
	return abs(x1-x2);
}

bool SmartSprite::collidedWithBullets(const Drawable* d) {
  return bullets.collidedWith(d);
}
