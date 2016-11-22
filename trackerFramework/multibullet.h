#ifndef MULTIBULLET_H
#define MULTIBULLET_H

#include <string>
#include "twoWayMultisprite.h"
#include "collisionStrategy.h"

class MultiBullet: public TwoWayMultiSprite {
    
public:
  MultiBullet(const std::string, const Vector2f&, const Vector2f&);
  MultiBullet(const MultiBullet&);
  virtual ~MultiBullet();
  
  void update(Uint32 ticks, const Vector2f& pPos);
  virtual bool collidedWith(const Drawable* d);  
  
  void reset();
  bool isTooFar() const {return tooFar;}
  void setStrategy(CollisionStrategy* aStrategy);
  void increaseFrame(int cFrame = -1);
  
private:
  float maxDistance;
  bool tooFar;
  MidPointCollisionStrategy strategy;

  virtual void advanceFrame(Uint32 ticks);  
  MultiBullet& operator=(const MultiBullet&);
};

#endif //MULTIBULLET_H