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

  int &dt; ///ÿ֡�����Ŀ�����
  int x;
  int y; ///�����ص�
  int *play_list; ///�����ļ��б�
  int pic_count; ///�ļ�����
  int delay; ///�ӳ�ʱ��
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
   // void drawSlingLine(b2Body* bird);
	 void drawSlingLine(int x, int y);
    void DrawData();
    void getScreenMove();
	void drawGameBg();  //������ͼ
	void drawGrass();  //�����
    void deleteObj();
    bool push_del(b2Body* obj);
    bool push_ani(Animation* aniobj);
    bool PlayAnimation();

  public:
    enum {GAME_LOADING =0, GAME_WAIT,GAME_SCROLL,GAME_RUNING,GAME_PAUSE}; ///50��ǰΪ���ز��� wait:�Ȳ��� scroll:���� runing:������ pause:��ͣ
    enum {SCROLL_UP,SCROLL_DOWN};
    int step;
	int slingx;
	int slingy;  //��������
    _Object_Data **controllable;
    _Object_Data *controlled;
    //Page* leftMenu;
    b2World* world;
    b2ContactListener *contact;
    b2ContactFilter *contact_filter;
    int scroll_flag;

    int blockShifty; //��ľƫ��λ��
    float32 slingX;
    float32 slingY;

    int lastY;
    static int SCREEN_SHIFT_Y;
    int SCREEN_SHIFT_X;

    int track[ARRMAX][2];///��¼���й켣
    int track_num;///��Ч��¼����

public:
	TButtonArea btn[2];	
	Image imgSling;
	Image imgRope[3];
	Image imgBg;
	Image imgExtra;
	Image imgGrass;
    Image imgBird[5];

private:
    b2Body* del[ARRMAX]; ///��ɾ���������б�
    Animation* ani[ARRMAX];///�������Ķ����б�

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
