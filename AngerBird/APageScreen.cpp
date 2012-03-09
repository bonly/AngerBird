#include "APageScreen.h"
#include "osport.h"
#include "jport.h"
#include "pre.h"
#include "tasks.h"
#include "Page.h"
#include "Configure.h"
#include "ResPool.h"
//using namespace NBird;

//ȫ�ֵ�dc
Graphics     gpDC;
bool gSoundOnFlag=true;
bool gPaintStatus=true;
int lastPageIdx=-1;
int firstEnterFlag=0;
int firstPageShowTimes=0;
#define LOG_SHOW_TIMES 2
//ȫ�ֵ�shell
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

    //STEP 0: �ڹ��캯���м�¼ȫ��DC��SHELL�� �������ʹ��
    gpDC        = m_pGlobal->m_pGraphics;
    gpShell     = m_pGlobal->m_pMe->m_pIShell;

    gpDC->setClip();	
    //STEP 1: ��Ϸ�ĳ�ʼ������
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

    //STEP 8 �˳�Ӧ��ʱ���ͷ����е���Դ    
    CancelTimer();

    //GameRelease();
    SafeDelete(task);
    Configure::destory();
    ResPool::destory();
    //LeftMenu::destory();
    
    return 0;
}

//FALSE��ʾδ������Ϣ�� TRUE��ʾ��������Ϣ
BOOL CAPageScreen::OnWndProc(void* pi, AEEEvent eCode , uint16 wParam , uint32 dwParam)
{
    BOOL bRet = CBaseScreen::OnWndProc(pi, eCode, wParam, dwParam);

    return bRet;
}

//����������
void CAPageScreen::OnShow(BOOL bShow)
{
    //STEP 2   �������ɹ��� ϵͳ���Զ����õ�ǰ���ڵ�ONSHOW
    //����ֻ��һ��window��ͨ��״̬�����Ƶ���Ϸ���ԣ� �����
    //��Ϸ������ڣ� ������������ʱ��
    //���ֻ��һ����ʱ���� �򴰿ڵ�ȱʡ��ʱ���Ѿ�������
    //��ontimer�д�����Ϸ���߼�
        m_bVisible = TRUE;
        //��ǰ̨�ˣ� �򱳾���
        gpDC->SetBackLight(TRUE);
        //ͨ����ʱ����ʽ������Ϸ���߼�, 1�����������
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
    //STEP 4: ��Ϸ�����߼��ɷ�������
    //���ÿ֡�Ļ���
    //���Դ���ֻ��ˢ�ɺ�ɫ(����)

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
      if (task->list[idx].page != 0)///��ɾ����ҳ
      {
        SafeDelete(task->list[idx].page);
        task->list[idx].page = 0;
      }
      idx = task->get_next_page(); ///��ȡ��һҳ����
      if (idx == -1) ///-1��ʾ�˳�
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
          ///��������ʼ��ҳ��
          task->list[idx].page = task->list[idx].creatFcn();
          task->list[idx].page->init();
          task->current_page = idx;
        }
        task->list[idx].page->running();
      }
      break;
    }
  }

  //STEP 3 ��Ϸ��ʱ���ص�, �����������Ϸ�����߼�
  //���߼�
  OnPaint(NULL);

  //STEP 6  ���DEMO��Ϸ����ɺ��Ȼˢ�����Ѹ��µ���Ϸ����ˢ�µ���Ļ)
  //����java��servicerepaints
  //������Ϸ���Ƿ�ˢ��Ҳ���Է������߼���״̬�����Լ�����
  //ˢ��
  gpDC->FlushScreen();

  //����һ���򵥵Ķ�ʱ���������ӣ�������һ�ζ�ʱ��
  //������JAVA��  thread:sleep����
  //������30FPS���£� �����ǰʱ��С��30MS�� ����SLEEPʱ��
  //�����Ϸ�Ƚϼ򵥣�����׷���ٶȣ� ֻҪSetTimer(5)�ͺ���
  SetTimer(1);   
}

BOOL CAPageScreen::OnSuspend()
{
    //STEP 6
    //�����ʱӦ��ֹͣ��ʱ���� �ر�����
    // �������ͷ���Դ
    //���������ͷ�򵥵Ĺر��˶�ʱ��

    CBaseScreen::OnSuspend();

    CancelTimer();
    
    return TRUE;
}

BOOL CAPageScreen::OnResume()
{
    //STEP 7
    //�ָ�ʱӦ������������ʱ���� �ָ���Դ
    //���������ͷ�򵥵������˶�ʱ��
    //ͨ����ʱ�������߼�����

    CBaseScreen::OnResume();

    SetTimer(1);

    return TRUE;
}
BOOL CAPageScreen::OnKeyPressed(int keyCode)
{
    //STEP 5  ������Ϣ���� ���DEMO��Ϸ�Ǽ�¼��ֵ��ʽ��
    //������Ϸ�����������Ϸ�߼�/״̬��ֱ��Ӱ�죬 ���Ծ��ڴ˴�����
    //BREWKEY2JAVA�ɽ���Ϸ����JAVA��
    //int i = BrewKey2Java(keyCode);

    //������˳���
    if(AVK_SOFT1 == keyCode)
    {
       OnDestroy();

       destroyApp(false);
    }


    return TRUE;
}

BOOL CAPageScreen::OnKeyReleased(int keyCode)
{
    //STEP 5  ������Ϣ����-���� ���DEMO��Ϸ�Ǽ�¼��ֵ��ʽ��
    //������Ϸ�����������Ϸ�߼�/״̬��ֱ��Ӱ�죬 ���Ծ��ڴ˴�����

    int i = BrewKey2Java(keyCode);

    return TRUE; //�Ѵ���KEY�¼�
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

