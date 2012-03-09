/**
 *  @file Session1.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "Life.h"
#include "../Configure.h"
#include "../ABDraw.h"
#include "../BuildBlock.h"
//namespace NBird{

Life::Life()
{
  //status = ~s_pickAble & s_jumpAble & ~s_clound ;
  status = 0x0;
}

Life::~Life()
{
}

void Life::BeginContact(b2Contact* contact)
{

}

void Life::EndContact(b2Contact* contact)
{

}

bool Life::ShouldCollide(TObjectData *other)
{
  return true;
}

void Life::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

void Life::setSessionPage(GamePage* page)
{
  gpage = page;
}
//}
