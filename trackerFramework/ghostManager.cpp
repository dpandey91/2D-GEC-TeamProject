#include "ghostManager.h"
#include "gamedata.h"
#include "player.h"
#include "ghost.h"

GhostManager::GhostManager():
  viewport(Viewport::getInstance()),
  name("ghost"),
  dumbGhosts()
{}

GhostManager::GhostManager(const GhostManager& g):
  viewport(g.viewport),
  name(g.name),
  dumbGhosts(g.dumbGhosts)
{}

GhostManager::~GhostManager(){
  std::list<Ghost*>::iterator iter = dumbGhosts.begin();
  while(iter != dumbGhosts.end()){
    delete *iter;
    iter = dumbGhosts.erase(iter);
  }
}

void GhostManager::makeGhosts(){
  //Creating ghosts
  int noOfGhosts = Gamedata::getInstance().getXmlInt(name+"/noOfObjects");
  Ghost* ghostSprite = NULL;
  Vector2f velocity(Gamedata::getInstance().getXmlFloat(name+"/speed/x"), Gamedata::getInstance().getXmlFloat(name+"/speed/y"));
  for(int i =0; i < noOfGhosts; i++){
  
    Vector2f position(Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), Gamedata::getInstance().getXmlInt(name+      "/endLoc/x")), Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(name+"/startLoc/y"), Gamedata::getInstance().getXmlInt(name+"/endLoc/y")));
                     
    if(!ghostSprite){
        ghostSprite = new Ghost(name, position, velocity);
        dumbGhosts.push_back(ghostSprite);
    }
    else{
        dumbGhosts.push_back(new Ghost(ghostSprite->getName(), position, velocity, ghostSprite->getFrame()));   
    }
  }
}

void GhostManager::draw() const{
  std::list<Ghost*>::const_iterator ptr = dumbGhosts.begin();  
  while(ptr != dumbGhosts.end()) {
    (*ptr)->draw();
    ptr++;
  }
}

void GhostManager::update(unsigned int ticks){
  std::list<Ghost*>::const_iterator ptr = dumbGhosts.begin();
  while(ptr != dumbGhosts.end()) {
     (*ptr)->update(ticks);
     
     float x1 = viewport.X();
     float x2 = viewport.X() + viewport.getWidth();
     float y2 = viewport.Y() + viewport.getHeight();
     
     Vector2f objectVel = viewport.getObjectVelocity();
     
     if((*ptr)->X() < (x1 - 40) || (*ptr)->X() > (x2 + 40)){
        if(objectVel[0] < 0){
            (*ptr)->setPosition(getScaledPosition(Vector2f(x1-40, Gamedata::getInstance().getRandFloat(150, y2)), 40));
        }
        else{
            (*ptr)->setPosition(getScaledPosition(Vector2f(x2+40, Gamedata::getInstance().getRandFloat(150, y2)), 40));
        }
     }
     if(objectVel[0] < 0){
         (*ptr)->velocityX(abs((*ptr)->velocityX()));
     }
     else {
         (*ptr)->velocityX(-abs((*ptr)->velocityX()));
     }
     
     ptr++;
  }
}

Vector2f GhostManager::getScaledPosition(Vector2f position, float cushion)
{
  Vector2f startVel = position - cushion;
  Vector2f endVel = position + cushion;
  Vector2f temp (Gamedata::getInstance().getRandFloat(startVel[0],endVel[0]), Gamedata::getInstance().getRandFloat(startVel[1], endVel[1]));
  return temp;
}

bool GhostManager::checkForCollisions(Player* player) {
  std::list<Ghost*>::iterator iter = dumbGhosts.begin();
  bool bExplode = false;
  while ( iter != dumbGhosts.end() ) {
    if((*iter)->isObjExploded() || (*iter)->X() < viewport.X() || (*iter)->X() > viewport.X() + viewport.getWidth()) {
        ++iter;
    }
    else if (player->collidedWithBullets(*iter)){
        (*iter)->explode();
        bExplode = true;
        ++iter;
    }
    else if(player->collidedWith(*iter)){
        
        //if(!player->isObjExploded())
        //    player->explode();
        break;
    }
    else ++iter;
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