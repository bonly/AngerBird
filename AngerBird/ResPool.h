/**
 *  @file ResPool.h
 *
 *  @date 2012-2-27
 *  @Author: Bonly
 */

#ifndef RESPOOL_H_
#define RESPOOL_H_
#include "pre.h"
//namespace NBird {


class PreLoad;
extern OBJ<Obj,void*>* List[];

class ResPool
{
  public:
    static ResPool* resp;

  public:
    ResPool();
    void fixRelation(int idx);
    virtual ~ResPool();

    template<typename T>
    T* getObj(int ID)
    {
      if (ID > RES_MAX)
        return 0;

      if (List[ID]==0)
      {
        List[ID] = SafeNew(T);
        fixRelation(ID);
      }
      return (List[ID]);
    }

    static ResPool& instance();
    static void destory();
};

#define RESP ResPool::instance()
#define GETOBJ(X,Y) RESP.getObj<Y>(X)

JImage* GETIMG(int idx);
void DELIMG(int idx);


/*
#define RESSEG
enum RES{
  #define RES(O) ID_##O,
  #include "Resource.inc"
  #undef RES
  RES_MAX
};

//#define RES(O) class O;
//#include "Resource.inc"
//#undef RES

#define RES(O) extern OBJ<Obj,void*>* V_##O;
#include "Resource.inc"
#undef RES

#define RES(O) typedef OBJ<Obj,void*>* T_##O;
#include "Resource.inc"
#undef RES

#undef RESSEG
*/

#define IMGSEG
enum RES{
  #define RES(O,F) ID_##O,
  #include "Resource.inc"
  #undef RES
  RES_MAX
};

/*
#define RES(O,F) class O;
#include "Resource.inc"
#undef RES
*/

#define RES(O,F) extern OBJ<Obj,void*>* V_##O;
#include "Resource.inc"
#undef RES

#define RES(O,F) typedef OBJ<Obj,void*> T_##O;
#include "Resource.inc"
#undef RES

#define RES(X,F) \
 void load_##X(void*);
#include "Resource.inc"
#undef RES

#define CHKIMG(X) load_##X(0)

#undef IMGSEG



//} /* namespace NBird */
#endif /* RESPOOL_H_ */
