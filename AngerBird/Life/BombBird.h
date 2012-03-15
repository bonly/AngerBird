/**
 *  @file BombBird.h
 *
 *  @date 2012-3-12
 *  @Author: Bonly
 */
#ifndef _BOMBBIRD_H
#define _BOMBBIRD_H

#include "../pre.h"
#include "Life.h"
#include "Bird.h"
//namespace NBird{
class GamePage;
class BombBird : public Bird
{
public:
  BombBird();
  virtual JImage* GetStatusPiC(TObjectData *);
  //virtual void Draw(TObjectData *);
  //virtual bool ShouldCollide(TObjectData *other);
  //virtual void BeginContact(b2Contact* contact);
  //virtual void EndContact(b2Contact* contact);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

  int redBomb;
};

//}

#endif
