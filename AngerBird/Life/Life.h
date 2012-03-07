/**
 *  @file Life.h
 *  @brief 各种生物的显示
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
    virtual bool ShouldCollide(TObjectData *other); ///决定是否参与碰撞
    virtual void BeginContact(b2Contact* contact); ///碰撞开始
    virtual void EndContact(b2Contact* contact);  ///碰撞结束
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); ///发生碰撞处理后
    virtual bool PickAble(int x, int y)  ///可交由子类坐标点中的物体决定是否被控制
    {
      return false;
    }

  public:
	  enum
	  {
		  s_pickAble				= 0x0001,	///< 可抓取
		  s_waiting 				= 0x0002,	///< 上叉前等待中
		  s_flying  				= 0x0004,	///< 飞行中
      s_eyes            = 0x0008, ///< 能眨眼
      s_crash           = 0x0010, ///< 碰撞了
      s_clound          = 0x0020  ///< 变云消失
	  };
    int status;

    int x;  //中心点在屏幕中的位置
    int y; 
    int width;
    int height;
    b2Body *body;
    GamePage *gpage;
    float PH;  ///当前血量
};


#endif


//}
