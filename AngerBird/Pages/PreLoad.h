/**
 *  @file PreLoad.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#ifndef PRELOAD_H_
#define PRELOAD_H_
#include "../pre.h"
#include "../page.h"
//namespace NBird {

class PreLoad: public ControlPage
{
  public:
    PreLoad();
    virtual ~PreLoad();
    virtual void onPaint();
    virtual int  init();
    virtual bool OnPointerDragged(int x, int y)
    {return true;}
    virtual bool OnPointerReleased(int x, int y)
    {return true;}
    virtual bool OnPointerPressed(int x, int y)
    {return true;}
    //static Page* create();

};

//} /* namespace NBird */
#endif /* PRELOAD_H_ */
