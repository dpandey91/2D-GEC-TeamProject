#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "twoWayMultiSprite.h"

class Player : public TwoWayMultiSprite {
public:

  Player(const std::string&);
  Player(const Player&);
  virtual ~Player() { };

  virtual void update(Uint32 ticks);
  void resetPosition();
  void setState(int state);
  
  void stop();
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
  
  void increaseVelocity(float scale);
  void decreaseVelocity(float scale);

private:
  enum PLAYER_STATES{
      IDLE,
      WALK
  };
  
  void move(const float& incr);
  int currState;
  bool keyPressed;
  bool keyPresseda;
  bool keyPresseds;
  bool keyPressedd;
  bool keyPressedw;
};

#endif
