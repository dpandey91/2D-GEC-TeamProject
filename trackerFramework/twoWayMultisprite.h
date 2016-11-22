#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include "multisprite.h"

class TwoWayMultiSprite : public MultiSprite {
public:
  TwoWayMultiSprite(const std::string&);
  TwoWayMultiSprite( const std::string& name, const Vector2f& pos, const Vector2f& vel);
  TwoWayMultiSprite(const TwoWayMultiSprite&);
  virtual ~TwoWayMultiSprite() { };

  //virtual void explode(){};
protected:
  virtual void advanceFrame(Uint32 ticks);
};
#endif
