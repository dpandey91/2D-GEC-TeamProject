#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include "drawable.h"

class Sprite : public Drawable {
public:
  Sprite(const std::string&);
  Sprite(const bool aComeback, const std::string&, const Vector2f& pos, const Vector2f& vel);
  Sprite(const bool aComeback, const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  Sprite(const std::string& name, const Vector2f& vel, const Frame* frm);
  Sprite(const Sprite& s);
  Sprite& operator=(const Sprite& rhs);
  
  virtual ~Sprite() { } 

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;

  virtual void update(Uint32 ticks);
  
  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }

private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const Sprite*) const;
};
#endif
