#ifndef MULTIBULLET_H
#define MULTIBULLET_H

#include <string>
#include "multisprite.h"

class CollisionStrategy;
class MultiBullet: public MultiSprite {
    
public:
  MultiBullet(const std::string&, const Vector2f&, const Vector2f&);
  MultiBullet(const MultiBullet&);
  virtual ~MultiBullet();
  
  void update(Uint32 ticks, const Vector2f& pPos);
  virtual bool collidedWith(const Drawable* d);  
  
  void reset();
  bool isTooFar() const {return tooFar;}
  void setStrategy(CollisionStrategy* aStrategy);
  
private:
  float maxDistance;
  bool tooFar;
  CollisionStrategy* strategy;
    
  MultiBullet& operator=(const MultiBullet&);
};

#endif //MULTIBULLET_H