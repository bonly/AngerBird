/**
 *  @file ContactListener.h
 *  @brief �����������ײ����
 *  @date 2012-3-4
 *  @Author: Bonly
 */
#ifndef _CONTACTLISTENER_H
#define _CONTACTLISTENER_H
#include "../pre.h"

//namespace NBird{
class b2ContactListener;

/**
 * @brief ��ײ�����
 */
class ContactListener : public b2ContactListener
{
  public:
    ContactListener();
    virtual ~ContactListener();

	  virtual void BeginContact(b2Contact* contact); ///��ʼ��ײ
	  virtual void EndContact(b2Contact* contact);  ///��ײ����
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold); ///������ײ����ǰ
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); ///������ײ�����
};

/**
 * @brie ��ײ������
 */
class ContactFilter : public b2ContactFilter
{
  virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB); ///����Ƿ������ײ
};

#endif


//}
