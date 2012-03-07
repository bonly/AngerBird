/**
 *  @file Life.h
 *  @brief �����������ʾ
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#ifndef _LIEF_H
#define _LIEF_H
#include "../pre.h"
#include "../BuildBlock.h"
#include "../Page.h"
//namespace NBird{
class b2World;
class GamePage;
class Life
{
  public:
    Life();
    ~Life();
    void setSessionPage(GamePage*);
    virtual void Draw(TObjectData *)=0;
    virtual bool ShouldCollide(TObjectData *other); ///�����Ƿ������ײ
    virtual void BeginContact(b2Contact* contact); ///��ײ��ʼ
    virtual void EndContact(b2Contact* contact);  ///��ײ����
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); ///������ײ�����
    virtual bool PickAble(int x, int y)  ///�ɽ�������������е���������Ƿ񱻿���
    {
      return false;
    }

  public:
	  enum
	  {
		  s_pickAble				= 0x0001,	///< ��ץȡ
		  s_waiting 				= 0x0002,	///< �ϲ�ǰ�ȴ���
		  s_flying  				= 0x0004,	///< ������
      s_eyes            = 0x0008, ///< ��գ��
      s_crash           = 0x0010, ///< ��ײ��
      s_clound          = 0x0020  ///< ������ʧ
	  };
    int status;

    int x;  //���ĵ�����Ļ�е�λ��
    int y; 
    int width;
    int height;
    b2Body *body;
    GamePage *gpage;
    float PH;  ///��ǰѪ��
};


#endif


//}
