#ifndef __BUILD_BLOCK
#define __BUILD_BLOCK
#include <Box2D/Box2D.h>
#include "osport.h"
#include "jport.h"
#include "objectDef.h"

class Life;
///////////////////////////////////////////////////////////////////
class GamePage;
typedef struct _object
{
	int no;
	int shapeType;  //什么形状
	int objectShapeType;  //细致形状
	int objectfixture;	
	float density;
 	float friction;
	float restitution;
	int dynamicFlag; // 1为运动物体
	int imgFlag;  //地面时的图片ID
	//
	float x;
	float y;  // 中心点坐标
	float angle; //初始角度
	int polyLines;  //多边形条数
	float data[16];  //其它数据   矩形->长宽  圆形->半径  多边形(最多四边，四个角相对坐标, 三角形存储三个角)
    Life *life;
}TObject;

typedef struct _Object_Data
{
	int no;
	int shapeType;//什么形状
	int fixture;  //什么材质   //根据以上二个算出用什么图片
	int floorImgPos; //如果fixture是FIXTURE_FLOOR，则此处有用1,2,3表示引入1.png, 2.png, 3.png
	float PH;     //生命值
	float press;  //当前受到的压力值, 由contactListen赋予
	float angle; //初始角度
	//
	int imgFlag; //地面时的图片ID
	Life *life;
}TObjectData;
//

void addObject(b2World *world, TObject *object,TObjectData* objectDataList,int& objectNum,
               TObjectData** controllable);

void initBlock(b2World *world, int nFloorNum1, int nFloorList[][21],int SCREEN_SHIFT_Y,
               int& nBlockNum, int nBlockList[][8],TObjectData* objectDataList,int& objectNum,
               TObjectData** controllable, GamePage* page, int screenMovey);

float32 calObjectPH(int objectShapeType, int fixture);

float32 getAngle(float32 angle);
void analyseBlock(TObject *myObject,  float block[5], GamePage* page, int screenMovey);
void addWall(b2World* world, int w, int h, int px, int py);
#endif