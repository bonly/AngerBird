#include "BuildBlock.h"
#include "Configure.h"
#include "Life/Life.h"
#include "Life/Wood.h"
#include "Life/RedBird.h"
#include "Life/Pig.h"
#include "Life/Stone.h"
#include "Life/Ice.h"


/**
 * @note nFloorList[][21]
 * 1:  使用的图片ID
 * 2:  X
 * 3:  Y
 * 4:  多边形边数
*/

/**
 * @note nBlockList[][8]
 * 0: 1增加 0删除
 * 1: 所删除物件的记号num
 * 2: 模拟等待步数
 * 3: objectfixture
 * 4: objectShapeType
 * 5: x
 * 6: y
 * 7: 角度
 */

int pageGravityFlag=1;  //当前页重力开关,默认打开

void initBlock(b2World *world, int nFloorNum, int nFloorList[][21],
               int& nBlockNum, int nBlockList[][8],TObjectData* objectDataList,int& objectNum,
               TObjectData** controllable, GamePage* page, int screenMovey)
{
	int i = 0, j = 0;

	////////初始化地面
	for (i=0; i<nFloorNum; i++)
	{
		TObject myObject;
		//左边(右边)，图片ID，中心点X，中心点Y，　共几边, x1,y1......
		int shiftnum=0;
    myObject.life = 0;
		myObject.objectfixture=FIXTURE_FLOOR;
		myObject.objectShapeType=SHAPE_FLOOR_POLY;
		myObject.shapeType=SHAPE_POLY;
		myObject.polyLines=nFloorList[i][4]; ///多边形的边数
		myObject.x=getWorldNum(nFloorList[i][2]+FLOOR_LEVEL_X); ///X位置
		myObject.y=getWorldNum(nFloorList[i][3]+screenMovey); ///Y位置
		myObject.angle=0;
		myObject.no = -1;
		myObject.dynamicFlag=0;
		myObject.imgFlag=nFloorList[i][1];  ///所使用的图片ID
		myObject.density=FLOOR_DENSITY;
		myObject.friction=FLOOR_FRICTION;
		myObject.restitution=FLOOR_RESTITION;
		
		myObject.polyLines= nFloorList[i][4];
		//
		for (j=0; j< 16; j++)
				myObject.data[j] = getWorldNum(nFloorList[i][5+j]);			
		//
		addObject(world, &myObject, objectDataList,objectNum,controllable);
	}
	//
	////////初始化其它物体
	for (i=0; i< nBlockNum; i++)
	{
		TObject myObject;	
    myObject.life = 0;
    myObject.no = nBlockList[i][1]; ///位1:记录号
		float data[5];
		//
    if (nBlockList[i][0] == 1)  ///位0:增加操作
		{
			int m;
			for (m=0; m < 5; m++)
				data[m]=nBlockList[i][m+3]; ///取位3开始的5位数据
			analyseBlock(&myObject, data, page, screenMovey); ///分析构建定义
			addObject(world, &myObject, objectDataList,objectNum,controllable); ///加入物体到物理世界
    }else  if (nBlockList[i][0] == 0)  ///位0:删除操作,删除掉那个物体
		{
			for (b2Body *currentBody=world->GetBodyList(); currentBody; currentBody=currentBody->GetNext()) 
			{
				if(currentBody->GetUserData()) 
				{
					 TObjectData *curr = (TObjectData *) currentBody->GetUserData();
					 if (curr->no == nBlockList[i][1]) ///删除与用户数据中匹配记号的物件
					 {
						 world->DestroyBody(currentBody);
						 break;
					 }
				}
			}
							
		}else  if (nBlockList[i][0] == 2)   // add gra
			pageGravityFlag=1;
		else
			pageGravityFlag=0;
		///模拟工具搭建时的操作
		if (pageGravityFlag == 1)
		{
			int n;
			float32 timeStep = 1.0f /20.0f; 
			int num=nBlockList[i][2]; ///模拟等待步数
		
			for (n=0; n < num; n++)
			{
				world->Step(timeStep, 10,10);
			}
		}
	}
}

void analyseBlock(TObject *myObject,  float block[5], GamePage* page, int screenMovey)
{
		myObject->objectfixture=block[0];  ///类型
		myObject->objectShapeType=block[1]; ///型状
		myObject->x=getWorldNum(block[2] + FLOOR_LEVEL_X);		///x
		//      //不是鸟要偏移
			myObject->y=getWorldNum(block[3]+screenMovey);  ///
		//
		myObject->angle=block[4];   ///角度
		myObject->dynamicFlag=1;
		//
		switch(myObject->objectfixture)
		{
		case FIXTURE_BIRD:
			myObject->density=BIRD_DENSITY;
			myObject->friction=BIRD_FRICTION;
			myObject->restitution=BIRD_RESTITION;
			break;
		case FIXTURE_WOOD:
			myObject->density=WOOD_DENSITY;
			myObject->friction=WOOD_FRICTION;
			myObject->restitution=WOOD_RESTITION;
      myObject->life = SafeNew Wood;
      myObject->life->setSessionPage(page);
			break;
		case FIXTURE_ICE:
			myObject->density=ICE_DENSITY;
			myObject->friction=ICE_FRICTION;
			myObject->restitution=ICE_RESTITION;
      myObject->life = SafeNew Ice;
      myObject->life->setSessionPage(page);
			break;
		case FIXTURE_STONE:
			myObject->density=STONE_DENSITY;
			myObject->friction=STONE_FRICTION;
			myObject->restitution=STONE_RESTITION;
      myObject->life = SafeNew Stone;
      myObject->life->setSessionPage(page);
			break;
		case FIXTURE_PIG:
			myObject->density=PIG_DENSITY;
			myObject->friction=PIG_FRICTION;
			myObject->restitution=PIG_RESTITION;
      myObject->life = SafeNew Pig;
      myObject->life->setSessionPage(page);
			break;
		}
		/////////////////////矩形
		if (block[1] <= SHAPE_S_RECT || block[1] == SHAPE_B_TIP)
		{
			int type=block[1];
				switch(type)
				{
				case SHAPE_B_TIP:
					myObject->data[0]=getWorldNum(B_TIP_WIDTH/2.0f);
					myObject->data[1]=getWorldNum(B_TIP_HEIGHT/2);
					break;
				case SHAPE_L_TIP:
					myObject->data[0]=getWorldNum(L_TIP_WIDTH/2.0f);
					myObject->data[1]=getWorldNum(L_TIP_HEIGHT/2);
					break;
				 case SHAPE_M_TIP:
					myObject->data[0]=getWorldNum(M_TIP_WIDTH/2.0f);
					myObject->data[1]=getWorldNum(M_TIP_HEIGHT/2);
					break;
				 case SHAPE_S_TIP:
					myObject->data[0]=getWorldNum(S_TIP_WIDTH/2.0f);
					myObject->data[1]=getWorldNum(S_TIP_HEIGHT/2);
					break;
				 case SHAPE_L_SQU:
					myObject->data[0]=getWorldNum(L_SQU_WIDTH/2.0f);
					myObject->data[1]=getWorldNum(L_SQU_WIDTH/2.0f);
					break;
				 case SHAPE_M_SQU:
					myObject->data[0]=getWorldNum(M_SQU_WIDTH/2.0f);
					myObject->data[1]=getWorldNum(M_SQU_WIDTH/2.0f);
					break;
				case SHAPE_S_SQU:
					myObject->data[0]=getWorldNum(S_SQU_WIDTH/2.0f);
					myObject->data[1]=getWorldNum(S_SQU_WIDTH/2.0f);
					break;
			  case SHAPE_S_RECT:
					myObject->data[0]=getWorldNum(S_RECT_WIDTH/2.0f);
					myObject->data[1]=getWorldNum(S_RECT_HEIGHT/2);
					break;						 
			}
			myObject->shapeType=SHAPE_RECT;
		}
		/////////////////////圆形
		else if ( (block[1] >=SHAPE_L_CIR &&  block[1] <=SHAPE_S_PIG)
			|| (block[1] >=SHAPE_RED_BIRD &&  block[1] <=SHAPE_EGG_BIRD))
		{
			myObject->shapeType=SHAPE_CIRCLE;
			switch(myObject->objectShapeType)
			{
			case SHAPE_L_CIR:
				myObject->data[0]=getWorldNum(L_CIR_RADIUS);
				break;
			case SHAPE_S_CIR:
				myObject->data[0]=getWorldNum(S_CIR_RADIUS);
				break;
			case SHAPE_CROWN_PIG:
				myObject->data[0]=getWorldNum(PIG_CROWN_RADIUS);
				break;
			case SHAPE_BEARD_PIG:
				myObject->data[0]=getWorldNum(PIG_BEARD_RADIUS);
				break;
			case SHAPE_CAP_PIG:
				myObject->data[0]=getWorldNum(PIG_CAP_RADIUS);
				break;
			case SHAPE_L_PIG:
				myObject->data[0]=getWorldNum(PIG_L_RADIUS);
				break;
			case SHAPE_M_PIG:
				myObject->data[0]=getWorldNum(PIG_M_RADIUS);
				break;
			case SHAPE_S_PIG:
				myObject->data[0]=getWorldNum(PIG_S_RADIUS);
				break;
			case SHAPE_RED_BIRD:
				myObject->data[0]=getWorldNum(BIRD_RED_RADIUS);
        myObject->life = SafeNew RedBird;
        myObject->life->setSessionPage(page);
				break;
			case SHAPE_THREE_BIRD:
				myObject->data[0]=getWorldNum(BIRD_THREE_RADIUS);
				break;
			case SHAPE_BOMB_BIRD:
				myObject->data[0]=getWorldNum(BIRD_BOMB_RADIUS);
				break;
			case SHAPE_EGG_BIRD:
				myObject->data[0]=getWorldNum(BIRD_EGG_RADIUS);
				break;

			}
		}
		else  //其它三角形
		{
			myObject->shapeType=SHAPE_POLY;
			myObject->polyLines=3;
			if (myObject->objectShapeType== SHAPE_Z_TRIANGLE)
			{
				myObject->data[0]=getWorldNum(Z_TRI_X1);
				myObject->data[1]=getWorldNum(Z_TRI_Y1);
				myObject->data[2]=getWorldNum(Z_TRI_X2);
				myObject->data[3]=getWorldNum(Z_TRI_Y2);
				myObject->data[4]=getWorldNum(Z_TRI_X3);
				myObject->data[5]=getWorldNum(Z_TRI_Y3);
			}else if (myObject->objectShapeType== SHAPE_C_TRIANGLE)
			{
				myObject->data[0]=getWorldNum(C_TRI_X1);
				myObject->data[1]=getWorldNum(C_TRI_Y1);
				myObject->data[2]=getWorldNum(C_TRI_X2);
				myObject->data[3]=getWorldNum(C_TRI_Y2);
				myObject->data[4]=getWorldNum(C_TRI_X3);
				myObject->data[5]=getWorldNum(C_TRI_Y3);
			}else if (myObject->objectShapeType== SHAPE_SPEED_BIRD)
			{
				myObject->data[0]=getWorldNum(BIRD_TRI_X1);
				myObject->data[1]=getWorldNum(BIRD_TRI_Y1);
				myObject->data[2]=getWorldNum(BIRD_TRI_X2);
				myObject->data[3]=getWorldNum(BIRD_TRI_Y2);
				myObject->data[4]=getWorldNum(BIRD_TRI_X3);
				myObject->data[5]=getWorldNum(BIRD_TRI_Y3);
			}
		}
}
///////////////////////////////////////////////////
void addObject(b2World *world, TObject *object,TObjectData* objectDataList,int& objectNum,TObjectData** controllable)
{
	int i=0;
  static int ctrl_num = 0;
  
	b2PolygonShape polygonShape;
	b2CircleShape circleShape;
	//
	b2FixtureDef myfixture;
	myfixture.density=object->density;
	myfixture.friction=object->friction;
	myfixture.restitution=object->restitution;  
	//
	objectDataList[objectNum].shapeType=object->objectShapeType;
	objectDataList[objectNum].fixture=object->objectfixture;
	objectDataList[objectNum].floorImgPos=object->imgFlag;
	objectDataList[objectNum].life = object->life;
  objectDataList[objectNum].PH=calObjectPH(object->objectShapeType, object->objectfixture);  ///PH值这里根据具体的物体属性
  if (object->life!=0)
    objectDataList[objectNum].life->PH = objectDataList[objectNum].PH; ///同步所生成物体的血量
	/////////
	
	/////////////////////////////////////////////////////////////////////////////
	b2BodyDef bodyDef ;
	if (object->dynamicFlag==1)
		bodyDef.type=b2_dynamicBody;
	bodyDef.position.Set(object->x, object->y);   //设置位置
	bodyDef.angle=getAngle(object->angle);
	bodyDef.bullet=true;
	//
	bodyDef.userData = &objectDataList[objectNum];
  myfixture.userData = &objectDataList[objectNum];

  if (object->objectfixture == FIXTURE_BIRD)  ///对鸟类设置相关状态
  {
    bodyDef.active = false;
    controllable[ctrl_num] = &objectDataList[objectNum];
    if (ctrl_num == 0) ///第一只鸟可抓取,会眨眼
    {
      controllable[0]->life->status |= Life::s_pickAble 
                                    |  Life::s_eyes;
    }
    else ///其它鸟不可抓取,但会眨眼
    {
      controllable[ctrl_num]->life->status &= ~Life::s_pickAble &  ~Life::s_clound;
      controllable[ctrl_num]->life->status |= Life::s_eyes | Life::s_jumpAble;
    }
    ++ctrl_num; ///可控鸟计数器自加1
  }

	//

	if (object->shapeType == SHAPE_RECT)
	{
		polygonShape.SetAsBox(object->data[0],object->data[1]);
		myfixture.shape=&polygonShape;
	}else if(object->shapeType== SHAPE_CIRCLE)
	{
		circleShape.m_radius =object->data[0];
		myfixture.shape=&circleShape;
	}else
	{

    b2Vec2 *mm;
    int num=0; 
    mm= (b2Vec2 *) SafeMalloc(object->polyLines * sizeof(struct b2Vec2));
    for (i=0; i<object->polyLines; i++)
    {
	    mm[i].Set(object->data[num], object->data[num+1]);
	    num = num + 2;
    }
    polygonShape.Set(mm, object->polyLines);
    myfixture.shape=&polygonShape;
    SafeDelete(mm);

	}

	//
	b2Body *B2Object=world->CreateBody(&bodyDef);   //在body里组装很多形状  都是通过b2Body.CreateFixture(b2FixtureDef)来确定
	B2Object->CreateFixture(&myfixture);
  if(objectDataList[objectNum].life != 0)
    objectDataList[objectNum].life->body = B2Object;
	++objectNum;
}

//根据物体的大小形状得到PH值
float32 calObjectPH(int objectShapeType, int fixture)
{
	float result;
	switch(fixture)
	{
	case FIXTURE_FLOOR:
		result=0;
		break;
	case FIXTURE_WOOD:
		switch(objectShapeType)
		{
		case SHAPE_B_TIP:
			result=WOOD_B_TIP_PH;
			break;
		case SHAPE_L_TIP:
			result=WOOD_L_TIP_PH;
			break;
		case SHAPE_M_TIP:
			result=WOOD_M_TIP_PH;
			break;
		case SHAPE_S_TIP:
			result=WOOD_S_TIP_PH;
			break;
		case SHAPE_M_SQU:
			result=WOOD_M_SQU_PH;
			break;
		case SHAPE_S_SQU:
			result=WOOD_S_SQU_PH;
			break;
		case SHAPE_S_RECT:
			result=WOOD_S_RECT_PH;
			break;
		}
		break;
	case FIXTURE_ICE:
		switch(objectShapeType)
		{
		case SHAPE_B_TIP:
			result=ICE_B_TIP_PH;
			break;
		case SHAPE_L_TIP:
			result=ICE_L_TIP_PH;
			break;
		case SHAPE_M_TIP:
			result=ICE_M_TIP_PH;
			break;
		case SHAPE_S_TIP:
			result=ICE_S_TIP_PH;
			break;
		case SHAPE_M_SQU:
			result=ICE_M_SQU_PH;
			break;
		case SHAPE_S_SQU:
			result=ICE_S_SQU_PH;
			break;
		case SHAPE_S_RECT:
			result=ICE_S_RECT_PH;
			break;
		}
		break;
	case FIXTURE_STONE:
		switch(objectShapeType)
		{
		case SHAPE_B_TIP:
			result=STONE_B_TIP_PH;
			break;
		case SHAPE_L_TIP:
			result=STONE_L_TIP_PH;
			break;
		case SHAPE_M_TIP:
			result=STONE_M_TIP_PH;
			break;
		case SHAPE_S_TIP:
			result=STONE_S_TIP_PH;
			break;
		case SHAPE_M_SQU:
			result=STONE_M_SQU_PH;
			break;
		case SHAPE_S_SQU:
			result=STONE_S_SQU_PH;
			break;
		case SHAPE_S_RECT:
			result=STONE_S_RECT_PH;
			break;
		}
		break;
	case FIXTURE_PIG:
		switch(objectShapeType)
		{
		case SHAPE_CROWN_PIG:
			result=PIG_CROWN_PH;
			break;
		case SHAPE_BEARD_PIG:
			result=PIG_BEARD_PH;
			break;
		case SHAPE_CAP_PIG:
			result=PIG_CAP_PH;
			break;
		case SHAPE_L_PIG:
			result=PIG_L_PH;
			break;
		case SHAPE_M_PIG:
			result=PIG_M_PH;
			break;
		case SHAPE_S_PIG:
			result=PIG_S_PH;
			break;		
		}
		break;
	}
	return result;
}
float32 getAngle(float32 angle)
{
	return (angle/((180.f / b2_pi)));
}

void  addWall(b2World* world,int w, int h, int px, int py)
{
  float32 w1 = P2M(w);
  float32 h1 = P2M(h);
	  //
  b2PolygonShape floorShape;
  floorShape.SetAsBox(w1, h1);
  	

  b2FixtureDef floorFixture;
  floorFixture.density=0;
  floorFixture.friction=10;
  floorFixture.restitution=0.f;   //弹性
  floorFixture.shape=&floorShape;

  //
  b2BodyDef floorBodyDef ;
  float32 x1=P2M(px);
  float32 y1=P2M(py);

  floorBodyDef.position.Set(x1, y1);
  floorBodyDef.bullet=true;
  //floorBodyDef.userData=&floorData;
  //
  b2Body *floor=world->CreateBody(&floorBodyDef);

  floor->CreateFixture(&floorFixture);

}


