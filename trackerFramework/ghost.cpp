#include "ghost.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "health.h"
#include "explodingSprite.h"
#include "vector2f.h"

Ghost::Ghost( const std::string& name) :
  Sprite(name),
  currState(WALK),
  yBound(Gamedata::getInstance().getXmlInt("ghost/yBound")),
  minxAdd(Gamedata::getInstance().getXmlInt("ghost/xAdd/min")),
  maxxAdd(Gamedata::getInstance().getXmlInt("ghost/xAdd/max")),
  minyAdd(Gamedata::getInstance().getXmlInt("ghost/yAdd/min")),
  maxyAdd(Gamedata::getInstance().getXmlInt("ghost/yAdd/max")),
  explosion(NULL)
{}

Ghost::Ghost(const std::string& name, const Vector2f& pos, const Vector2f& vel):
  Sprite(name, pos, vel,
         FrameFactory::getInstance().getFrame(name)),
  currState(WALK),
  yBound(Gamedata::getInstance().getXmlInt("ghost/yBound")),
  minxAdd(Gamedata::getInstance().getXmlInt("ghost/xAdd/min")),
  maxxAdd(Gamedata::getInstance().getXmlInt("ghost/xAdd/max")),
  minyAdd(Gamedata::getInstance().getXmlInt("ghost/yAdd/min")),
  maxyAdd(Gamedata::getInstance().getXmlInt("ghost/yAdd/max")),
  explosion(NULL)
{}

Ghost::Ghost(const std::string& name, const Vector2f& pos, const Vector2f& vel, const Frame* frm):
  Sprite(name, pos, vel, frm),
  currState(WALK),
  yBound(Gamedata::getInstance().getXmlInt("ghost/yBound")),
  minxAdd(Gamedata::getInstance().getXmlInt("ghost/xAdd/min")),
  maxxAdd(Gamedata::getInstance().getXmlInt("ghost/xAdd/max")),
  minyAdd(Gamedata::getInstance().getXmlInt("ghost/yAdd/min")),
  maxyAdd(Gamedata::getInstance().getXmlInt("ghost/yAdd/max")),
  explosion(NULL)
{ }

Ghost::Ghost(const Ghost& s) :
  Sprite(s),
  currState(s.currState),
  yBound(s.yBound),
  minxAdd(s.minxAdd),
  maxxAdd(s.maxxAdd),
  minyAdd(s.minyAdd),
  maxyAdd(s.maxyAdd),
  explosion(NULL)
{}

Ghost& Ghost::operator=(const Ghost& rhs){
    if(this != &rhs){
      Sprite::operator=(rhs);
      currState = rhs.currState;
      yBound = rhs.yBound;
      minxAdd = rhs.minxAdd;
      maxxAdd = rhs.maxxAdd;
      minyAdd = rhs.minyAdd;
      maxyAdd = rhs.maxyAdd;
      explosion = rhs.explosion;
    }
    
    return *this;
}

Ghost::~Ghost() {
  if(explosion){
    delete explosion;
    explosion = NULL;
  }
}

void Ghost::resetPosition(){
   
  Vector2f position(Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/x"), Gamedata::getInstance().getXmlInt(getName()+      "/endLoc/x")), Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y"), Gamedata::getInstance().getXmlInt(getName()+"/endLoc/y")));setPosition(position);
  bExploded = false;
  currState = WALK;
}

void Ghost::initPosition(){
   X(getPosition()[0] + Gamedata::getInstance().getRandInRange(minxAdd, maxxAdd));
   Y(getPosition()[1] + Gamedata::getInstance().getRandInRange(minyAdd, maxyAdd));
   bExploded = false;
   currState = WALK;
}

void Ghost::setState(int state){
  currState = state;
}

void Ghost::stop(){
    
  if(Y()>worldHeight-frameHeight)
      Y(worldHeight-frameHeight);  
  
  currState = VANISH;
}

void Ghost::draw() const {
    
  if(currState == EXPLODE && explosion && explosion->chunkCount() != 0){
    explosion->draw();
  }
  else if(currState != VANISH){
    Sprite::draw();  
  }
}

void Ghost::update(Uint32 ticks) {
  if(currState == EXPLODE && explosion){
      explosion->update(ticks);
      if(explosion->chunkCount() == 0){
          currState = VANISH;
          initPosition();
      }
      return;
  }
  Sprite::update(ticks);
  
  if(bComeback){
    if ( Y() > yBound) {
        velocityY( -abs( velocityY() ) );
    }
  }
}

void Ghost::explode(){
    if(!explosion){
        explosion = new ExplodingSprite(*this);
    }
    explosion->resetChunks(getPosition());
    currState = EXPLODE;
    bExploded = true;
}

void Ghost::increaseVelocity(float scale){
    setVelocity(getVelocity()*scale);
}

void Ghost::decreaseVelocity(float scale){
    setVelocity(getVelocity()/scale);
}
