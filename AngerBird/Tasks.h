/**
 *  @file Tasks.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#ifndef TASKS_H_
#define TASKS_H_

//namespace NBird {
class Page;

typedef Page* PageCreateFcn();

struct PageEntry
{
    Page* page;
    PageCreateFcn* creatFcn;
};

class Tasks
{
  public:
    static PageEntry list[];
    Tasks();
    virtual ~Tasks();

  public:
    int get_current_page();
    int get_next_page();

  public:
    int page_count;
    int current_page;
    int next_page;
    enum{CURRENT_PAGE,NEXT_PAGE};
    int step;
};

extern Tasks *task;

//} /* namespace NBird */

#endif /* TASKS_H_ */
