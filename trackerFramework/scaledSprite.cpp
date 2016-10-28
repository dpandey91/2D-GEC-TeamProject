#include <iostream>

#include "scaledSprite.h"
#include "frameFactory.h"

ScaledSprite::ScaledSprite(const std::string& name, const Vector2f& pos, const Vector2f& vel, float aScale, const int iter) :
  Sprite(Gamedata::getInstance().getXmlBool(name+"/comeback"),
         name,
         pos,
         vel,
         FrameFactory::getInstance().getScaledFrame(name, aScale, iter)),
  scale(aScale)
{}

ScaledSprite::ScaledSprite(const std::string& name, const Vector2f& pos, const Vector2f& vel, const Frame* frm, float aScale) :
  Sprite(Gamedata::getInstance().getXmlBool(name+"/comeback"),
         name, pos, vel, frm),
  scale(aScale)
{ }

ScaledSprite::ScaledSprite(const ScaledSprite& s) :
  Sprite(s), 
  scale(s.scale)
{ }

ScaledSprite& ScaledSprite::operator=(const ScaledSprite& rhs) {
    if(this != &rhs){
      Sprite::operator=(rhs);
      scale = rhs.scale;
    }
    return *this;
}

ScaledSprite::~ScaledSprite() 
{}