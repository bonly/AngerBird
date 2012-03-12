/**
 *  @file Pig.h
 *
 *  @date 2012-3-8
 *  @Author: Bonly
 */
#ifndef _PIG_H
#define _PIG_H

#include "../pre.h"
#include "Life.h"

//namespace NBird{
class GamePage;
class Pig : public Life
{
public:
  Pig();
  virtual JImage* GetStatusPiC(TObjectData *);
  virtual void Draw(TObjectData *);
  virtual bool ShouldCollide(TObjectData *other);
  virtual void BeginContact(b2Contact* contact);
  virtual void EndContact(b2Contact* contact);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
  
public:
  int bcrown[2]; 
  int bbeard[2];
  int bcap[3];
  int sgeneral[2];
  int mgeneral[2];
  int bgeneral[2];
  int dt; ///当前时间间隔计算
};

//}
#endif
