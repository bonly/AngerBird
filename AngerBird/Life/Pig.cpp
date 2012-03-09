/**
 *  @file Pig.cpp
 *
 *  @date 2012-3-8
 *  @Author: Bonly
 */
#include "Pig.h"
#include "../Configure.h"
#include "../ResPool.h"
#include "../Page.h"
//namespace NBird{

JImage* Pig::GetStatusPiC(TObjectData *)
{
  JImage *pic = GETIMG(pig[0]);

  if (Life::status & s_eyes) ///գ��
  {
    pic = GETIMG(pig[dt%2]);
  }

  if (dt%40==0 && Life::status & s_jumpAble) ///ԭ������
  {
    Life::status |= s_flip;
    body->GetFixtureList()->SetRestitution(0.f);
    body->SetActive(true);

    //body->ApplyForce(b2Vec2(100,0), body->GetWorldCenter());
    body->ApplyForceToCenter(b2Vec2(100.f * body->GetMass(), 0.f));
    //body->SetLinearVelocity(b2Vec2(4.f,0.f));
  }

  if (!(Life::status & s_crash))
  {
    if (dt%2 == 0 && Life::status & s_flying) ///���й켣
    {
      gpage->track[gpage->track_num][0] = (int)M2P(body->GetPosition().x);
      gpage->track[gpage->track_num][1] = (int)M2P(body->GetPosition().y);
      ++gpage->track_num;
    }
  }
  
  return pic;
}
void Pig::Draw(TObjectData *status)
{
  JImage *pic = GetStatusPiC(status);
  if (pic==0) return;

  int angle = sin2oc(body->GetAngle());

  ///��Ⱦ
  x = M2P(body->GetPosition().x);
  y = M2P(body->GetPosition().y);
  gpDC->drawImageWithRotate(pic, 
    x - pic->getWidth()/2, 
    y - pic->getHeight()/2 + SHIFT, 20, angle);
}

Pig::Pig()
{
}

bool Pig::ShouldCollide(TObjectData *other)
{
  bool ret = true;
  switch (other->fixture)
  {
  case FIXTURE_BIRD:
    ret = false;
  }
  return ret;
}

void Pig::BeginContact(b2Contact* contact)
{
  if (status & s_flying )
     status |= s_crash;
  /*
  if ((Life::status & s_flip) && (contact->GetFixtureA()->GetBody()->GetType()==b2_staticBody)) ///�������ײ
  {
      Life::status &= ~s_flip;
      flip_angle = 0;
      //body->ApplyTorque(flip_angle);
      body->SetTransform(b2Vec2(body->GetPosition().x, body->GetPosition().y), flip_angle);
  }
  */
}

void Pig::EndContact(b2Contact* contact)
{
  
}

void Pig::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) ///������ײ�����
{
  //printf("�����ײ����Ϊ: %lf\n",impulse->normalImpulses[0]);
  if(impulse->normalImpulses[0] >= 0.2)///����Ƿ���ڵ���ë��ѹ��ֵ
  {

    
  }

}
//}
