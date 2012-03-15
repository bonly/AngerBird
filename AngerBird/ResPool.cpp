/**
 *  @file ResPool.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "ResPool.h"


//namespace NBird {
//Image_createImage(gpDC,#F); 
/*
#define RESSEG
#define RES(O) OBJ<Obj,void*>* V_##O=0;
#include "Resource.inc"
#undef RES

#define RES(O) (Obj*)V_##O,
Obj*  List[]={
#include "Resource.inc"
};
#undef RES
#undef RESSEG
*/

#define IMGSEG
#define RES(O,F) OBJ<Obj,void*> V_##O;
#include "Resource.inc"
#undef RES

#define RES(O,F) (OBJ<Obj,void*>*)&V_##O,
OBJ<Obj,void*>*  List[]={
#include "Resource.inc"
};
#undef RES

#define RES(X,F) \
 void load_##X(void*) { \
 if(V_##X.attr==0) \
   V_##X.attr =  SafeNew JImage(#F, TRUE); \
}
#include "Resource.inc"
#undef RES

#undef IMGSEG

void DELIMG(int idx)
{
  if (idx >= RES_MAX || idx < 0) return;
  SafeDelete(List[idx]->attr);
}

ResPool* ResPool::resp = 0;
ResPool::ResPool()
{
  fixRelation();
}

ResPool::~ResPool()
{
}

void ResPool::destory()
{
  if(resp)
  {
    for (int i=0; i<RES_MAX; ++i)
    {
       SafeDelete(List[i]->attr);
    }
    SafeDelete(resp);  
  }
}

void ResPool::fixRelation()
{
  int i = 0;
#define IMGSEG
#define RES(X,F) \
  List[i]->ID = i; \
  List[i]->create = load_##X; \
  ++i;
#include "Resource.inc"
#undef RES
#undef IMGSEG
}

ResPool& ResPool::instance()
{
  if(0 == resp)
  {
    resp = new ResPool;

  }
  return *resp;
}

JImage* GETIMG(int idx)
{
  if(idx > RES_MAX || idx < 0) return 0;
  OBJ<Obj,void*>* obj = RESP.getObj<OBJ<Obj,void*> >(idx);
  if(obj->attr == 0)
  {
     List[idx]->create(0);
  }
  JImage* res = (JImage*)List[idx]->attr;
  if (res==0)
    throw "no ";
  return res;
}


//} /* namespace NBird */
