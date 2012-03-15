/**
 *  @file EggBird.h
 *
 *  @date 2012-3-12
 *  @Author: Bonly
 */
#ifndef _EGGBIRD_H
#define _EGGBIRD_H

#include "../pre.h"
#include "Life.h"
#include "Bird.h"
//namespace NBird{
class GamePage;
class EggBird : public Bird
{
public:
  EggBird();
  virtual JImage* GetStatusPiC(TObjectData *);
  //virtual void Draw(TObjectData *);
  //virtual bool ShouldCollide(TObjectData *other);
  //virtual void BeginContact(b2Contact* contact);
  //virtual void EndContact(b2Contact* contact);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

//}

#endif
