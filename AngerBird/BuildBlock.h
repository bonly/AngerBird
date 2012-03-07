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
	int shapeType;  //ʲô��״
	int objectShapeType;  //ϸ����״
	int objectfixture;	
	float density;
 	float friction;
	float restitution;
	int dynamicFlag; // 1Ϊ�˶�����
	int imgFlag;  //����ʱ��ͼƬID
	//
	float x;
	float y;  // ���ĵ�����
	float angle; //��ʼ�Ƕ�
	int polyLines;  //���������
	float data[16];  //��������   ����->����  Բ��->�뾶  �����(����ıߣ��ĸ����������, �����δ洢������)
    Life *life;
}TObject;

typedef struct _Object_Data
{
	int no;
	int shapeType;//ʲô��״
	int fixture;  //ʲô����   //�������϶��������ʲôͼƬ
	int floorImgPos; //���fixture��FIXTURE_FLOOR����˴�����1,2,3��ʾ����1.png, 2.png, 3.png
	float PH;     //����ֵ
	float press;  //��ǰ�ܵ���ѹ��ֵ, ��contactListen����
	float angle; //��ʼ�Ƕ�
	//
	int imgFlag; //����ʱ��ͼƬID
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