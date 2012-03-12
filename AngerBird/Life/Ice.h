/**
 *  @file Ice.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#ifndef _ICE_H
#define _ICE_H

#include "../pre.h"
#include "Life.h"
#include "Wood.h"

//namespace NBird{
class b2Body;
class GamePage;
class Ice : public Wood
{
public:
  virtual void Draw(TObjectData *);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); ///发生碰撞处理后
  Ice();

public:
  int bcir[2];
  int btip[2];
  int dytriangle[2];
  int loop[2];
  int ltip[2];
  int msqu[2];
  int mrect[2];
  int mtip[2];
  int rtriangle[2];
  int scir[2];
  int ssqu[2];
  int stip[2];
};

//}
#endif
