#include "player.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "health.h"
#include "explodingSprite.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  currState(IDLE),
  keyPressed(false),
  keyPresseda(false),
  keyPresseds(false),
  keyPressedd(false),
  keyPressedw(false),
  yBound(Gamedata::getInstance().getXmlInt("boy/yBound")),
  bulletName("bullet"),
  bulletSpeed(Gamedata::getInstance().getXmlInt(bulletName+"/bulletSpeed")),
  bullets(bulletName),
  isExploding(false),
  explosion(NULL),
  strategy()
{}

Player::Player(const Player& s) :
  TwoWayMultiSprite(s),
  currState(s.currState),
  keyPressed(s.keyPressed),
  keyPresseda(s.keyPresseda),
  keyPresseds(s.keyPresseds),
  keyPressedd(s.keyPressedd),
  keyPressedw(s.keyPressedw),
  yBound(s.yBound),
  bulletName(s.bulletName),
  bulletSpeed(s.bulletSpeed),
  bullets(s.bullets),
  isExploding(s.isExploding),
  explosion(NULL),
  strategy(s.strategy)
{}

Player::~Player(){
    if(explosion){
        delete explosion;
        explosion = NULL;
    }
}

void Player::resetPosition(){
   X(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/x"));
   Y(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y"));
   setVelocity(Vector2f(Gamedata::getInstance().getXmlInt(getName()+"/speedX"),
                    Gamedata::getInstance().getXmlInt(getName()+"/speedY")));
   bullets.reset();
   isExploding = false;
   explosion = NULL;
   setState(WALK);
} 

void Player::setState(int state){
  currState = state;
}

void Player::stop(){
    
  keyPressed = false;
  keyPresseda = false;
  keyPressedd = false;
  keyPressedw = false;
  keyPresseds = false;
  
  if(Y() > worldHeight-frameHeight)
      Y(worldHeight-frameHeight);  
  
  setState(IDLE);
}

void Player::moveLeft(){
  keyPressed = true;
  keyPresseda = true;
  setState(WALK);
}

void Player::moveRight(){
  keyPressed = true;
  keyPressedd = true;
  setState(WALK);
}

void Player::moveUp(){
  keyPressed = true;
  keyPressedw = true;
  setState(WALK);
}

void Player::moveDown(){
  keyPressed = true;
  keyPresseds = true;
  setState(WALK);
}

void Player::move(const float& incr){
    if(keyPresseda){
        if( X() > 0){
            X(X() + velocityX()*incr); 
            velocityX( -abs( velocityX() ) );
        }
    }
        
    if(keyPressedd){
        if( X() < worldWidth-frameWidth){
             X(X() + velocityX()*incr);     
             velocityX( abs( velocityX() ) );
        }
    }
    
    if(keyPressedw){
        if( Y() > yBound){
            Y(Y() + velocityY()*incr);     
            velocityY( -abs( velocityY() ) ); 
        }
    }
        
    if(keyPresseds){
        if( Y() < worldHeight-frameHeight){
             Y(Y() + velocityY()*incr);
             velocityY( abs( velocityY() ) );
        }
    }        
}

void Player::draw() const{
  if(currState == EXPLODE && explosion && explosion->chunkCount() != 0){
    explosion->draw();
  }
  else if(currState != VANISH){
    TwoWayMultiSprite::draw();
    bullets.draw();
  }
}

void Player::update(Uint32 ticks) {
  if(explosion){
      explosion->update(ticks);
      if(explosion->chunkCount() == 0){
          delete explosion;
          explosion = NULL;
          currState = IDLE;
          bExploded = false;
      }
      return;
  }
  else if(currState != VANISH){
    bullets.update(ticks, getPosition());
    if(Health::getInstance().getHealth() > 0){
      if(currState == WALK){
        float incr =  static_cast<float>(ticks) * 0.0005;
        move(incr);
        advanceFrame(ticks);
      }
      else{
        if(velocityX() >= 0){
          currentFrame = 2;
        }
        else{
          currentFrame = 2+numberOfFrames/2;
        }
      }
    }    
  }
}

void Player::increaseVelocity(float scale){
    setVelocity(getVelocity()*scale);
}

void Player::decreaseVelocity(float scale){
    setVelocity(getVelocity()/scale);
}

void Player::shoot(){
  if((currState == IDLE || currState == WALK) && (Health::getInstance().getHealth() > 0))
  {
    Vector2f vel = getVelocity();
    float x;
    float y = Y()+ frameHeight/2;
    if(currentFrame < numberOfFrames/2) {        
      x = X() + frameWidth - 40;
      vel[0] += bulletSpeed;
    }
    else {
      x=X();
      vel[0] -= bulletSpeed;
    }
    vel[1] *=0;
  
    bullets.shoot(Vector2f(x,y), vel);
  }
}

void Player::explode(){
    if(!explosion){
        explosion = new ExplodingSprite(Sprite(getName(), getPosition(), getVelocity(), frames[currentFrame]));
    }
    currState = EXPLODE;
    bExploded = true;
}

bool Player::collidedWithBullets(const Drawable* d) {
  return bullets.collidedWith(d);
}

bool Player::collidedWith(const Drawable* d) {
  bool bRet = false;
  bRet = strategy.execute(*this, *d);
  if(bRet){
    if(!isExploding){
      Health::getInstance().update();
      isExploding = true;    
    }
  }
  else{
    isExploding = false;
  }
  return bRet;
}



