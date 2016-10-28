#ifndef SCALEDSPRITE__H
#define SCALEDSPRITE__H

#include "sprite.h"

class ScaledSprite : public Sprite {
public:
  ScaledSprite(const std::string& name, const Vector2f& pos, const Vector2f& vel, float aScale, const int iter);
  ScaledSprite(const std::string& name, const Vector2f& pos, const Vector2f& vel, const Frame* frm, float aScale);
  ScaledSprite(const ScaledSprite& s);
  ~ScaledSprite();

  ScaledSprite& operator=(const ScaledSprite&);
  
  bool operator<(const ScaledSprite& rhs) const {
    return scale < rhs.scale;
  }

  float getScale() const { return scale; }

private:
  float scale;
};
#endif
