/**
 *  @file ContactListener.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "ContactListener.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "../BuildBlock.h"
#include "Life.h"
//namespace NBird{

ContactListener::ContactListener()
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
  TObjectData* objA = (TObjectData*)contact->GetFixtureA()->GetUserData();
  TObjectData* objB = (TObjectData*)contact->GetFixtureB()->GetUserData();

  if(objA && objA->life)
  {
     objA->life->BeginContact(contact);
  }
  if(objB && objB->life)
  {
     objB->life->BeginContact(contact);
  }
  
  return;
}

void ContactListener::EndContact(b2Contact* contact)
{
  TObjectData* objA = (TObjectData*)contact->GetFixtureA()->GetUserData();
  TObjectData* objB = (TObjectData*)contact->GetFixtureB()->GetUserData();

  if(objA && objB && objA->life && objB->life)
  {
     objA->life->EndContact(contact);
     objB->life->EndContact(contact);
  }
  
  return;
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
  TObjectData* objA = (TObjectData*)contact->GetFixtureA()->GetBody()->GetUserData();
  TObjectData* objB = (TObjectData*)contact->GetFixtureB()->GetBody()->GetUserData();

  if(objA && objB && objA->life && objB->life)
  {
    objA->life->PostSolve(contact, impulse);
    objB->life->PostSolve(contact, impulse);
  }
}

bool ContactFilter::ShouldCollide(b2Fixture *fixtureA, b2Fixture *fixtureB)
{
  TObjectData* objA = (TObjectData*)fixtureA->GetBody()->GetUserData();
  TObjectData* objB = (TObjectData*)fixtureB->GetBody()->GetUserData();

  if(objA && objB && objA->life && objB->life)///只要有一个接受碰撞.都算可以碰撞
  {
    return (objA->life->ShouldCollide(objB))||(objB->life->ShouldCollide(objA));
  }  
  
  return true;
}

//}
