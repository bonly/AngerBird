/**
 *  @file ContactListener.h
 *  @brief 各种物体的碰撞监听
 *  @date 2012-3-4
 *  @Author: Bonly
 */
#ifndef _CONTACTLISTENER_H
#define _CONTACTLISTENER_H
#include "../pre.h"

//namespace NBird{
class b2ContactListener;

/**
 * @brief 碰撞监测器
 */
class ContactListener : public b2ContactListener
{
  public:
    ContactListener();
    virtual ~ContactListener();

	  virtual void BeginContact(b2Contact* contact); ///开始碰撞
	  virtual void EndContact(b2Contact* contact);  ///碰撞结束
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold); ///发生碰撞处理前
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); ///发生碰撞处理后
};

/**
 * @brie 碰撞过滤器
 */
class ContactFilter : public b2ContactFilter
{
  virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB); ///检查是否参与碰撞
};

#endif


//}
