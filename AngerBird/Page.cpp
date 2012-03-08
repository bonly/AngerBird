/**
 *  @file Page.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#include "pre.h"
#include "Configure.h"
#include "Page.h"
#include "ResPool.h"
#include "BuildBlock.h"
#include "Life/Life.h"
#include "pages/LeftMenu.h"
#include "Life/ContactListener.h"
//#include <aeeappgen.h>
//#include "basescreen.h"

//namespace NBird {
//int testx= 65;
//int testy= 65;

int GamePage::SCREEN_SHIFT_Y = 0;
extern bool gPaintStatus;
Page::Page()
{
	
}

Page::~Page()
{
}

int ControlPage::init()
{
  return 0;
}

void ControlPage::onDestory()
{
  return;
}

void ControlPage::running()
{
  return;
}

void ControlPage::onPaint()
{
  return;
}
ControlPage::ControlPage()
{
}
ControlPage::~ControlPage()
{

}

GamePage::GamePage():lastY(0),controllable(0),controlled(0)
{
}

GamePage::~GamePage()
{
  onDestory();
}

void GamePage::onDestory()
{
  SafeDelete(world);
  SafeDelete(contact);
  SafeDelete(contact_filter);
  for (int i=0; i<ARRMAX; ++i)
    SafeDelete(ani[i]);

  return;
}

int GamePage::resume()
{
  return 0;
}

int GamePage::pause()
{
  return 0;
}


int GamePage::init()
{
  world = SafeNew b2World(CONF.gravity);
  contact = SafeNew ContactListener;
  world->SetContactListener(contact);
  contact_filter = SafeNew ContactFilter;
  world->SetContactFilter(contact_filter);
  idxControl = -1;
 
  slingx += FLOOR_LEVEL_X;  //����λ��
  //slingx = 120;
  slingy = 100;  //��������
  return 0;
}


//ƴ�ӱ���ͼ
void GamePage::drawGameBg()
{
	int extrax, bgy;
	gpDC->drawImage(imgBg, SCREEN_SHIFT_X, SCREEN_SHIFT_Y, 20);
	if (SCREEN_SHIFT_X != 0)
	{
		extrax= 320+SCREEN_SHIFT_X;
		while(true)
		{
			if (extrax < 320)
			{
				gpDC->drawImage(imgExtra, extrax, SCREEN_SHIFT_Y, 20);
				extrax += 50;
			}else
				break;
		}
	}
	///
	if (SCREEN_SHIFT_Y != 0)
	{
		bgy= 480+SCREEN_SHIFT_Y;
		while(true)
		{
			if (bgy < 480)
			{
				gpDC->drawImage(imgBg, SCREEN_SHIFT_X, bgy, 20);
				
				extrax= 320+SCREEN_SHIFT_X;
				while(true)
				{
					if (extrax < 320)
					{
						gpDC->drawImage(imgExtra, extrax, bgy, 20);
						extrax += 50;
					}else
						break;
				}
				bgy += 480;
				//
			}else
				break;
		}
	}
}
void GamePage::drawGrass()
{
	int extrax, bgy;
	gpDC->drawImage(imgGrass, SCREEN_SHIFT_X+FLOOR_LEVEL_X, SCREEN_SHIFT_Y, 20);
	if (SCREEN_SHIFT_Y != 0)
	{
		bgy= 480+SCREEN_SHIFT_Y;
		while(true)
		{
			if (bgy < 480)
			{
				gpDC->drawImage(imgGrass, SCREEN_SHIFT_X, bgy, 20);						
				bgy += 480;
			}else
				break;
		}
	}
}
void GamePage::drawSlingLine(int birdx, int birdy)
{
	int i, j;
	int centerx, centery, angle;
	int x[2];
	int y[2];
	//
	if (birdx <= 0 ||  birdx >= 320 ||  birdy <= 0 || birdy >= 480)
	{
		return;
	}
	//

	//int birdx=bird->GetPosition().x * 50+SCREEN_SHIFT_X;
	//int birdy=bird->GetPosition().y * 50+SCREEN_SHIFT_Y;
	
	
	x[0]=slingx+SLING_DOT1_X+SCREEN_SHIFT_X;
	y[0]=slingy+SLING_DOT1_Y+SCREEN_SHIFT_X;
	x[1]=slingx+SLING_DOT2_X+SCREEN_SHIFT_X;
	y[1]=slingy+SLING_DOT2_Y+SCREEN_SHIFT_X;
	
	if (birdy >=  y[0] || birdy >=  y[1])
		return;

	//
	for (i=0; i< 2; i++)
	{
		int cutx = abs(birdx-x[i]);
		int cuty = abs(birdy-y[i]);
		
		float32 distance = sqrtl( pow(float(cutx),2) + pow(float(cuty),2));
		///sinת��Ϊ�Ƕ�(��������)
		///�����ߵ�sin
		float32 sina = (float32)cuty/(float32)distance;
		float32 cosa = (float32)cutx/(float32)distance;

		int oc = ceill(sina * (180.f/b2_pi));
		
		if (i == 0 && distance> MAX_ROLE_LEN)
		{
			//���¾���bird������
			int cy = MAX_ROLE_LEN * sina;
			int cx =  MAX_ROLE_LEN * cosa;
			if (birdx < x[0])
				birdx = x[0] - cx;
			else
				birdx = x[0] + cx;
			birdy=y[0] - cy;
			cutx = abs(birdx-x[i]);
		  cuty = abs(birdy-y[i]);
			sina = (float32)cuty/(float32)distance;
		  cosa = (float32)cutx/(float32)distance;
		  oc = ceill(sina * (180.f/b2_pi));
			//
			//
		
		}
			
		for (j=2; j< 300; j=j+2)
		{
			int ox, oy;
			if (birdx >x[i])
			{
				gpDC->drawImageWithRotate(imgRope[0], ox, oy, ACHOR_HV, oc);
				ox=x[i]+j * cosa;
			}
			else
			{
				gpDC->drawImageWithRotate(imgRope[1], ox, oy, ACHOR_HV, oc);
				ox = x[i]-j * cosa;
			}
			 oy = y[i]-j * sina;
			//
			
			//
			if (birdy >= oy)	
			{
				if (i == 1)
					gpDC->drawImageWithRotate(imgRope[2], ox, oy, ACHOR_HV, oc);		
				break;
			}
		}
	}
}
void GamePage::onPaint()
{
  switch(step)
  {
  case GAME_LOADING:
	  break;
  case GAME_WAIT:
  case GAME_GETBIRD:
  case GAME_SCROLL:
  case GAME_PAUSE:
  case GAME_OVER:
  case GAME_END:
  case GAME_RUNING:
    //SCREEN_SHIFT_Y=SCREEN_SHIFT_Y-2;
    //SCREEN_SHIFT_X=SCREEN_SHIFT_X-2;
    drawGameBg();
    gpDC->drawImage(imgSling, slingx, slingy, 20);   //������
    //������
    drawGrass();
    break;
  }

  DrawData();

  ///���켣
  gpDC->setColor(255, 0, 0);
  JImage* tr = GETIMG(ID_track);
  for (int i=0; i<track_num; ++i)
  {
    //gpDC->drawRect(track[i][0], track[i][1], 4, 4);
    gpDC->drawImage(tr, track[i][0], track[i][1], 20);
  }
  return;
}
  
void GamePage::running()
{
  switch(step)
  {
    case PRELOAD:
      break;
    case PRELOADING:
      imgRope[0]=GETIMG(ID_rope1);
	    imgRope[1]=GETIMG(ID_rope2);
	    imgRope[2]=GETIMG(ID_rope3);
	    imgExtra=GETIMG(ID_birdbg_extern);
	    imgBird[0]= GETIMG(ID_bird_red_1);
	    imgBird[1]= GETIMG(ID_bird_addspeed_1);
	    imgBird[2]= GETIMG(ID_bird_three_1);
	    imgBird[3]= GETIMG(ID_bird_bomb_1);
	    imgBird[4]= GETIMG(ID_bird_egg_1);
	    imgSling= GETIMG(ID_sling);  
      slingX = slingx + imgSling->getWidth(); ///���õ�����������λ��
      slingY = slingy + imgSling->getHeight()/2; 

	    //������������
	    addWall(world, FLOOR_LEVEL_X, 1500, 0,240);
      break;
    case PRELOAD_END: ///Ԥ�����ڽ���
      break;
    case GAME_LOADING:
      step = GAME_GETBIRD;
      break;
    case GAME_GETBIRD:
      if(getBird())
      {
        controlled->life->status &= ~Life::s_jumpAble;///�޸�״̬,��������
        controlled->life->status |= Life::s_getReady; ///�޸�״̬,׼��
        int x = M2P(controlled->life->body->GetPosition().x);
        int y = M2P(controlled->life->body->GetPosition().y);
        if(JumpLine(x, y, slingX, slingY, 10) == true)
        {
          step = GAME_WAIT;
          controlled->life->status &= ~Life::s_getReady; ///׼������,��Ҫ�����ʾλ
        }
        else  ///�ƶ���λ
        {
          controlled->life->body->SetTransform(b2Vec2(P2M(x),P2M(y)),0);
        }
      }
      else ///û������
      {
        step = GAME_OVER;
      }
      break;
    case GAME_WAIT:
      if (controlled == 0)
      {
        step = GAME_GETBIRD;
        break;
      }
      break;
    case GAME_SCROLL:
    case GAME_PAUSE:
    case GAME_RUNING: ///������
    case GAME_OVER:  ///��ɼ�,��ʾ�ɼ���
    case GAME_END: ///�л����¸�ҳ��
      break;
  }
  deleteObj(); ///ɾ��С������Ƶ�����
  return;
}

bool GamePage::getBird()
{
    if (controlled == 0)
    {
      for(int i=0; i<10; ++i) ///ȡ���õ�С��
      {
        if(controllable[i] != 0 && controllable[i]->life !=0)
        {
          controlled = controllable[i];
          return true;
        }
      }
    }
    else
      return true;
    return false;
}
void GamePage::deleteObj()
{
  if (controlled && ((!controlled->life->body->IsAwake()))) ///�����е�С���Ѿ�ֹ
  {
    if(controlled->life->status & controlled->life->s_crash) ///��ײ�꾲ֹ��
      controlled->life->status = controlled->life->s_clound; ///������ʧ
    else
    {
      world->DestroyBody(controlled->life->body);
      controlled->life->body = 0;
      SafeDelete(controlled->life);
      controlled = 0;
      step = GAME_GETBIRD;
    }
  }
  for (int i=0; i<ARRMAX; ++i)
  {
    if(del[i])
    {
       world->DestroyBody(del[i]);
       del[i] = 0;
    }
  }
}

void GamePage::DrawData()
{
  for (b2Body *cBody = world->GetBodyList(); cBody; cBody = cBody->GetNext()) 
  {
    if(TObjectData* obj = (TObjectData*)cBody->GetUserData() )
     {
        if(obj->life != 0)
          obj->life->Draw(obj);
        if (controlled != 0)
        {
          if (!(controlled->life->status & Life::s_getReady) && !(controlled->life->status & Life::s_flying))
            drawSlingLine(M2P(controlled->life->body->GetPosition().x), M2P(controlled->life->body->GetPosition().y));
        }
     }
  }
  PlayAnimation();
}

bool GamePage::OnPointerPressed(int x, int y)
{
    BOOL bRet = FALSE;
    controlled = 0;
    MENU.OnPointerPressed(x, y);
    switch (step)
    {
    case GAME_WAIT:
    {
      ///����Ƿ��ڿؼ���Χ
      int i = 0;
      while (controllable[i]!=0)
      { 
        Rec rc;
        rc.height = controllable[i]->life->height;
        rc.width = controllable[i]->life->width;
        rc.x = controllable[i]->life->x - rc.width/2;
        rc.y = controllable[i]->life->y - rc.height/2;
        if (InButtonPic(x, y, 0, SHIFT, rc) == 1 && (controllable[i]->life->status & Life::s_pickAble) == true)
        {
            controlled = controllable[i];
            controlled->life->status &= ~Life::s_jumpAble;
            idxControl = i;
            break;
        }
        ++i;
      }
      if (controlled == 0)
        lastY = y;
      break;
    }
    case GAME_SCROLL:
    case GAME_RUNING:
      lastY = y;
    default:
      break;
    }

    return bRet;
}
bool GamePage::OnPointerDragged(int x, int y)
{
    BOOL bRet = FALSE;
    switch(step)
    {
    case GAME_WAIT:
      {
        if (controlled!=0)
        {
          Rec rc;
          rc.height = controlled->life->height;
          rc.width = controlled->life->width;
          rc.x = controlled->life->x - rc.width/2;
          rc.y = controlled->life->y - rc.height/2;
          if (InButtonPic(x, y, 0, SHIFT, rc) == 1 && (controlled->life->status & Life::s_pickAble) == true)
          {
            b2Vec2 ps;
            ps.x = P2M(x);
            ps.y = P2M(y);
            controlled->life->body->SetTransform(ps, 0);
          }
        }
        else
        {
          /*
          if (lastY != 0 && lastY != y)
          {
            step = GAME_SCROLL;
            if (lastY > y) //����
              scroll_flag = SCROLL_UP;
            else
              scroll_flag = SCROLL_DOWN;
          }*/
        }  
        break;
      
      }
    case GAME_SCROLL:
    case GAME_RUNING:
      {
        /*
        if (lastY != 0 && lastY != y)
        {
          if (lastY > y) //����
            scroll_flag = SCROLL_UP;
          else
            scroll_flag = SCROLL_DOWN;
        }
        */
        break;
      }
    }
    return bRet;
}

/**@brief ��갴���ͷ�
 */
bool GamePage::OnPointerReleased(int x, int y)
{
    BOOL bRet = FALSE;
    MENU.OnPointerReleased(x, y);
    lastY = 0;
    switch (step)
    {
    case GAME_WAIT:
      {
        if (controlled != 0)
        {
          Rec rc;
          rc.height = controlled->life->height;
          rc.width = controlled->life->width;
          rc.x = controlled->life->x - rc.width/2;
          rc.y = controlled->life->y - rc.height/2;
          if (InButtonPic(x, y, 0, SHIFT, rc) == 1 && (controlled->life->status & Life::s_pickAble) == true)
          {
            controlled->life->body->GetFixtureList()->SetRestitution(BIRD_RESTITION);
            controlled->life->body->SetActive(true);
            //b2Vec2 rc;
            //rc.x = x;
            //rc.y = y;
            //controlled->life->body->SetTransform(rc, 0);

            float32 distanceX = (float32)x - slingX;
            float32 distanceY = (float32)y - slingY;
            float32 distance = b2Sqrt((float32)distanceY*(float32)distanceY +
                                      (float32)distanceX*(float32)distanceX);
            float32 birdAngle = b2Atan2((float32)distanceY, (float32)distanceX);
            b2Vec2 birdStrlen = b2Vec2(-distance * cos(birdAngle)/4.0f, 
                                       -distance * sin(birdAngle)/4.0f);
            controlled->life->body->SetLinearVelocity(birdStrlen);

            controlled->life->status &= ~controlled->life->s_pickAble & ~controlled->life->s_jumpAble;
            controlled->life->status |= controlled->life->s_flying;
            //controlled = 0;
            step = GAME_RUNING;
          }
        }
        break;
      }
    }

    return bRet;
}

void GamePage::getScreenMove()
{
  switch(step)
  {
    case GAME_SCROLL:
    {
      if (scroll_flag == SCROLL_UP)
        SCREEN_SHIFT_Y = SCREEN_SHIFT_Y - CONF.MOVE_SPEED;
      else 
        SCREEN_SHIFT_Y = SCREEN_SHIFT_Y + CONF.MOVE_SPEED;
      if (SCREEN_SHIFT_Y <= -CONF.Y)
        SCREEN_SHIFT_Y = -CONF.Y;
      if (SCREEN_SHIFT_Y > 0)
      {
        SCREEN_SHIFT_Y = 0;
        if (step == GAME_SCROLL)
          step = GAME_WAIT;
      }
      break;
    }
    case GAME_RUNING:
    {


    }
  }

}

/**
 * @ȡ���ϵ�����·�ߵ�
 * @param inv ����
 * @return true:���  false:��δ��Ŀ�ĵ�
 */
bool GamePage::JumpLine(int &x, int &y, const int tx, const int ty, const int inv)
{
    if (x == tx && y == ty)  ///���ǵ�onPaint�Ǻ����,�˴��ڻ�����һ��������,���ӳ��ж�ʱ��
       return true;
    if (x !=tx )
      ((x+=inv)>=tx)?x=tx : x;
    if (y !=ty )
      ((y+=inv)>=ty)?y=ty : y;
    
    return false;
}

/**
 * @brief ����Ҫɾ��������,����һ��stepǰ������������ɾ��
 */
bool GamePage::push_del(b2Body* obj)
{
  return add_obj(del,obj);
}

/**
 * @brief ���붯��
 */
bool GamePage::push_ani(Animation* aniobj)
{
  return add_obj(ani, aniobj);
}
/**
 * @brief ���Ŷ���
 * @return true:ȫ�������� false:���к���Ҫ����
 */
bool GamePage::PlayAnimation()
{
  bool ret = true;
  for (int i=0; i<ARRMAX; ++i)
  {
    if(ani[i]!=0)
    {
      if (true == ani[i]->play()) ///����true ��ʾ�������
      {
        SafeDelete(ani[i]);
      }
      else 
        ret = false;
    }
  }
  return ret;
}

/** @brief ������ʵ��,�л�ͼƬ
 */
/*
bool Animation::play()
{
  int step = dt % (pic_count + delay);
  if (step < delay)
    return false;

  JImage* tmp = GETIMG(play_list[step-delay]);
  gpDC->drawImage(tmp, x, y + GamePage::SCREEN_SHIFT_Y, 20, AEE_RO_MIRROR);
  if (step >= pic_count + delay - 1)
    return true; ///ȫ���������

  return false;
}
*/

bool Animation::play()
{
  if (delay > 0)
  {
    --delay;
    return false;
  }
  int step = dt % (pic_count * interval);

  JImage* tmp = GETIMG(play_list[step/interval]);
  gpDC->drawImage(tmp, x, y + GamePage::SCREEN_SHIFT_Y, 20, AEE_RO_MIRROR);
  if (step >= pic_count * interval - 1)
    return true; ///ȫ���������

  return false;
}

Animation::Animation(int &hb, int dl, int inv)
   :dt(hb),delay(dl),interval(inv)
{
}

Animation::~Animation()
{
  //DELETEV(play_list, pic_count);
  //*
  delete []play_list;
  play_list = 0;
  //*/
}
//} /* namespace NBird */
/** ͼƬ�������,��͸��
enum {
	AEE_RO_MIRROR=0x10,
	AEE_RO_ROTATE90=0x20,
	AEE_RO_ROTATE180=0x40,
	AEE_RO_ROTATE270=0x80
};

��ʾ����
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

*/