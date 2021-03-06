/**
 *  @file Configure.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 *  @date 2012-3-12 LiXiang 增加飞出边界的处理
 */

#ifndef CONFIGURE_H_
#define CONFIGURE_H_
#include "pre.h"

//namespace NBird {

class Configure
{
  public:
    Configure();
    virtual ~Configure();
    int init();
    static Configure& instance();
    static void destory();

	void initBorderline( int y );
	int getBorderline();

  public:
    b2Vec2 gravity; ///重力
    enum {PTM=50}; ///缩放比率   
	  int X; ///屏幕分辨率X
    int Y; ///屏幕分辨率Y
    int MOVE_SPEED; ///移动镜头速度
	
	int nMaxY;		//屏幕边界值

  public:
    static Configure *conf;

};

#define CONF Configure::instance()

//} /* namespace NBird */
#endif /* CONFIGURE_H_ */
