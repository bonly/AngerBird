#ifndef __PRE__
#define __PRE__
#include <aeestdlib.h>

#define _DEBUG 1
#if _DEBUG
enum {LOGLEN = 10*1024};
extern char gpcDebug[LOGLEN];
#define _ { \
	SPRINTF(gpcDebug, "@%s:%s----%s:%d\r\n", __DATE__, __TIME__, __FILE__, __LINE__); \
	OutputDebugData(gpcDebug); \
	}
#define alog(X) { \
	SPRINTF(gpcDebug, "@%s:%s----%s:%d:%s\r\n", __DATE__, __TIME__, __FILE__, __LINE__,X); \
	OutputDebugData(gpcDebug); \
	}
#else
#define _ 
#endif

bool OutputDebugData(const char* pcDbg);



#endif