#include "bulletsPool.h"

BulletsPool::BulletsPool(const std::string & str) :
  name(str),
  bulletList(),
  freeList()
{}

BulletsPool::BulletsPool(const BulletsPool& b) :
  name(b.name),
  bulletList(b.bulletList),
  freeList(b.freeList)
{}

void BulletsPool::shoot(const Vector2f& pos, const Vector2f& vel){
  if(freeList.empty()) {
    MultiBullet b(name, pos, vel);
    bulletList.push_back(b);
  }
  else{
    MultiBullet b = freeList.front();
    freeList.pop_front();
    b.reset();
    b.setVelocity(vel);
    b.setPosition(pos);
    bulletList.push_back(b);
  }
}

void BulletsPool::draw() const {
  std::list<MultiBullet>::const_iterator bitr = bulletList.begin();
  while(bitr != bulletList.end()){
     (*bitr).draw();
     ++bitr;
  }
}
void BulletsPool::reset(){
  std::list<MultiBullet>::iterator bitr = bulletList.begin();
  while(bitr != bulletList.end()){
     freeList.push_back(*bitr);
     bitr = bulletList.erase(bitr);
 }
}

bool BulletsPool::collidedWith(const Drawable* obj){
   std::list<MultiBullet>::iterator iter = bulletList.begin();
   while(iter != bulletList.end()){   
     if((*iter).collidedWith(obj)){
         freeList.push_back(*iter);
         iter = bulletList.erase(iter);
         return true;
     }
     ++iter;
   }          
   return false;
}
 
void BulletsPool::update(Uint32 ticks, const Vector2f& pPos)  {
    
  std::list<MultiBullet>::iterator bitr = bulletList.begin();
  while(bitr != bulletList.end()){
    (*bitr).update(ticks, pPos);
    if((*bitr).isTooFar()){
      freeList.push_back(*bitr);
      bitr = bulletList.erase(bitr);
    }
    else ++bitr;
  }
}