#ifndef GHOST_MANAGER_H
#define GHOST_MANAGER_H

#include <list>
#include <string>
#include "stdint.h"
#include "viewport.h"
#include "player.h"

class Ghost;
class GhostManager{
public:    
  GhostManager(Player& player);
  GhostManager(const GhostManager& g);
  ~GhostManager();
  
  void makeGhosts();
  void makeSmartGhost();
  
  void draw() const;
  void update(unsigned int ticks);
  bool checkForCollisions(Player* player);
  void reset();
  
  void shoot();
  
  int getNoOfExplosions(){ return noOfExplosions; }
  
private:
  Viewport& viewport;
  std::string name;
  std::list<Ghost*> dumbGhosts;
  std::list<Ghost*> smartGhosts;
  
  Player& player;
  int noOfExplosions;
  Vector2f getScaledPosition(Vector2f position, float cushion);
  void updateGhost(Ghost* ghost);
};


#endif //GHOST_MANAGER_H