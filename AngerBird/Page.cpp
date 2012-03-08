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
 
  slingx += FLOOR_LEVEL_X;  //弹工位置
  //slingx = 120;
  slingy = 100;  //弹工坐标
  return 0;
}


//拼接背景图
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
		///sin转换为角度(四舍五入)
		///计算线的sin
		float32 sina = (float32)cuty/(float32)distance;
		float32 cosa = (float32)cutx/(float32)distance;

		int oc = ceill(sina * (180.f/b2_pi));
		
		if (i == 0 && distance> MAX_ROLE_LEN)
		{
			//重新纠正bird的坐标
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
    gpDC->drawImage(imgSling, slingx, slingy, 20);   //画弹工
    //最后画青草
    drawGrass();
    break;
  }

  DrawData();

  ///画轨迹
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
      slingX = slingx + imgSling->getWidth(); ///设置弹弓的受力点位置
      slingY = slingy + imgSling->getHeight()/2; 

	    //创建世界物体
	    addWall(world, FLOOR_LEVEL_X, 1500, 0,240);
      break;
    case PRELOAD_END: ///预加载期结束
      break;
    case GAME_LOADING:
      step = GAME_GETBIRD;
      break;
    case GAME_GETBIRD:
      if(getBird())
      {
        controlled->life->status &= ~Life::s_jumpAble;///修改状态,不再跳动
        controlled->life->status |= Life::s_getReady; ///修改状态,准备
        int x = M2P(controlled->life->body->GetPosition().x);
        int y = M2P(controlled->life->body->GetPosition().y);
        if(JumpLine(x, y, slingX, slingY, 10) == true)
        {
          step = GAME_WAIT;
          controlled->life->status &= ~Life::s_getReady; ///准备好了,不要这个标示位
        }
        else  ///移动鸟位
        {
          controlled->life->body->SetTransform(b2Vec2(P2M(x),P2M(y)),0);
        }
      }
      else ///没有鸟了
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
    case GAME_RUNING: ///飞行中
    case GAME_OVER:  ///算成绩,显示成绩单
    case GAME_END: ///切换到下个页面
      break;
  }
  deleteObj(); ///删除小鸟或已破的物体
  return;
}

bool GamePage::getBird()
{
    if (controlled == 0)
    {
      for(int i=0; i<10; ++i) ///取可用的小鸟
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
  if (controlled && ((!controlled->life->body->IsAwake()))) ///控制中的小鸟已静止
  {
    if(controlled->life->status & controlled->life->s_crash) ///碰撞完静止了
      controlled->life->status = controlled->life->s_clound; ///变云消失
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
      ///检查是否在控件范围
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
            if (lastY > y) //向上
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
          if (lastY > y) //向上
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

/**@brief 鼠标按键释放
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
 * @取跳上弹弓的路线点
 * @param inv 步长
 * @return true:完成  false:还未到目的地
 */
bool GamePage::JumpLine(int &x, int &y, const int tx, const int ty, const int inv)
{
    if (x == tx && y == ty)  ///考虑到onPaint是后面调,此处在画完上一动作后处理,以延迟判断时机
       return true;
    if (x !=tx )
      ((x+=inv)>=tx)?x=tx : x;
    if (y !=ty )
      ((y+=inv)>=ty)?y=ty : y;
    
    return false;
}

/**
 * @brief 加入要删除的物体,在下一个step前从物理世界中删除
 */
bool GamePage::push_del(b2Body* obj)
{
  return add_obj(del,obj);
}

/**
 * @brief 加入动画
 */
bool GamePage::push_ani(Animation* aniobj)
{
  return add_obj(ani, aniobj);
}
/**
 * @brief 播放动画
 * @return true:全部播放完 false:还有后续要播放
 */
bool GamePage::PlayAnimation()
{
  bool ret = true;
  for (int i=0; i<ARRMAX; ++i)
  {
    if(ani[i]!=0)
    {
      if (true == ani[i]->play()) ///返回true 表示播放完毕
      {
        SafeDelete(ani[i]);
      }
      else 
        ret = false;
    }
  }
  return ret;
}

/** @brief 动画的实现,切换图片
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
    return true; ///全部播放完毕

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
    return true; ///全部播放完毕

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
/** 图片特殊参数,可透明
enum {
	AEE_RO_MIRROR=0x10,
	AEE_RO_ROTATE90=0x20,
	AEE_RO_ROTATE180=0x40,
	AEE_RO_ROTATE270=0x80
};

显示分数
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