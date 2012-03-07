#include "MainEntryPage.h"

#include "../objectDef.h"
#include "../Configure.h"
#include <Box2D/Box2D.h>
#include "../Tasks.h"
//
extern bool gSoundOnFlag;
extern bool gPaintStatus;

void MainEntryPage::preLoad()
{
  #define IMGSEG
  #define RES(X) load_##X(0); 
  #include "MainEntryPage.inc"
  #undef RES
  #undef IMGSEG
}

MainEntryPage::MainEntryPage()
{
	btn[0].x=70;
	btn[0].y=106;
	btn[0].width=150;
	btn[0].height=180;
	//
	btn[1].x=0;
	btn[1].y=0;
	btn[1].width=55;
	btn[1].height=55;
	//
	btn[2].x=0;
	btn[2].y=420;
	btn[2].width=55;
	btn[2].height=55;
	//
	btnQuit[0].x=94;
	btnQuit[0].y=161;
	btnQuit[1].x=94;
	btnQuit[1].y=260;
	btnQuit[0].width=55;
	btnQuit[0].height=55;
	btnQuit[1].width=55;
	btnQuit[1].height=55;
	state = ENTRY_LOADING;
		
} 
MainEntryPage::~MainEntryPage()
{
	onDestory();
} 

void MainEntryPage::onPaint()
{	
	switch(state)
	{
	case ENTRY_LOADING:
		imgBg[0] = GETIMG(ID_entrybg);
		imgBg[1] = GETIMG(ID_bgquit);
		imgSoundoff =  GETIMG(ID_msoundoff);
		imgStart = GETIMG(ID_start1);
		imgQuiting=GETIMG(ID_quiting);
		//
		state= MAIN_ENTRY_WAITSTART;
		gPaintStatus=false;
	case MAIN_ENTRY_WAITSTART:
		gpDC->drawImage( imgBg[0], 0, 0, 20);	
		if (btn[0].press==1)
			gpDC->drawImage( imgStart, 0, 0, 20);
		if (!gSoundOnFlag)
			gpDC->drawImage(imgSoundoff, 0, 480-59, 20);
		break;
	case MAIN_ENTRY_QUITTIP:
		gpDC->drawImage( imgBg[1], 0, 0, 20);	
		break;
	}
}

Page* MainEntryPage::create()
{
   return SafeNew(MainEntryPage);
}

int MainEntryPage::init()
{	
	return 1;
}
void MainEntryPage::onDestory()
{
  DELIMG(ID_entrybg);
  DELIMG(ID_bgquit);
  DELIMG(ID_msoundoff);
  DELIMG(ID_start1);
}

void MainEntryPage::running()
{
	

}
bool MainEntryPage::OnPointerDragged(int x, int y)
{
	return true;
}

void MainEntryPage::btnPressAction(int code)
{
	btn[code].press=1;
}
void MainEntryPage::btnReleaseAction(int code)
{
	switch(code)
	{
	case 0:
		++task->next_page;
		task->step=task->NEXT_PAGE;
		break;
	case 1:
		state=MAIN_ENTRY_QUITTIP;
		break;
	case 2:
		if (gSoundOnFlag)
			gSoundOnFlag=false;
		else
			gSoundOnFlag=true;
		break;
	
	}
}

void MainEntryPage::btnQuitReleaseAction(int code)
{
	if (code == 0)
	{
		gpDC->setColor(0);  
		gpDC->drawImage(imgQuiting, 320/2, 480/2, ACHOR_HV);			
		destroyApp(false);
	}else
		state=MAIN_ENTRY_WAITSTART;
}

bool MainEntryPage::OnPointerReleased(int x, int y)
{
	int i;
	for (i=0; i< 3; i++)
		btn[i].press=0;
	for (i=0; i< 2; i++)
		btnQuit[i].press=0;
	
	if (state == MAIN_ENTRY_WAITSTART)
	{
		for (i=0; i< 2; i++)
			btn[i].press=0;
		
		for (i=0; i< 3; i++)
		{
			if (InButtonPic(x, y, 0, 0, btn[i], 5) >0)
				btnReleaseAction(i);
		}	
	}else if (state == MAIN_ENTRY_QUITTIP)
	{
		for (i=0; i< 2; i++)
		{
			if (InButtonPic(x, y, 0, 0, btnQuit[i], 5) >0)
				btnQuitReleaseAction(i);
		}	
	}
	return true;
}
bool MainEntryPage::OnPointerPressed(int x, int y)
{
	int i;
	if (state == MAIN_ENTRY_WAITSTART)
	{
		for (i=0; i< 3; i++)
		{
		if (InButtonPic(x, y, 0, 0, btn[i], 5) >0)
			btnPressAction(i);
		}
	}
	
	
	return true;
}