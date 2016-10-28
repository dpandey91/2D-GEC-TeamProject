#include "player.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "health.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  currState(IDLE),
  keyPressed(false),
  keyPresseda(false),
  keyPresseds(false),
  keyPressedd(false),
  keyPressedw(false)
{}

Player::Player(const Player& s) :
  TwoWayMultiSprite(s),
  currState(IDLE),
  keyPressed(false),
  keyPresseda(false),
  keyPresseds(false),
  keyPressedd(false),
  keyPressedw(false)
{}

void Player::resetPosition(){
   X(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/x"));
   Y(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y")); 
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
  
  if(Y()>worldHeight-frameHeight)
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
        if( Y() >0){
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

void Player::update(Uint32 ticks) {
  
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

void Player::increaseVelocity(float scale){
    setVelocity(getVelocity()*scale);
}

void Player::decreaseVelocity(float scale){
    setVelocity(getVelocity()/scale);
}



