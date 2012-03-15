/**
 *  @file SpeedBird.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#include "SpeedBird.h"
#include "../Configure.h"
#include "../ResPool.h"
#include "../Page.h"
//namespace NBird{

JImage* SpeedBird::GetStatusPiC(TObjectData *stat)
{
  ++dt;
  JImage *pic = GETIMG(bird[0]);

  ///@todo 检查血量
  //if (status->PH) 
  if (Life::status & s_clound)
  {
    pic = GETIMG(ID_birdcloud);
    return pic;
  }

  pic = Bird::GetStatusPiC(stat);

  (dt%1000==0)?dt=0:dt=dt; ///循环计时器
  return pic;
}

SpeedBird::SpeedBird()
{
  bird[0] = ID_bird_addspeed_1;
  bird[1] = ID_bird_addspeed_2;

  //width = S_REDBIRD_WIDTH;
  //height = S_REDBIRD_HEIGHT;
  width = BIRD_RED_RADIUS * 2.f;
  height = BIRD_RED_RADIUS * 2.f;

}

void SpeedBird::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) ///发生碰撞处理后
{
  //printf("红鸟的碰撞冲量为: %lf\n",impulse->normalImpulses[0]);
  //*
  if(impulse->normalImpulses[0] >= 0.1f)///检查是否大于掉羽毛的压力值
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
    feather->y = M2P(body->GetPosition().y); ///draw时再偏移
    aniFile = SafeNew int[2];
    aniFile[0] = ID_feather_red_1;
    aniFile[1] = ID_feather_red_2;
    feather->play_list = aniFile;
    gpage->push_ani(feather);
  }
  //*/

}
//}
