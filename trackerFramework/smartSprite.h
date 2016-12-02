#include <iostream>
#include "ghost.h"
#include "ioManager.h"
#include "bulletsPool.h"
#include "player.h"

class SmartSprite : public Ghost {
public:
  SmartSprite(const Ghost& ghost, Player& p);
  void draw() const;
  void update(Uint32 ticks);
  void goLeft();
  void goRight();
  void goUp();
  void goDown();
  
  void shoot();
  void manageEnemy();
  
  bool collidedWithBullets(const Drawable* d);
  void makeDumb(){ isDumb = true;}
  void makeSmart(){ isDumb = false;}

  //static void incrSafeDistance() {++safeDistance; }
  //static void decrSafeDistance() { --safeDistance; }
  //static float getSafeDistance() { return safeDistance; }

private:	
  enum MODE {NORMAL, SHOOT, EVADE};
  Player& player;
  MODE currentMode;
  
  //MultiBullet
  std::string bulletName;
  float bulletSpeed;
  BulletsPool bullets;
  
  int safeDistance;
  int bulletInterval;
  int timeSinceLastBullet;
  
  bool isDumb;
  
  SmartSprite(const SmartSprite &);
  SmartSprite& operator=(const SmartSprite &rhs);
};
