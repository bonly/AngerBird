/**
 *  @file ThreeBird.h
 *
 *  @date 2012-3-12
 *  @Author: Bonly
 */
#ifndef _THREEBIRD_H
#define _THREEBIRD_H

#include "../pre.h"
#include "Life.h"
#include "Bird.h"
//namespace NBird{
class GamePage;
class ThreeBird : public Bird
{
public:
  ThreeBird();
  virtual JImage* GetStatusPiC(TObjectData *);
  //virtual void Draw(TObjectData *);
  //virtual bool ShouldCollide(TObjectData *other);
  //virtual void BeginContact(b2Contact* contact);
  //virtual void EndContact(b2Contact* contact);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

//}

#endif
