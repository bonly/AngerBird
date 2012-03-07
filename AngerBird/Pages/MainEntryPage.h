#ifndef _MAIN_ENTRY_PAGE
#define _MAIN_ENTRY_PAGE

#include "../pre.h"
#include "../Page.h"
#include "../ResPool.h"
#include "../BuildBlock.h"
#include "../ABDraw.h"

enum _MAIN_ENTRY_STATE
{
	ENTRY_LOADING =0,
	MAIN_ENTRY_WAITSTART,
	MAIN_ENTRY_QUITTIP
};

class MainEntryPage : public Page
{
  public:
    MainEntryPage();
    virtual ~MainEntryPage();
    virtual void onPaint();
    virtual int init() ;
    virtual void onDestory();
    virtual void running();
    virtual bool OnPointerDragged(int x, int y);
    virtual bool OnPointerReleased(int x, int y);
    virtual bool OnPointerPressed(int x, int y);
	
	  void preLoad();
	  static Page* create();
	  void btnPressAction(int code);
	  void btnReleaseAction(int code);
	  //
	  void btnQuitReleaseAction(int code);
	  //
	  Image imgBg[2];	
	  Image imgSoundoff;
	  Image imgStart;
	  Image imgQuiting;
	  TButtonArea btn[3];	
	  TButtonArea btnQuit[2];	
	  //
	  int state;
};


#endif