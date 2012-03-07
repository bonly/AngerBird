/**
 *  @file Stone.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#ifndef _STONE_H
#define _STONE_H

#include "../pre.h"
#include "Life.h"
#include "Wood.h"

//namespace NBird{
class b2Body;
class GamePage;
class Stone : public Wood
{
public:
  virtual void Draw(TObjectData *);
  virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); ///发生碰撞处理后
  Stone();

public:
  int bcir[2];
  int btip[2];
  int dytriangle[2];
  int loop[2];
  int ltip[2];
  int msqu[2];
  int mtect[2];
  int mtip[2];
  int rtriangle[2];
  int scir[2];
  int ssqu[2];
  int stip[2];
};

//}
#endif
