/**
 *  @file RedBird.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "../pre.h"
#include "Life.h"
//namespace NBird{
class GamePage;
class Bird : public Life
{
public:
  Bird();
  virtual JImage* GetStatusPiC(TObjectData *);
  virtual void Draw(TObjectData *);
  virtual bool ShouldCollide(TObjectData *other);
  virtual void BeginContact(b2Contact* contact);
  virtual void EndContact(b2Contact* contact);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
  
public:
  int bird[2]; 
  int dt; ///当前时间间隔计算
  int flip_angle; ///筋斗的角度
};

//}
