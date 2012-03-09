#include "APageScreen.h"
#include "osport.h"
#include "jport.h"
#include "pre.h"
#include "tasks.h"
#include "Page.h"
#include "Configure.h"
#include "ResPool.h"
//using namespace NBird;

//全局的dc
Graphics     gpDC;
bool gSoundOnFlag=true;
bool gPaintStatus=true;
int lastPageIdx=-1;
int firstEnterFlag=0;
int firstPageShowTimes=0;
#define LOG_SHOW_TIMES 2
//全局的shell
IShell*      gpShell;
Image imgLoading;
Image imgFirstLoading;

int framecnt = 0;

CAPageScreen::CAPageScreen():CBaseScreen()
{
    OnCreate(NULL);
}

CAPageScreen::~CAPageScreen()
{
    OnDestroy();
}

int CAPageScreen::OnCreate(void* pi)
{

    //STEP 0: 在构造函数中记录全局DC和SHELL， 方便后续使用
    gpDC        = m_pGlobal->m_pGraphics;
    gpShell     = m_pGlobal->m_pMe->m_pIShell;

    gpDC->setClip();	
    //STEP 1: 游戏的初始化工作
    // GameInit();

	CONF.init();
	CONF.gravity.Set(-10.0f, 0.0f);
	CONF.X = 320;
	CONF.Y = 480;
  task  = SafeNew Tasks;
  imgLoading=GETIMG(ID_loading);
  imgFirstLoading=GETIMG(ID_firstloading);
  return 0;
}
int CAPageScreen::OnDestroy(void)
{

    //STEP 8 退出应用时，释放所有的资源    
    CancelTimer();

    //GameRelease();
    SafeDelete(task);
    Configure::destory();
    ResPool::destory();
    //LeftMenu::destory();
    
    return 0;
}

//FALSE表示未处理消息， TRUE表示处理了消息
BOOL CAPageScreen::OnWndProc(void* pi, AEEEvent eCode , uint16 wParam , uint32 dwParam)
{
    BOOL bRet = CBaseScreen::OnWndProc(pi, eCode, wParam, dwParam);

    return bRet;
}

//代码的总入口
void CAPageScreen::OnShow(BOOL bShow)
{
    //STEP 2   当创建成功后， 系统会自动调用当前窗口的ONSHOW
    //对于只有一个window，通过状态机控制的游戏而言， 这个是
    //游戏的总入口， 在这里启动定时器
    //如果只有一个定时器， 则窗口的缺省定时器已经够用了
    //在ontimer中处理游戏主逻辑
        m_bVisible = TRUE;
        //到前台了， 打背景灯
        gpDC->SetBackLight(TRUE);
        //通过定时器正式启动游戏主逻辑, 1个毫秒后启动
        SetTimer(1);
}

AECHAR  test[]={'h', 'l', 0};

void drawLayer()
{
	int i,j;
	int inter=2;
	for (i=0; i< 320; i=i+inter)
	{
		for (j=0; j< 480; j=j+inter)
		{
			gpDC->drawLine(i, j, i, j+1);			
		}
	}
	gpDC->drawImage(imgLoading, 160, 240, ACHOR_HV);
}

int CAPageScreen::OnPaint(void* pi)
{
    //STEP 4: 游戏的主逻辑可放在这里
    //完成每帧的绘制
    //测试代码只是刷成黑色(清屏)

    if (!m_bVisible)    return 0;

    int idx = task->get_current_page();
	if (lastPageIdx != idx)
	{
		if (idx == 1)
			firstEnterFlag=2;
		//
		if (firstEnterFlag == 0)
		{
			if (firstPageShowTimes++ == LOG_SHOW_TIMES)
				firstEnterFlag=1;
			gpDC->setColor(0);
			gpDC->clearScreen();
			gpDC->drawImage(imgFirstLoading, 0, 0, 20);
			return 0;
		}
		if (firstEnterFlag == 2)
			drawLayer();
		//
		gPaintStatus=true;
		lastPageIdx=idx;
		

		return 0;
	}
	if (gPaintStatus==false)   
	{
		gpDC->setColor(0);
		gpDC->clearScreen();
	}
	
  if(task->list[idx].page != 0)
  {
    task->list[idx].page->onPaint();
  }
    return 0;
}

void CAPageScreen::OnTimer(void)
{
  int idx = task->get_current_page();
  
  switch(task->step)
  {
    case Tasks::NEXT_PAGE:
    {
      if (task->list[idx].page != 0)///先删除旧页
      {
        SafeDelete(task->list[idx].page);
        task->list[idx].page = 0;
      }
      idx = task->get_next_page(); ///获取下一页索引
      if (idx == -1) ///-1表示退出
      {
        destroyApp(false);
      }
      task->step = task->CURRENT_PAGE;
    }
    case Tasks::CURRENT_PAGE:
    {
      if (task->list[idx].creatFcn != 0)
      {
        if (task->list[idx].page == 0)
        {
          ///创建并初始化页面
          task->list[idx].page = task->list[idx].creatFcn();
          task->list[idx].page->init();
          task->current_page = idx;
        }
        task->list[idx].page->running();
      }
      break;
    }
  }

  //STEP 3 游戏定时器回调, 在这里调用游戏的主逻辑
  //主逻辑
  OnPaint(NULL);

  //STEP 6  这个DEMO游戏是完成后必然刷屏（把更新的游戏画面刷新到屏幕)
  //类似java的servicerepaints
  //其他游戏，是否刷屏也可以放在主逻辑的状态机中自己处理
  //刷屏
  gpDC->FlushScreen();

  //这是一个简单的定时器处理例子，启动下一次定时器
  //类似于JAVA的  thread:sleep操作
  //限制在30FPS以下， 如果当前时间小于30MS， 计算SLEEP时间
  //如果游戏比较简单，或者追求速度， 只要SetTimer(5)就好了
  SetTimer(1);   
}

BOOL CAPageScreen::OnSuspend()
{
    //STEP 6
    //被打断时应当停止定时器， 关闭网络
    // 尽可能释放资源
    //这个例子里头简单的关闭了定时器

    CBaseScreen::OnSuspend();

    CancelTimer();
    
    return TRUE;
}

BOOL CAPageScreen::OnResume()
{
    //STEP 7
    //恢复时应当重新启动定时器， 恢复资源
    //这个例子里头简单的重启了定时器
    //通过定时器驱动逻辑运行

    CBaseScreen::OnResume();

    SetTimer(1);

    return TRUE;
}
BOOL CAPageScreen::OnKeyPressed(int keyCode)
{
    //STEP 5  按键消息处理， 这个DEMO游戏是记录键值方式的
    //其他游戏如果按键对游戏逻辑/状态有直接影响， 可以均在此处处理
    //BREWKEY2JAVA可将游戏码变成JAVA的
    //int i = BrewKey2Java(keyCode);

    //左软件退出！
    if(AVK_SOFT1 == keyCode)
    {
       OnDestroy();

       destroyApp(false);
    }


    return TRUE;
}

BOOL CAPageScreen::OnKeyReleased(int keyCode)
{
    //STEP 5  按键消息处理-弹起， 这个DEMO游戏是记录键值方式的
    //其他游戏如果按键对游戏逻辑/状态有直接影响， 可以均在此处处理

    int i = BrewKey2Java(keyCode);

    return TRUE; //已处理KEY事件
}

BOOL CAPageScreen::OnPointerPressed(int x, int y)
{
    BOOL bRet = FALSE;
    int idx = task->get_current_page();
    if (task->list[idx].page != 0)
    {
      bRet = task->list[idx].page->OnPointerPressed(x,y);
    }

    return bRet;
}
BOOL CAPageScreen::OnPointerDragged(int x, int y)
{
    BOOL bRet = FALSE;
    int idx = task->get_current_page();
    if (task->list[idx].page != 0)
    {
      bRet = task->list[idx].page->OnPointerDragged(x,y);
    }

    return bRet;
}
BOOL CAPageScreen::OnPointerReleased(int x, int y)
{
    BOOL bRet = FALSE;
    int idx = task->get_current_page();
    if (task->list[idx].page != 0)
    {
      bRet = task->list[idx].page->OnPointerReleased(x,y);
    }

    return bRet;
}

