/**
 *  @file EggBird.cpp
 *
 *  @date 2012-3-12
 *  @Author: Bonly
 */
#include "EggBird.h"
#include "../Configure.h"
#include "../ResPool.h"
#include "../Page.h"
//namespace NBird{

JImage* EggBird::GetStatusPiC(TObjectData *stat)
{
  ++dt;
  JImage *pic = GETIMG(bird[0]);

  ///@todo ���Ѫ��
  //if (status->PH) 
  if (Life::status & s_clound)
  {
    pic = GETIMG(ID_birdcloud);
    return pic;
  }

  pic = Bird::GetStatusPiC(stat);

  (dt%1000==0)?dt=0:dt=dt; ///ѭ����ʱ��
  return pic;
}

EggBird::EggBird()
{
  bird[0] = ID_bird_egg_1;
  bird[1] = ID_bird_egg_2;

  width = BIRD_EGG_RADIUS * 2.f;
  height = BIRD_EGG_RADIUS * 2.f;

}

void EggBird::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) ///������ײ�����
{
  //printf("�������ײ����Ϊ: %lf\n",impulse->normalImpulses[0]);
  //*
  if(impulse->normalImpulses[0] >= 0.1f)///����Ƿ���ڵ���ë��ѹ��ֵ
  {
    int *aniFile = 0;
    Animation* clound = SafeNew Animation(dt,0,2);
    clound->pic_count = 3;
    clound->x = M2P(body->GetPosition().x);
    clound->y = M2P(body->GetPosition().y);
    aniFile = SafeNew int[3];
    aniFile[0] = ID_whitecloud;
    aniFile[1] = ID_whitecloud_big;
    aniFile[2] = ID_whitecloud_cir;
    clound->play_list = aniFile;
    gpage->push_ani(clound);

    Animation* feather = SafeNew Animation(dt,1,1);
    feather->pic_count = 2;
    feather->x = M2P(body->GetPosition().x);
    feather->y = M2P(body->GetPosition().y); ///drawʱ��ƫ��
    aniFile = SafeNew int[2];
    aniFile[0] = ID_feather_red_1;
    aniFile[1] = ID_feather_red_2;
    feather->play_list = aniFile;
    gpage->push_ani(feather);
  }
  //*/

}
//}
