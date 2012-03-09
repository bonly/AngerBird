/**
 *  @file Session1.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
//#include <jdefine.h>
#include "Session1.h"
#include "PreLoad.h"
#include "../BuildBlock.h"
#include "../objectDef.h"
#include "../Configure.h"
//#include "../lua/lua.hpp"
//#include "../rapidxml.hpp"
#include "../BuildBlock.h"
#include "../Page.h"
extern bool gPaintStatus;
//#define SCREEN_SHIFT_Y 0
//活动物体列表
//定义一个活动物体数量

/**
 * 0: 1增加 0删除
 * 1: 所删除物件的记号num
 * 2: 模拟等待步数
 * 3: objectfixture
 * 4: objectShapeType
 * 5: x
 * 6: y
 * 7: 角度
 */
static int nBlockNum=17;
static int nBlockList[][8]={ 
{1,1,11,1,2,32,66,0},
{1,2,7,1,2,32,169,0},
{1,3,7,1,0,53,89,0},
{1,4,9,1,0,53,145,0},
{1,5,6,1,1,32,118,90},
{1,6,5,4,1,45,107,0},
{1,7,4,4,1,45,126,0},
{1,8,5,1,1,70,118,90},
{1,9,5,1,0,90,118,90},
{1,10,7,1,0,129,99,0},
{1,11,6,1,2,102,117,90},
{1,12,5,2,16,114,117,0},
{1,13,7,1,0,121,132,0},
{1,14,25,1,1,159,117,90},
{0,14,24,1,1,159,117,90},
{1,15,6,1,0,159,117,90},
{1,16,5,1,2,178,109, 0}
};



//////////////////////////////////
static int nFloorNum=2;
static int nFloorList[][21]={
{ 0, ID_floor_1_1_1, 10, 89, 4, 9, -29, 9, 25, -11, 25, -11, -30, 0, 0, 0, 0, 0, 0, 0 },
{ 0, ID_floor_1_1_1, 10, 149, 4, 9, -29, 9, 25, -11, 25, -11, -30, 0, 0, 0, 0, 0, 0, 0 }
};


//////////////////////////////////
static int nBirdNum=4;
static int nBirdList[][8]={ 
{1,0,7,3,21,12,170,0},
{1,1,16,3,21,12,195,0},
{1,2,8,3,21,12,220,0},
{1,3,13,3,21,12,245, 0}
};

static int nBirdFloorNum=0;
static int nBirdFloorList[][21]={
	{0}
};

static int objectNum=0;
static TObjectData objectDataList[MAX_OBJECTS];    //物体userdata的全局变量
static TObjectData* s_controllable[10]; ///可控制物列表

extern int firstEnterFlag;
//namespace NBird{
Session1::Session1(void)
{
  step = PRELOAD;
  objectNum = 0;///密须重置一次,防止重载此页时值累加
}

Session1::~Session1(void)
{
  onDestory();
}

void Session1::onDestory()
{
  //SafeDelete(preload);
  for (int i = 0; i < objectNum; ++i)
  {
     SafeDelete(objectDataList[i].life);
  }
}
int Session1::init()
{
  GamePage::init();
  GamePage::controllable = s_controllable;
  //preload = SafeNew PreLoad;
  //preload->init();

  return 0;
}

Page* Session1::create()
{
   return SafeNew(Session1);
}

/** 预读取
 */
void Session1::preLoad()
{
  #define IMGSEG
  #define RES(X) load_##X(0); 
  #include "session1.inc"
  #undef RES
  #undef IMGSEG

  imgBg=GETIMG(ID_1_bg);
  imgGrass=GETIMG(ID_1_bg_grass);
  createWorld();
}

void Session1::running()
{
  switch(step)
  {
  case PRELOAD: ///指示预载页面,并同时加载本关所需的资源
    firstEnterFlag = 2;
    GamePage::running();
    step = PRELOADING;
    break;
  case PRELOADING:
    preLoad();
    GamePage::running();
    step = PRELOAD_END;
    break;  
  case PRELOAD_END:
    GamePage::running();
    step = GAME_LOADING;
    break;
  case GAME_LOADING:
  case GAME_GETBIRD:
  case GAME_WAIT:
  case GAME_SCROLL:
  case GAME_RUNING:
    GamePage::running();
    world->Step(1.0f/20.0f,20,10);
    break;
  case GAME_PAUSE:
  case GAME_OVER:
  case GAME_END:
    GamePage::running();
    world->Step(1.0f/20.0f,20,10);
    break;
  }
}

void Session1::onPaint()
{
  switch(step)
  {
  case PRELOAD:  ///在预加载时显示预加载页面
    firstEnterFlag = 2; ///加蒙层
    break;
  case PRELOADING:
    break;
  case PRELOAD_END: ///预加载期结束
    gPaintStatus=false;//session中修改
    firstEnterFlag = 0; ///去掉蒙层
    break;
  case GAME_LOADING:
  case GAME_GETBIRD:
  case GAME_SCROLL:
  case GAME_PAUSE:
  case GAME_OVER:
  case GAME_END:
  case GAME_WAIT:     ///在游戏中加载游戏页面
  {
    //gpDC->drawImage((JImage*)GETIMG(ID_background), 0, GamePage::SCREEN_SHIFT_Y, 20);
    GamePage::onPaint();

    /*
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    ab.SetFlags(flags);
    world->DrawDebugData();
    */
    break;
  }
  case GAME_RUNING: ///飞行中,不接受抓鸟控制
    //gpDC->drawImage((JImage*)GETIMG(ID_background), 0, GamePage::SCREEN_SHIFT_Y, 20);
    GamePage::onPaint();

    /*
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    ab.SetFlags(flags);
    world->DrawDebugData();
    */
    break;
  }
}

int Session1::createWorld()
{
  world->SetDebugDraw(&ab);
  //addWall(world, 200, 720, -200,240);
  initBlock(world, nFloorNum, nFloorList, nBlockNum, 
            nBlockList, objectDataList, objectNum, s_controllable, this, 300);

  initBlock(world, nBirdFloorNum, nBirdFloorList, nBirdNum, 
            nBirdList, objectDataList, objectNum, s_controllable, this, 0);
  return 0;
}
//}
