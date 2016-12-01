#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hudClass.h"
#include "health.h"
#include "ghostManager.h"
#include "sound.h"

class Player;
class ScaledSprite;

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

private:
  const bool env;
  const IOManager& io;
  GhostManager ghostMgr;
  Clock clock;

  SDL_Surface * const screen;
  World world;
  World layer2;
  World layer3;
  World layer4;
  World house;
  
  Viewport& viewport;

  std::vector<Drawable*> sprites;
  int currentSprite;

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;
  
  HudClass& hudBar;
  Health& healthBar;
  unsigned int hudTime;
  bool showHud;
  bool isWalk;
  unsigned int playerMoveCount;
  unsigned int moveTick;
  
  Player* player;
  SDLSound sound;
  
  std::vector<ScaledSprite*> pumpkin;

  void draw() const;
  void update();

  void makePumpkins();
  void drawLayers(unsigned int& iter) const;
  float getScaleFromRange(float start, float end, float pointNumber);
  Vector2f getScaledVelocity(Vector2f vel, float cushion);
  
  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
