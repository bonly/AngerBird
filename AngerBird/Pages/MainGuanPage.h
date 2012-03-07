#ifndef _MAIN_GUAN_PAGE
#define _MAIN_GUAN_PAGE

#include "../pre.h"
#include "../Page.h"
#include "../ResPool.h"
#include "../ABDraw.h"

enum _GUAN_STATUS
{
	GUAN_LOADING=0,
	GUAN_WAIT
};

class MainGuanPage : public Page
{
  public:
    MainGuanPage();
	virtual ~MainGuanPage();
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

	void btnReleaseAction(int code);
	void showPicNumber(int number, int x, int y);
	void readFileStr(char *filename, char *buf, int len);
	void writeFileStr(char *filename, char *str, int len);
	void showStar(int x, int y,  int num);
	//
	char stageData[50];
	//
	Image imgBg[2];
	Image imgBtn[2];
	Image imgReturnBig;
	Image imgLock;
	Image imgNumber;
	Image imgStar;
	//
	TButtonArea btn[22];
	int state;
	
};


#endif