#include "MainStagePage.h"
#include "../objectDef.h"
#include "../Configure.h"
#include <Box2D/Box2D.h>
#include "../Tasks.h"
//
extern bool gSoundOnFlag;
extern bool gPaintStatus;
extern int iStageNum;
void MainStagePage::preLoad()
{
  #define IMGSEG
  #define RES(X) load_##X(0); 
  #include "MainStagePage.inc"
  #undef RES
  #undef IMGSEG
}


MainStagePage::MainStagePage()
{
	btn[0].x = 89;
	btn[0].y = 93;
	btn[1].x = 89;
	btn[1].y = 280;
	btn[0].width = 136;
	btn[0].height = 227-93;
	btn[1].width  = btn[0].width ;
	btn[1].height =btn[0].height;
	//
	btn[2].x = 3;
	btn[2].y = 3;
	btn[2].width = 49;
	btn[2].height = 58;
	state = LOADING;
} 
MainStagePage::~MainStagePage()
{
	
} 
void drawStageIco(int x, int y, int movey)
{
}
void MainStagePage::onPaint()
{	
	if (state== LOADING)
	{
			imgBg =  GETIMG(ID_guankabg);
			imgReturnBig = GETIMG(ID_mreurnbig);
			imgStage[0] =  GETIMG(ID_guan1);
			imgStage[1] =  GETIMG(ID_guan2);
			state=MAIN_STATE_WAIT;
			gPaintStatus=false;
	}
	else if (state== MAIN_STATE_WAIT)		
	{
		gpDC->drawImage( imgBg, 0, 0, 20);	
		if (btn[0].press==1)
			gpDC->drawImage(imgStage[0],155 ,155, ACHOR_HV);	
		else if (btn[1].press==1)
			gpDC->drawImage(imgStage[1],155 ,344, ACHOR_HV);	
		else if(btn[2].press==1)
			gpDC->drawImage(imgReturnBig,28 ,30, ACHOR_HV);	
	}	
}

Page* MainStagePage::create()
{
   return SafeNew(MainStagePage);
}

int MainStagePage::init()
{	
	return 1;
}
void MainStagePage::onDestory()
{
	DELIMG(ID_guankabg);
DELIMG(ID_start1);
DELIMG(ID_guan1);
DELIMG(ID_mreurnbig);
}

void MainStagePage::running()
{
	int no;
	
}
bool MainStagePage::OnPointerDragged(int x, int y)
{
	return true;
}

bool MainStagePage::OnPointerReleased(int x, int y)
{
	int i;
	for (i=0; i< 3; i++)
		btn[i].press=0;

			for (i=0; i< 3; i++)
			{
				if (InButtonPic(x, y, 0, 0, btn[i], 5) >0)
				{
					if (i==2)					
					{
						task->next_page=0;
						task->step=task->NEXT_PAGE;
					}
					else
					{
						iStageNum = i;
						++task->next_page;
						task->step=task->NEXT_PAGE;
					}
				}
			}
			
	return true;
}
bool MainStagePage::OnPointerPressed(int x, int y)
{
	int i;
	
		for (i=0; i< 3; i++)
		{
			if (InButtonPic(x, y, 0, 0, btn[i], 5) >0)
				btn[i].press=1;
		}
	
	
	return true;
}