/**
 *  @file Wood.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#include "pre.h"
#include "Stone.h"
#include "../Configure.h"
#include "../ResPool.h"
#include "../Page.h"

//namespace NBird{
void Stone::Draw(TObjectData *status)
{
  int *pic_idx=0;
  switch (status->shapeType)
  {
  case SHAPE_L_TIP: //长条
    pic_idx = ltip;
    break;
  case SHAPE_M_TIP:	//中条
    pic_idx = mtip;
    break;
  case SHAPE_S_TIP:	//短条
    pic_idx = stip;
    break;
  case SHAPE_M_SQU:	//中正方形
    pic_idx = msqu;
    break;
  case SHAPE_S_SQU:	//小正方形
    pic_idx = ssqu;
    break;
  case SHAPE_S_RECT: //短矩形  
    pic_idx = mrect;
    break;
  }
  /// 检查血量
  TObjectData* stat = (TObjectData*)body->GetUserData();
  if (PH <= 0) 
  {
     gpage->push_del(this->body); ///删除物体
  }
  if (PH <= stat->PH/2.f)
  {
    ++pic_idx; ///半血的图片
  }

  if(pic_idx == 0) return;
  
  ///开始show
  float32 angle = sin2oc(body->GetAngle());

  JImage *pic = GETIMG(*pic_idx);
  gpDC->drawImageWithRotate(pic, 
    M2P(body->GetPosition().x) - pic->getWidth()/2, 
    M2P(body->GetPosition().y) - pic->getHeight()/2 + SHIFT, ACHOR_HV, angle);
}

Stone::Stone()
{
  ltip[0] = ID_ltip1;
  ltip[1] = ID_ltip2;

  msqu[0] = ID_msqu1;
  msqu[1] = ID_msqu2;

  mtip[0] = ID_mtip1;
  mtip[1] = ID_mtip2;

  ssqu[0] = ID_ssqu1;
  ssqu[1] = ID_ssqu2;

  stip[0] = ID_stip1;
  stip[1] = ID_stip2;

  mrect[0] = ID_mrect1;
  mrect[1] = ID_mrect1;

}

void Stone::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) ///发生碰撞处理后
{
  //printf("碰撞冲量为: %lf\n",impulse->normalImpulses[0]);
  if(impulse->normalImpulses[0] >= 3)///检查是否大于HP
  {
    gpage->push_del(this->body);
  }

}
 
//}
