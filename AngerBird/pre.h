/**
 *  @file pre.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#ifndef PRE_H_
#define PRE_H_
#include <Box2D/Box2D.h>
#include <aeestdlib.h>
#include <jport.h>
enum _PAINT_STATUS
{
	E_PAINT_NORMAL=0,
	E_PAINT_LAYER,
	E_PAINT_REG
};

extern Graphics gpDC;

//namespace NBird {

//判断屏幕触摸是否落入某个控件内
//x, y, 当前触摸点坐标, Xzero,Yzero 虚似坐标(偏移), deviation(偏差范围)
template<typename KEY>
int InButtonPic(int x, int y, int Xzero, int Yzero, KEY btn, int deviation = 0)
{
	if ((x + Xzero) >= (btn.x - deviation) 
    && (x + Xzero) <= (btn.x + btn.width + deviation)  
		&& (y + Yzero) >= (btn.y - deviation) 
    && (y + Yzero) <= (btn.y + btn.height + deviation))
         return 1;
     else
         return 0;

}

template<typename KEY>
int InButtonPic(int x, int y, int Xzero, int Yzero, KEY* btn, int deviation = 0)
{
	if (   (x + Xzero) >= (btn->x - deviation) 
    && (x + Xzero) <= (btn->x + btn->width + deviation)  
		&& (y + Yzero) >= (btn->y - deviation) 
    && (y + Yzero) <= (btn->y + btn->height + deviation))
         return 1;
     else
         return 0;

}


template<typename T> ///没有提供API删除不了数组
void DELETEV(T* p, int num)
{
  for (int i=0; i<num; ++i)
  {
    SafeDelete(p[i]);
  }
}

typedef void(*Tcreate)(void*);
struct Obj
{
    int  ID;
    Tcreate create;
};

typedef struct Rec
{
  int x,y;
  int width,height;
  int press;
  virtual void onClick(){}
}TButtonArea;

template<typename C, typename T>
struct OBJ : public C
{
  T  attr;
  /*
  void operator=(const C& b)
  {
    MEMCPY (this, (const void*)&b, sizeof(b));
    return;
  }
  void operator=(const T& b)
  {
    MEMCPY (this+sizeof(C), (const void*)&b, sizeof(b));
    return;
  }
  */
};

//template<typename T> struct OBJ<Obj,T>;

int getImagePosFromAngle(float angle);
float getWorldNum(int num);
float getPixNum(float num);

#define P2M(X) getWorldNum(X)
#define M2P(X) getPixNum(X)
#define SHIFT  GamePage::SCREEN_SHIFT_Y

float32 sin2oc(float32);
//} /* namespace NBird */
#endif /* PRE_H_ */
