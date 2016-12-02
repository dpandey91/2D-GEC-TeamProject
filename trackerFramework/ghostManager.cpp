#include "ghostManager.h"
#include "gamedata.h"
#include "ghost.h"
#include "smartSprite.h"

GhostManager::GhostManager(Player& p):
  viewport(Viewport::getInstance()),
  name("ghost"),
  dumbGhosts(),
  smartGhosts(),
  player(p),
  noOfExplosions(0)
{}

GhostManager::GhostManager(const GhostManager& g):
  viewport(g.viewport),
  name(g.name),
  dumbGhosts(g.dumbGhosts),
  smartGhosts(g.smartGhosts),
  player(g.player),
  noOfExplosions(g.noOfExplosions)
{}

GhostManager::~GhostManager(){
  std::list<Ghost*>::iterator iter = dumbGhosts.begin();
  while(iter != dumbGhosts.end()){
    delete *iter;
    ++iter;
  }
  
  iter = smartGhosts.begin();
  while(iter != smartGhosts.end()){
    delete *iter;
    ++iter;
  }
  dumbGhosts.clear();
  smartGhosts.clear();
}

void GhostManager::makeGhosts(){
  //Creating ghosts
  int noOfGhosts = Gamedata::getInstance().getXmlInt(name+"/noOfObjects");
  Ghost* ghostSprite = NULL;
  Vector2f velocity(Gamedata::getInstance().getXmlFloat(name+"/speed/x"), Gamedata::getInstance().getXmlFloat(name+"/speed/y"));
  for(int i =0; i < noOfGhosts; i++){
  
    Vector2f position(Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), Gamedata::getInstance().getXmlInt(name+      "/endLoc/x")), Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(name+"/startLoc/y"), Gamedata::getInstance().getXmlInt(name+"/endLoc/y")));
                     
   // if(!ghostSprite){
        ghostSprite = new Ghost(name, position, velocity);
        dumbGhosts.push_back(ghostSprite);
    //}
    //else{
    //    dumbGhosts.push_back(new Ghost(ghostSprite->getName(), position, velocity, ghostSprite->getFrames()));   
    //}
  }
}

void GhostManager::draw() const{
  std::list<Ghost*>::const_iterator ptr = dumbGhosts.begin();  
  while(ptr != dumbGhosts.end()) {
    (*ptr)->draw();
    ptr++;
  }
  
  if(noOfExplosions >= 5){
      //std::cout << "draw smart ghost" << std::endl;
      ptr = smartGhosts.begin();  
      while(ptr != smartGhosts.end()) {
        (*ptr)->draw();
        ptr++;
      }
  }
}

void GhostManager::update(unsigned int ticks){
  std::list<Ghost*>::const_iterator ptr = dumbGhosts.begin();
  while(ptr != dumbGhosts.end()) {
     (*ptr)->update(ticks);
     updateGhost(*ptr);   
     ptr++;
  }
  
  if(noOfExplosions >= 5){
    ptr = smartGhosts.begin();
    while(ptr != smartGhosts.end()) {
     (*ptr)->update(ticks);
     updateGhost(*ptr);   
     ptr++;
    }   
  }
}

void GhostManager::updateGhost(Ghost* ghost){
     float x1 = viewport.X();
     float x2 = viewport.X() + viewport.getWidth();
     float y2 = viewport.Y() + viewport.getHeight();
     
     Vector2f objectVel = viewport.getObjectVelocity();
     
     if(ghost->X() < (x1 - 40) || ghost->X() > (x2 + 40)){
        if(objectVel[0] < 0){
            ghost->setPosition(getScaledPosition(Vector2f(x1-40, Gamedata::getInstance().getRandFloat(150, y2)), 40));
        }
        else{
            ghost->setPosition(getScaledPosition(Vector2f(x2+40, Gamedata::getInstance().getRandFloat(150, y2)), 40));
        }
     }
     if(objectVel[0] < 0){
         ghost->velocityX(abs(ghost->velocityX()));
     }
     else {
         ghost->velocityX(-abs(ghost->velocityX()));
     }
}

Vector2f GhostManager::getScaledPosition(Vector2f position, float cushion)
{
  Vector2f startVel = position - cushion;
  Vector2f endVel = position + cushion;
  Vector2f temp (Gamedata::getInstance().getRandFloat(startVel[0],endVel[0]), Gamedata::getInstance().getRandFloat(startVel[1], endVel[1]));
  return temp;
}

bool GhostManager::checkForCollisions(Player* player1) {
  std::list<Ghost*>::iterator iter = dumbGhosts.begin();
  bool bExplode = false;
  while ( iter != dumbGhosts.end() ) {
    if((*iter)->isObjExploded() || (*iter)->X() < viewport.X() || (*iter)->X() > viewport.X() + viewport.getWidth()) {
        ++iter;
    }
    else if (player1->collidedWithBullets(*iter)){
        (*iter)->explode();
        noOfExplosions++;
        bExplode = true;
        ++iter;
    }
    else ++iter;    
  }
  
  iter = smartGhosts.begin();
  while(iter != smartGhosts.end()){
    if(static_cast<SmartSprite*>(*iter)->collidedWithBullets(player1)){
        if(!player1->isObjExploded())
            player1->explode();
        break;
    }
    ++iter;
  }
  
  return bExplode;
}

void GhostManager::reset(){
  std::list<Ghost*>::iterator iter = dumbGhosts.begin();
  while ( iter != dumbGhosts.end() ) {
    (*iter)->resetPosition();
    ++iter;
  }
}

void GhostManager::makeSmartGhost(){
    std::list<Ghost*>::iterator iter = dumbGhosts.begin();
    int i = 0; int size = dumbGhosts.size()/2;
    while(i < size){
        SmartSprite* sm = new SmartSprite(*(*iter), player);
        smartGhosts.push_back(sm);
        ++iter;
        ++i;
        break;
    }
}

void GhostManager::shoot(){
    std::list<Ghost*>::iterator iter = smartGhosts.begin();
    while(iter != smartGhosts.end()){
        static_cast<SmartSprite*>(*iter)->shoot();
        break;
    }
}