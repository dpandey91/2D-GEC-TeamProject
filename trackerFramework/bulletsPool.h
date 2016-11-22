#ifndef BULLETS_POOL_H
#define BULLETS_POOL_H

#include <list>
#include "multibullet.h"

class BulletsPool {
    
public:
  BulletsPool(const std::string &);
  BulletsPool(const BulletsPool&);
  ~BulletsPool(){}
  
  void draw() const;
  
  void update(Uint32 ticks, const Vector2f& pPos);
  void shoot(const Vector2f& pos, const Vector2f& vel);
  bool collidedWith(const Drawable* obj);
  
  bool canShoot() const { return !bulletList.empty();}
  unsigned int getBulletlistCount() const {return bulletList.size();}
  unsigned int getFreelistCount() const {return freeList.size();}
  
  void reset();
private:
  std::string name;
  int maxBullet;
   
  std::list<MultiBullet> bulletList;
  std::list<MultiBullet> freeList;
};

#endif //#ifndef MULTIBULLET_H
