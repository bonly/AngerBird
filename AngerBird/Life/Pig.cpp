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

JImage* Pig::GetStatusPiC(TObjectData *stat)
{
  JImage *pic = 0;
  int* pig = 0;
  switch(stat->shapeType)
  {
    case SHAPE_CROWN_PIG:
      pig = bcrown;
      break;
    case SHAPE_BEARD_PIG:
      pig = bbeard;
      break;
    case SHAPE_CAP_PIG:
      pig = bcap;
      break;
    case SHAPE_L_PIG:
      pig = bgeneral;
      break;
    case SHAPE_M_PIG:
      pig = mgeneral;
      break;
    case SHAPE_S_PIG:
      pig = sgeneral;
      break;
  }

  if (Life::status & s_eyes) ///眨眼
  {
    pic = GETIMG(pig[dt%2]);
  }
  
  ///@todo 血量检查
  
  return pic;
}
void Pig::Draw(TObjectData *status)
{
  JImage *pic = GetStatusPiC(status);
  if (pic==0) return;

  int angle = sin2oc(body->GetAngle());

  ///渲染
  x = M2P(body->GetPosition().x);
  y = M2P(body->GetPosition().y);
  gpDC->drawImageWithRotate(pic, x, y + SHIFT, ACHOR_HV, angle);
}

Pig::Pig()
{
  bcrown[0] = ID_pig_bcrown_1;
  bcrown[1] = ID_pig_bcrown_2;

  bbeard[0] = ID_pig_bbeard_1;
  bbeard[1] = ID_pig_bbeard_2;

  bcap[0] = ID_pig_bcap_1;
  bcap[1] = ID_pig_bcap_2;
  bcap[2] = ID_pig_bcap_3;

  sgeneral[0] = ID_pig_sgeneral_1;
  sgeneral[1] = ID_pig_sgeneral_2;

  mgeneral[0] = ID_pig_mgeneral_1;
  mgeneral[1] = ID_pig_mgeneral_2;

  bgeneral[0] = ID_pig_bgeneral_1;
  bgeneral[1] = ID_pig_bgeneral_2;

  status |= Life::s_eyes;
}

bool Pig::ShouldCollide(TObjectData *other)
{
  bool ret = true;

  return ret;
}

void Pig::BeginContact(b2Contact* contact)
{

}

void Pig::EndContact(b2Contact* contact)
{
  
}

void Pig::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) ///发生碰撞处理后
{
  //printf("猪的碰撞冲量为: %lf\n",impulse->normalImpulses[0]);
  if(impulse->normalImpulses[0] >= 0.2)///检查是否大于掉羽毛的压力值
  {

    
  }

}

//}
