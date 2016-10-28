#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include "multisprite.h"
#include "twoWayMultisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "player.h"
#include "scaledSprite.h"

class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  
  for (unsigned i = 0; i < pumpkin.size(); ++i) {
    if(pumpkin[i])
     delete pumpkin[i];
  }
  pumpkin.clear();
  
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world("layer1", Gamedata::getInstance().getXmlInt("layer1/factor") ),
  layer2("layer2", Gamedata::getInstance().getXmlInt("layer2/factor") ),
  layer3("layer3", Gamedata::getInstance().getXmlInt("layer3/factor") ),
  layer4("layer4", Gamedata::getInstance().getXmlInt("layer4/factor") ),
  house("house", Gamedata::getInstance().getXmlInt("house/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  hudBar( HudClass::getInstance() ),
  healthBar(),
  playerHealth(100),
  showHud(false),
  player(new Player("boy")),
  pumpkin()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  
  makePumpkins();
  
  /*layers.push_back(World("layer2", Gamedata::getInstance().getXmlInt("layer2/factor")));
  layers.push_back(World("layer3", Gamedata::getInstance().getXmlInt("layer3/factor")));
  layers.push_back(World("layer4", Gamedata::getInstance().getXmlInt("layer4/factor")));
  layers.push_back(World("layer5", Gamedata::getInstance().getXmlInt("layer5/factor")));
  layers.push_back(World("layer6", Gamedata::getInstance().getXmlInt("layer6/factor")));*/
  
  sprites.push_back(player);  
  viewport.setObjectToTrack(sprites[currentSprite]);
}

float Manager::getScaleFromRange(float start, float end, float pointNumber)
{
  float scale = 0;
  if(pointNumber == 0)
      scale = start;
  else if(pointNumber == 2)
      scale = end;
  else
      scale = (end+start)/2;
  
  return scale;
}

Vector2f Manager::getScaledVelocity(Vector2f vel, float cushion)
{
  Vector2f startVel = vel - cushion;
  Vector2f endVel = vel + cushion;
  Vector2f temp (Gamedata::getInstance().getRandFloat(startVel[0],endVel[0]), Gamedata::getInstance().getRandFloat(startVel[1], endVel[1]));
  return temp;
}

void Manager::makePumpkins() {
  const std::string name = "pumpkin";  
  unsigned instances = Gamedata::getInstance().getXmlInt(name+"/noOfObjects/instances");
  unsigned actual = Gamedata::getInstance().getXmlInt(name+"/noOfObjects/actual");
  float cushion = Gamedata::getInstance().getXmlInt(name+"/cushion");
  
  unsigned noOfPumpkins = (actual*(actual+1))/2 * instances;  
  pumpkin.reserve( noOfPumpkins );
  
  for (unsigned i = 0; i < actual; ++i) {
    float scale = getScaleFromRange(Gamedata::getInstance().getXmlFloat(name+"/scale/min"), Gamedata::getInstance().getXmlFloat(name+"/scale/max"), i);
    float xVel = getScaleFromRange(Gamedata::getInstance().getXmlFloat(name+"/minspeed/x"), Gamedata::getInstance().getXmlFloat(name+"/maxspeed/x"), i);
    float yVel = getScaleFromRange(Gamedata::getInstance().getXmlFloat(name+"/minspeed/y"), Gamedata::getInstance().getXmlFloat(name+"/maxspeed/y"), i);
  
    Vector2f velocity(xVel, yVel);
    ScaledSprite* scaledSprite = NULL;
    for(unsigned j = 0; j < (actual-i)*instances; j++){
        Vector2f position(Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), Gamedata::getInstance().getXmlInt(name+"/endLoc/x")), 
                          Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(name+"/startLoc/y"), Gamedata::getInstance().getXmlInt(name+"/endLoc/y")));  

        if(!scaledSprite){
            scaledSprite = new ScaledSprite(name, position, getScaledVelocity(velocity, cushion), scale, i);
            pumpkin.push_back(scaledSprite);
        }
        else{
            pumpkin.push_back(new ScaledSprite(scaledSprite->getName(), position, getScaledVelocity(velocity, cushion), scaledSprite->getFrame(), scale));    
        }
     }
  }
  sort(pumpkin.begin(), pumpkin.end(), ScaledSpriteCompare());
}

void Manager::drawLayers(unsigned int& iter, const World* worlds) const{
  if(iter < pumpkin.size()){
    float scale = pumpkin[iter]->getScale();
    while(iter < pumpkin.size()) {
      if(pumpkin[iter]->getScale() == scale){
        pumpkin[iter]->draw(); 
        ++iter;
      }
      else{
        scale = pumpkin[iter]->getScale();
        if(worlds != NULL)
            worlds->draw();
        break;
      }
    }    
  }
}

void Manager::draw() const {
    
  world.draw();
  
  unsigned int iter = 0;
  drawLayers(iter, &layer2);
  house.draw();
  drawLayers(iter, &layer3);
  layer4.draw();
  drawLayers(iter);
  
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  
  // TODO: Replace 3 with xml value
  if(clock.getSeconds() < 3 || showHud){
    hudBar.drawHud(screen, io, clock.getSeconds(), clock.getAvgFrameRate(), playerHealth);
    healthBar.draw();
  }  
  
  //io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20);
  //io.printMessageValueAt("fps: ", clock.getAvgFrameRate(), 10, 40);
  //io.printMessageAt("Press T to switch sprites", 10, 65);
  io.printMessageAt(title, 10, 450);
  viewport.draw();
 
  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::update() {
  ++(clock);
  Uint32 ticks = clock.getElapsedTicks();

  static unsigned int lastSeconds = clock.getSeconds();
  if ( clock.getSeconds() - lastSeconds == 5 ) {
    lastSeconds = clock.getSeconds();
    //switchSprite();
  }
  
  for (unsigned i = 0; i < pumpkin.size(); ++i) {
    pumpkin[i]->update(ticks);
  }

  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  
  healthBar.update(ticks);
  world.update();
  layer2.update();
  layer3.update();
  layer4.update();
  house.update();
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  bool keyCatch = false;
  
  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYUP) { keyCatch = false; player->stop();}
      
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_t] && !keyCatch ) {
          keyCatch = true;
          switchSprite();
        }

        if ( keystate[SDLK_p] && !keyCatch) {
          keyCatch = true;
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDLK_d] ) {
          
        }
        
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
       
        if (keystate[SDLK_F1] && !keyCatch) {
          keyCatch = true;
          if(!showHud){
            showHud=true;
	      }
          else{
            showHud=false;
          }
        }
        
        if (keystate[SDLK_a] ) {
          player->moveLeft();
        }
        
        if (keystate[SDLK_d] ) {
          player->moveRight();
        }
        
        if (keystate[SDLK_s] ) {
          player->moveDown();
        }
        
        if (keystate[SDLK_z] ) {
	      player->increaseVelocity(1.5);
        }
       
        if (keystate[SDLK_x] ) {
              player->decreaseVelocity(1.5);
        }
        
        if (keystate[SDLK_w] ) {
	      player->moveUp();
        }
      }
    }
    
    draw();
    update();
  }
}
