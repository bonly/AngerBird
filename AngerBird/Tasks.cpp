/**
 *  @file Tasks.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "Tasks.h"
#include "Pages/MainEntryPage.h"
#include "Pages/MainStagePage.h"
#include "Pages/MainGuanPage.h"
#include "Pages/Session1.h"
//#include "pages/LeftMenu.h"
//namespace NBird {
Tasks *task = 0;

PageEntry Tasks::list[] =
{
	{ 0, MainEntryPage::create},
	{ 0, MainStagePage::create},
	{ 0, MainGuanPage::create},
  { 0, Session1::create},
  { 0, 0 }
};

Tasks::Tasks():page_count(0),current_page(0),next_page(-1),step(CURRENT_PAGE)
{
  while (list[page_count].creatFcn != 0)
  {
    ++page_count;
  }
}

Tasks::~Tasks()
{
  for(int i=0; i<page_count; ++i)
  {
    if(list[i].page != 0)
      SafeDelete(list[i].page);
  }
}

int Tasks::get_current_page()
{
  return current_page;
}

int Tasks::get_next_page()
{
  return next_page;
}
//} /* namespace NBird */
