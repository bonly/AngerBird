/**
 *  @file Page.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#ifndef PAGE_H_
#define PAGE_H_
#include "pre.h"

//namespace NBird {
class ResPool;
class b2World;
class JImage;
class Page
{
  public:
    Page();
    virtual ~Page();

  public:
    virtual int init() = 0;
    virtual void onPaint() = 0;
    virtual void onDestory() = 0;
    virtual void running() = 0;
    virtual bool OnPointerDragged(int x, int y)=0;
    virtual bool OnPointerReleased(int x, int y)=0;
    virtual bool OnPointerPressed(int x, int y)=0;
};

struct _Object_Data;

class Animation
{
public:
  Animation(int &hb,int dl=0, int inv=1);
  virtual ~Animation();

  int &dt; ///每帧发生的控制器
  int x;
  int y; ///发生地点
  int *play_list; ///播放文件列表
  int pic_count; ///文件数量
  int delay; ///延迟时间
  int interval;
  virtual bool play();
};

class GamePage : public Page
{
  public:
    enum {ARRMAX=50};
    GamePage();
    virtual ~GamePage();
    virtual int resume();
    virtual int pause();
    virtual int init();
    virtual void onPaint();
    virtual void onDestory();
    virtual void running();
    virtual bool OnPointerDragged(int x, int y);
    virtual bool OnPointerReleased(int x, int y);
    virtual bool OnPointerPressed(int x, int y);
    //void drawSlingLine(b2Body* bird);
	  void drawSlingLine(int x, int y);
    void DrawData();
    void getScreenMove();
	  void drawGameBg();  //画背景图
	  void drawGrass();  //画青草
    void deleteObj();
    bool push_del(b2Body* obj);
    bool push_ani(Animation* aniobj);
    bool PlayAnimation();
    bool JumpLine(int &x, int &y, const int tx, const int ty, const int inv);
    bool getBird();

  public:
    enum {PRELOAD=-10, PRELOADING, PRELOAD_END, 
          GAME_LOADING =0, GAME_WAIT, GAME_GETBIRD, 
          GAME_SCROLL, GAME_RUNING, GAME_PAUSE, GAME_OVER, GAME_END}; 
    ///0以前为加载步聚由session控制,之后的由GamePage控制跳转 wait:等操作 scroll:滚屏 runing:飞行中 pause:暂停
    enum {SCROLL_UP,SCROLL_DOWN};
    int step;
	  int slingx;
	  int slingy;  //弹工坐标
    _Object_Data **controllable;
    _Object_Data *controlled;
    int idxControl; ///所控制鸟在容器中的下标号
    //Page* leftMenu;
    b2World* world;
    b2ContactListener *contact;
    b2ContactFilter *contact_filter;
    int scroll_flag;

    int blockShifty; //积木偏移位置
    float32 slingX;
    float32 slingY; ///弹弓的受力点位置

    int lastY;
    static int SCREEN_SHIFT_Y;
    int SCREEN_SHIFT_X;

    int track[ARRMAX][2];///记录飞行轨迹
    int track_num;///有效记录点数

  public:
	  TButtonArea btn[2];	
	  Image imgSling;
	  Image imgRope[3];
	  Image imgBg;
	  Image imgExtra;
	  Image imgGrass;
    Image imgBird[5];

  public:
    b2Body* del[ARRMAX]; ///需删除的物体列表
    Animation* ani[ARRMAX];///本场景的动画列表

    template<typename T>
    bool add_obj(T** lst, T* obj)
    {
      for (int i=0; i<ARRMAX; ++i)
      {
        if(lst[i] == 0)
        {
           lst[i] = obj;
           return true;
        }
      }
      return false;
    }
    bool add_del_body(b2Body* obj)
    {
      for (int i=0; i<ARRMAX; ++i)
      {
        if(del[i] == 0)
        {
           del[i] = obj;
           return true;
        }
      }
      return false;
    }
    bool add_del_ani(Animation* obj)
    {
      for (int i=0; i<ARRMAX; ++i)
      {
        if(ani[i] == 0)
        {
           ani[i] = obj;
           return true;
        }
      }
      return false;
    }
};

class ControlPage : public Page
{
public:
    ControlPage();
    virtual ~ControlPage();
    virtual int init();
    virtual void onPaint();
    virtual void onDestory();
    virtual void running();
};

//} /* namespace NBird */
#endif /* PAGE_H_ */
