/**
 *  @file Configure.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
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

  public:
    b2Vec2 gravity; ///����
    enum {PTM=50}; ///���ű���   
	  int X; ///��Ļ�ֱ���X
    int Y; ///��Ļ�ֱ���Y
    int MOVE_SPEED; ///�ƶ���ͷ�ٶ�


  public:
    static Configure *conf;

};

#define CONF Configure::instance()

//} /* namespace NBird */
#endif /* CONFIGURE_H_ */
