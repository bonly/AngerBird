/**
 *  @file LeftMenu.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "PreLoad.h"
#include "../ResPool.h"
#include "../Configure.h"
#include "LeftMenu.h"
//namespace NBird {
Page* LeftMenu::menu = 0;
Page& LeftMenu::instance()
{
  if(0 == menu)
  {
    menu = new LeftMenu;
    menu->init();
  }
  return *menu;
}

void LeftMenu::destory()
{
  SafeDelete(menu);
}

LeftMenu::LeftMenu()
{
}

int LeftMenu::init()
{
  CHKIMG(pause1);
  CHKIMG(pause2);
  status = HIDE;
  btnPause.x = 250;
  btnPause.y = 30;
  btnPause.height = ((JImage*)V_pause1->attr)->getHeight();
  btnPause.width = ((JImage*)V_pause1->attr)->getWidth();
  btnPause.attr = (JImage*)V_pause1->attr;
  return 0;
}

LeftMenu::~LeftMenu()
{
  //SafeDelete( );
}

void LeftMenu::onPaint()
{
  gpDC->drawImage(btnPause.attr, btnPause.x, btnPause.y, 20);
}

bool LeftMenu::OnPointerPressed(int x, int y)
{
  switch(status)
  {
  case HIDE:
    {
      if (InButtonPic(x, y, 0, GamePage::SCREEN_SHIFT_Y, btnPause) == 1)
      {
        btnPause.attr = GETIMG(ID_pause2);
      }
      break;
    }

  }
  return true;
}

bool LeftMenu::OnPointerReleased(int x, int y)
{
  switch(status)
  {
  case HIDE:
    {
      if (InButtonPic(x, y, 0, GamePage::SCREEN_SHIFT_Y, btnPause) == 1)
      {
        btnPause.attr = GETIMG(ID_pause1);
      }
      break;
    }
  }
  return true;
}
//} /* namespace NBird */
