/**
 *  @file RedBird.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#include "Bird.h"
#include "../Configure.h"
#include "../ResPool.h"
#include "../Page.h"
//namespace NBird{

JImage* Bird::GetStatusPiC(TObjectData *)
{
  JImage *pic = GETIMG(bird[0]);

  if (Life::status & s_eyes) ///眨眼
  {
    pic = GETIMG(bird[dt%2]);
  }

  if (dt%40==0 && Life::status & s_waiting) ///原地跳动
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
    if (dt%2 == 0 && Life::status & s_flying) ///飞行轨迹
    {
      gpage->track[gpage->track_num][0] = (int)M2P(body->GetPosition().x);
      gpage->track[gpage->track_num][1] = (int)M2P(body->GetPosition().y);
      ++gpage->track_num;
    }
  }
  
  return pic;
}
void Bird::Draw(TObjectData *status)
{
  JImage *pic = GetStatusPiC(status);
  if (pic==0) return;

  if (Life::status & s_flip)
  {
    flip_angle += 45;
    if (flip_angle >= 360)
    {
      Life::status &= ~s_flip;
      flip_angle = 0;
    }
    //body->ApplyTorque(flip_angle);
    body->SetTransform(b2Vec2(body->GetPosition().x, body->GetPosition().y), flip_angle);
  }
  int angle = sin2oc(body->GetAngle());

  ///渲染
  x = M2P(body->GetPosition().x);
  y = M2P(body->GetPosition().y);
  gpDC->drawImageWithRotate(pic, 
    x - pic->getWidth()/2, 
    y - pic->getHeight()/2 + SHIFT, 20, angle);
}

Bird::Bird():flip_angle(0)
{
}

bool Bird::ShouldCollide(TObjectData *other)
{
  bool ret = true;
  switch (other->fixture)
  {
  case FIXTURE_BIRD:
    ret = false;
  }
  return ret;
}

void Bird::BeginContact(b2Contact* contact)
{
  status |= s_crash;
  if ((Life::status & s_flip) && (contact->GetFixtureA()->GetBody()->GetType()==b2_staticBody)) ///与地面相撞
  {
      Life::status &= ~s_flip;
      flip_angle = 0;
      //body->ApplyTorque(flip_angle);
      body->SetTransform(b2Vec2(body->GetPosition().x, body->GetPosition().y), flip_angle);
  }
}

void Bird::EndContact(b2Contact* contact)
{
  
}

void Bird::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) ///发生碰撞处理后
{
  printf("鸟的碰撞冲量为: %lf\n",impulse->normalImpulses[0]);
  if(impulse->normalImpulses[0] >= 0.2)///检查是否大于掉羽毛的压力值
  {

    
  }

}
//}
