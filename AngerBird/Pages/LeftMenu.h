/**
 *  @file LeftMenu.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#ifndef LEFT_MENU_
#define LEFT_MENU_
#include "../pre.h"
#include "../page.h"
//namespace NBird {

class LeftMenu: public ControlPage
{
  public:
    enum {HIDE=0,SHOW};
    int status;
    LeftMenu();
    virtual ~LeftMenu();
    virtual void onPaint();
    virtual int  init();
    virtual bool OnPointerDragged(int x, int y)
    {return true;}
    virtual bool OnPointerReleased(int x, int y);
    virtual bool OnPointerPressed(int x, int y);
    static Page& instance();
    static void destory();

    static Page *menu;
    OBJ<Rec,JImage*> btnPause;
};

#define MENU LeftMenu::instance()
//} /* namespace NBird */
#endif /* LEFT_MENU_ */
