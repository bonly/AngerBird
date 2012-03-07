#ifndef _MAIN_STATE_PAGE
#define _MAIN_STATE_PAGE

#include "../pre.h"
#include "../Page.h"
#include "../ResPool.h"
#include "../BuildBlock.h"
#include "../ABDraw.h"

enum _MAIN_STATE_STATUS
{
	LOADING=0,
	MAIN_STATE_WAIT	
};

class MainStagePage : public Page
{
  public:
    MainStagePage();
	virtual ~MainStagePage();
    virtual void onPaint();
	virtual int init() ;
    virtual void onDestory();
    virtual void running();
    virtual bool OnPointerDragged(int x, int y);
    virtual bool OnPointerReleased(int x, int y);
    virtual bool OnPointerPressed(int x, int y);
	
	void preLoad();
	void transPageState(int state);
	static Page* create();
	//
	int loadStep;
	Image imgBg;
	Image imgStage[2];
	Image imgReturnBig;
	//
	int state;
	TButtonArea btn[3];
};


#endif