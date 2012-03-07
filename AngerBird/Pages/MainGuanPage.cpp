#include "MainGuanPage.h"
#include "osport.h"
#include "jport.h"
#include "aeestdlib.h"
#include<JFileOutputStream.h >
#include<JFileInputStream.h >
#include "../objectDef.h"
#include "../Configure.h"
#include <Box2D/Box2D.h>
#include "../Tasks.h"
extern bool gPaintStatus;
extern bool gSoundOnFlag;
int iStageNum=0;

void MainGuanPage::preLoad()
{
  #define IMGSEG
  #define RES(X) load_##X(0); 
  #include "MainGuanPage.inc"
  #undef RES
  #undef IMGSEG
}


MainGuanPage::MainGuanPage()
{	
	int i, j;
	int orix=200;
	int oriy=60;
	int x=orix;
	int y=oriy;
	state=GUAN_LOADING;
	//
	int num=0;
	for (i=0; i< 3; i++)
	{
		for (j=0; j<7; j++)
		{			
			btn[num].x = x;
			btn[num].y = y;
			y = y + 52;
			btn[num].width=51;
			btn[num].height=42;
			num++;
		}
		x= x- 55;
		y=oriy;
	}

	btn[21].x = 4;
	btn[21].y = 6;
	btn[21].width=52;
	btn[21].height=62;
	//
	char path[256];
	SPRINTF(path, "bird%d.dat", iStageNum+1);
	readFileStr(path, stageData, 21);

} 
MainGuanPage::~MainGuanPage()
{
	
} 

/*
9  -- 未开
0  -- 3  星数目
*/
void MainGuanPage::showStar(int x, int y, int num)
{
	int movex ;
	int starWidth=9;
	int starHeight=7;
	int inter=2;
	int i;
	for (i=0; i< 3; i++)
	{
		switch(i)
		{
		case 0:
			if (num==0)
				movex=0;
			else
				movex=starWidth;
			gpDC->drawImage(imgStar, x, y,movex, 0, starWidth, starHeight, 20);
			num--;
			y=y+starHeight+inter;
			break;
		case 1:
			if (num<=0)
				movex=0;
			else
				movex=starWidth;
			gpDC->drawImage(imgStar, x, y,movex, 0, starWidth, starHeight, 20);
			num--;
			y=y+starHeight+inter;
			break;
		case 2:
			if (num<=0)
				movex=0;
			else
				movex=starWidth;
			gpDC->drawImage(imgStar, x, y,movex, 0, starWidth, starHeight, 20);
			break;

		}
	}

}

void MainGuanPage::onPaint()
{	
	int i,j;
	switch(state)
	{
	case GUAN_LOADING:
		if (iStageNum==0)
			imgBg[iStageNum] =  GETIMG(ID_guan1bg);
		else
			imgBg[iStageNum] =  GETIMG(ID_guan2bg);
		imgBtn[0] =  GETIMG(ID_guanbtn1);
		imgBtn[1] =  GETIMG(ID_guanbtn2);
		imgReturnBig=  GETIMG(ID_return_big);
		imgLock=  GETIMG(ID_lock);
		imgNumber=  GETIMG(ID_guanka_munber);
	    imgStar=  GETIMG(ID_guanka_star);
		////////////////////////////////////
		state= GUAN_WAIT;
		gPaintStatus=false;
		break;
	case GUAN_WAIT:
		gpDC->drawImage( imgBg[iStageNum], 0, 0, 20);	
		int numShiftx=16;
		int numShifty=3;
		int bigMove=2;
		int startShiftx=0;
		int startShifty=7;
		//
		if(btn[21].press==1)
			gpDC->drawImage(imgReturnBig,28 ,30, ACHOR_HV);	
		for (i=0; i< 21; i++)
		{
				/////显示星
				if (stageData[i] == '9')
				{
					gpDC->drawImage( imgLock, btn[i].x, btn[i].y, 20);	
				}else
				{
					int num;
					if (stageData[i] == '0')
						num=0;
					else if (stageData[i] == '1')
						num=1;
					else  if (stageData[i] == '2')	
						num=2;
					else
						num=3;
					
					if (btn[i].press == 1)
					{
						gpDC->drawImage( imgBtn[1], btn[i].x, btn[i].y, 20);	
						 showPicNumber(i+1,  btn[i].x+numShiftx+bigMove, btn[i].y+numShifty+bigMove);
						
						 showStar(btn[i].x+startShiftx+bigMove-1, btn[i].y+startShifty+bigMove, num);
					}
					else
					{
						gpDC->drawImage( imgBtn[0],btn[i].x, btn[i].y, 20);	
						showPicNumber(i+1,  btn[i].x+numShiftx, btn[i].y+numShifty);

						showStar(btn[i].x+startShiftx, btn[i].y+startShifty, num);
					}
					
				}
		}
		break;
	}
}

Page* MainGuanPage::create()
{
   return SafeNew(MainGuanPage);
}

int MainGuanPage::init()
{	
	return 1;
}
void MainGuanPage::onDestory()
{
	DELIMG(ID_guan1bg);
DELIMG(ID_guan2bg);
DELIMG(ID_guanbtn1);
DELIMG(ID_guanbtn2);
DELIMG(ID_return_big);
DELIMG(ID_lock);
DELIMG(ID_guanka_star);
DELIMG(ID_guanka_munber);
}

void MainGuanPage::running()
{
	int no;
	
}
bool MainGuanPage::OnPointerDragged(int x, int y)
{
	return true;
}
void MainGuanPage::btnReleaseAction(int code)
{
	if (code == 21)
	{
		task->next_page=1;
		task->step=task->NEXT_PAGE;
	}else
	{
		task->next_page=3;
		task->step=task->NEXT_PAGE;
	}
}
bool MainGuanPage::OnPointerReleased(int x, int y)
{
	int i;
	for (i=0; i< 22; i++)
	{	
			btn[i].press=0;
	}
//
	switch(state)
	{
	case GUAN_WAIT:
		for (i=0; i<22; i++)
		{			
			if (InButtonPic(x, y, 0, 0, btn[i], 3) >0)
				btnReleaseAction(i);
		}
		break;	
	}
	
	return true;
}
bool MainGuanPage::OnPointerPressed(int x, int y)
{
	int j;
	switch(state)
	{
	case GUAN_WAIT:
		for (j=0; j<22; j++)
		{			
			if (InButtonPic(x, y, 0, 0, btn[j], 3) >0)
				btn[j].press=1;
		}
		break;	
	}
	
	return true;
}



void  MainGuanPage::showPicNumber(int number, int x, int y)
{
	int num, pos, i;
	int shiwan, wan,qian,bai,shi,ge;
	num=number;
	if (num >= 1000000  || num < 0)
		return;
	
	shiwan=num/100000;
	num=num-shiwan*100000;
	wan=num/10000;
	num=num-wan*10000;
	qian=num/1000;
	num=num-qian*1000;
	bai=num/100;
	num=num-bai*100;
	shi=num/10;
	ge=num-shi*10;
	int numHeight = 17;
	int numWidth=22;	
	int interWid = 0;
	//
	if (shiwan > 0)
	{
		gpDC->drawImage(imgNumber, x, y, 0,numHeight*shiwan, numWidth,numHeight ,20);
		y = y + numHeight + interWid;
	}
	if (shiwan>0 || wan >0)
	{
		gpDC->drawImage(imgNumber, x, y, 0,numHeight*wan, numWidth,numHeight ,20);
		y = y + numHeight +  interWid;
	}
	
	if (shiwan>0 || wan >0 || qian >0)
	{
		gpDC->drawImage(imgNumber, x, y, 0,numHeight*qian, numWidth,numHeight ,20);
		y = y +  numHeight + interWid;
	}
	
	if (shiwan>0 || wan >0 || qian >0 || bai > 0)
	{
		gpDC->drawImage(imgNumber, x, y,0,numHeight*bai, numWidth,numHeight ,20);
		y = y +  numHeight + interWid;
	}
	
	if (shiwan>0 || wan >0 || qian >0 || bai > 0 || shi > 0)
	{
		gpDC->drawImage(imgNumber, x, y, 0,numHeight*shi, numWidth,numHeight ,20);
		y = y + numHeight +  interWid;
	}
	
	if (number <10)
	{
		gpDC->drawImage(imgNumber, x, y,0,numHeight*0,  numWidth,numHeight ,20);
		y = y + numHeight +  interWid;
	}
	gpDC->drawImage(imgNumber, x, y,0,numHeight*ge,  numWidth,numHeight ,20);

	return;
	
}


void MainGuanPage::readFileStr(char *filename, char *buf, int len)
{
	JFileInputStream* gpFileIn;
	gpFileIn=SafeNew JFileInputStream(filename); 
	gpFileIn->ReadCharArray(buf, len);
	SafeDelete(gpFileIn);
	return;
}


void MainGuanPage::writeFileStr(char *filename, char *str, int len)
{
	JFileOutputStream* gpFileOut;
	gpFileOut=SafeNew JFileOutputStream(filename); 
	gpFileOut->WriteChars(str, len);
	SafeDelete(gpFileOut);
	return;
}