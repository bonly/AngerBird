/**
 *  @file Session.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */
#ifndef SESSION1_H_
#define SESSION1_H_
#include "../pre.h"
#include "../Page.h"
#include "../ResPool.h"
#include "../BuildBlock.h"
#include "../ABDraw.h"
//namespace NBird{

class Session1 : public GamePage
{
  public:
    Session1(void);
    ~Session1(void);
    virtual int init();
    virtual void running();
    virtual void onPaint();
    virtual void onDestory();
    void preLoad();
    int createWorld();

    static Page* create();

  public:
    enum {PRELOAD=-10,PRELOADING,PRELOAD_END}; 
    //Page* preload;
    ABDraw ab;

  public:
};

//}
#endif
