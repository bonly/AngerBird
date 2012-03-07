/**
 *  @file abworld.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#ifndef ABWORLD_H
#define ABWORLD_H
#include "pre.h"

class ABWorld : public b2World
{
public:
  ABWorld(const b2Vec2& gravity);
  void DrawData();

};


//} /* namespace NBird */
#endif /* ABWORLD_H */
