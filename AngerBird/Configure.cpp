/**
 *  @file Configure.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 *  @date 2012-3-12 LiXiang 增加飞出边界的处理
 */

#include "Configure.h"

//namespace NBird {

Configure* Configure::conf = 0;
Configure::Configure()
{
  X = gpDC->getWidth();
  Y = gpDC->getHeight();
  MOVE_SPEED = 28;
  nMaxY = 480;
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

void Configure::initBorderline( int y )
{
	if( nMaxY < y )
	{
		nMaxY = y;
	}
}

int Configure::getBorderline( )
{
	return nMaxY;
}

//} /* namespace NBird */
