/**
 *  @file Configure.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "Configure.h"

//namespace NBird {

Configure* Configure::conf = 0;
Configure::Configure()
{
  X = gpDC->getWidth();
  Y = gpDC->getHeight();
  MOVE_SPEED = 28;
}

void Configure::destory()
{
  SafeDelete(conf);
}

Configure::~Configure()
{
}

int Configure::init()
{
  return 0;
}

Configure& Configure::instance()
{
  if(0 == conf)
  {
    conf = new Configure;
    conf->init();
  }
  return *conf;
}

//} /* namespace NBird */
