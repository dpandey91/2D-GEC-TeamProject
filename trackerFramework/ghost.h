#ifndef Ghost__H
#define Ghost__H
#include <string>
#include <vector>
#include "sprite.h"

class ExplodingSprite;
class Ghost : public Sprite {
public:

  Ghost(const std::string&);
  Ghost(const std::string& name, const Vector2f& pos, const Vector2f& vel);
  Ghost(const std::string& name, const Vector2f& pos, const Vector2f& vel, const Frame* frm);
  Ghost(const Ghost&);
  Ghost& operator=(const Ghost& rhs);
  
  virtual ~Ghost();

  void resetPosition();
  void initPosition();
  void setState(int state);
    
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual void explode();
  
  void stop();
  
  void increaseVelocity(float scale);
  void decreaseVelocity(float scale);

private:
  enum Ghost_STATES{
      WALK,
      SHOOT,
      EXPLODE,
      VANISH
  };
  
  int currState;
  int yBound;
  int minxAdd;
  int maxxAdd;
  int minyAdd;
  int maxyAdd;
  ExplodingSprite* explosion;
};

#endif
