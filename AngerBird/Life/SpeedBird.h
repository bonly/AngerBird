/**
 *  @file SpeedBird.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#ifndef _SPEEDBIRD_H
#define _SPEEDBIRD_H

#include "../pre.h"
#include "Life.h"
#include "Bird.h"
//namespace NBird{
class GamePage;
class SpeedBird : public Bird
{
public:
  SpeedBird();
  virtual JImage* GetStatusPiC(TObjectData *);
  //virtual void Draw(TObjectData *);
  //virtual bool ShouldCollide(TObjectData *other);
  //virtual void BeginContact(b2Contact* contact);
  //virtual void EndContact(b2Contact* contact);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

//}

#endif
