#ifndef GHOST_MANAGER_H
#define GHOST_MANAGER_H

#include <list>
#include <string>
#include "stdint.h"
#include "viewport.h"

class Ghost;
class Player;

class GhostManager{
public:    
  GhostManager();
  GhostManager(const GhostManager& g);
  ~GhostManager();
  
  void makeGhosts();
  void draw() const;
  void update(unsigned int ticks);
  bool checkForCollisions(Player* player);
  void reset();
  
private:
  Viewport& viewport;
  std::string name;
  std::list<Ghost*> dumbGhosts;
  
  Vector2f getScaledPosition(Vector2f position, float cushion);
};


#endif //GHOST_MANAGER_H