/**
 *  @file Wood.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#ifndef _WOOD_H
#define _WOOD_H

#include "../pre.h"
#include "Life.h"

//namespace NBird{
class b2Body;
class GamePage;
class Wood : public Life
{
public:
  virtual void Draw(TObjectData *);
  virtual bool ShouldCollide(TObjectData *other);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); ///发生碰撞处理后
  Wood();

public:
  int ltip[2];
  int mrect[2];
  int msqu[2];
  int mtip[2];
  int ssqu[2];
  int stip[2];
};

//}
#endif
