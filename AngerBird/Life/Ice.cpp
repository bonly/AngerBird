/**
 *  @file Ice.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#include "Ice.h"
#include "../Configure.h"
#include "../ResPool.h"
#include "../Page.h"

//namespace NBird{
void Ice::Draw(TObjectData *status)
{
  int *pic_idx=0;
  switch (status->shapeType)
  { 
    case SHAPE_B_TIP:
      pic_idx = btip;
      break;
    case SHAPE_L_TIP: //����
      pic_idx = ltip;
      break;
    case SHAPE_M_TIP:	//����
      pic_idx = mtip;
      break;
    case SHAPE_S_TIP:	//����
      pic_idx = stip;
      break;
    case SHAPE_M_SQU:	//��������
      pic_idx = msqu;
      break;
    case SHAPE_S_SQU:	//С������
      pic_idx = ssqu;
      break;
    case SHAPE_S_RECT: //�̾���  
      pic_idx = mrect;
      break;
  }
  /// ���Ѫ��
  TObjectData* stat = (TObjectData*)body->GetUserData();
  if (PH <= 0) 
  {
     gpage->push_del(this->body); ///ɾ������
  }
  if (PH <= stat->PH/2.f)
  {
    ++pic_idx; ///��Ѫ��ͼƬ
  }

  if(pic_idx == 0) return;
  
  ///��ʼshow
  float32 angle = sin2oc(body->GetAngle());

  JImage *pic = GETIMG(*pic_idx);
  gpDC->drawImageWithRotate(pic, 
                  M2P(body->GetPosition().x), 
                  M2P(body->GetPosition().y) + SHIFT, 
                  ACHOR_HV, angle);
}

Ice::Ice()
{
  bcir[0] = ID_ice_bcir_1;
  bcir[1] = ID_ice_bcir_2;

  btip[0] = ID_ice_btip_1;
  btip[1] = ID_ice_btip_2;

  dytriangle[0] = ID_ice_dytriangle_1;
  dytriangle[2] = ID_ice_dytriangle_2;

  loop[0] = ID_ice_loop_1;
  loop[1] = ID_ice_loop_2;

  ltip[0] = ID_ice_ltip_1;
  ltip[1] = ID_ice_ltip_2;

  msqu[0] = ID_ice_msqu_1;
  msqu[1] = ID_ice_msqu_2;

  mrect[0] = ID_ice_mrect_1;
  mrect[1] = ID_ice_mrect_2;

  mtip[0] = ID_ice_mtip_1;
  mtip[1] = ID_ice_mtip_2;

  rtriangle[0] = ID_ice_rtriangle_1;
  rtriangle[1] = ID_ice_rtriangle_2;

  scir[0] = ID_ice_scir_1;
  scir[1] = ID_ice_scir_2;

  ssqu[0] = ID_ice_ssqu_1;
  ssqu[1] = ID_ice_ssqu_2;

  stip[0] = ID_ice_stip_1;
  stip[1] = ID_ice_stip_2;
}

void Ice::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) ///������ײ�����
{
  //printf("��ײ����Ϊ: %lf\n",impulse->normalImpulses[0]);
  if(impulse->normalImpulses[0] >= 3)///����Ƿ����HP
  {
    gpage->push_del(this->body);
  }

}
 
//}
