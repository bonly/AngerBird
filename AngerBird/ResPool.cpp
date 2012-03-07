/**
 *  @file ResPool.cpp
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#include "ResPool.h"


//namespace NBird {
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
#define RES(O,F) OBJ<Obj,void*>* V_##O=0;
#include "Resource.inc"
#undef RES

#define RES(O,F) (OBJ<Obj,void*>*)V_##O,
OBJ<Obj,void*>*  List[]={
#include "Resource.inc"
};
#undef RES

#define RES(X,F) \
 void load_##X(void*) { \
 V_##X = GETOBJ(ID_##X,T_##X);  \
 if(V_##X->attr!=0) SafeDelete(V_##X->attr); \
 V_##X->attr = Image_createImage(gpDC,#F); \
 V_##X->ID = ID_##X; \
 V_##X->create = load_##X; \
 List[ID_##X] = V_##X; \
}
#include "Resource.inc"
#undef RES

#undef IMGSEG

void DELIMG(int idx)
{
  if (idx >= RES_MAX) return;
  if (List[idx])
    SafeDelete(List[idx]->attr);
  SafeDelete(List[idx]);
}

ResPool* ResPool::resp = 0;
ResPool::ResPool()
{
  
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
      if(List[i])
         SafeDelete(List[i]->attr);
      SafeDelete(List[i]);
    }
    SafeDelete(resp);  
  }
}

void ResPool::fixRelation(int idx)
{
  int i = 0;
#define IMGSEG
#define RES(X,F) {\
  if(i == idx) \
  { \
    List[idx]->ID = idx; \
    List[idx]->create = load_##X; \
  } \
  ++i;}
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
  if(idx > RES_MAX) return 0;
  JImage* res=0;
  if((res = (JImage*)RESP.getObj<OBJ<Obj,void*> >(idx)->attr) == 0)
  {
     List[idx]->create(0);
  }
  res = (JImage*)RESP.getObj<OBJ<Obj,void*> >(idx)->attr;
  return res;
}


//} /* namespace NBird */
