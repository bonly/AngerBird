/**
 *  @file RedBird.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "../pre.h"
#include "Life.h"
#include "Bird.h"
//namespace NBird{
class GamePage;
class RedBird : public Bird
{
public:
  RedBird();
  virtual JImage* GetStatusPiC(TObjectData *);
  //virtual void Draw(TObjectData *);
  //virtual bool ShouldCollide(TObjectData *other);
  //virtual void BeginContact(b2Contact* contact);
  //virtual void EndContact(b2Contact* contact);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

//}
