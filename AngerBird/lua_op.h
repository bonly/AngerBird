/**
 *  @file lua_op.h
 *
 *  @date 2012-2-28
 *  @Author: Bonly
 */

#ifndef LUA_OP_
#define LUA_OP_
#include "lua/lua.h"
#include <string>
#include <vector>
using namespace std;
struct KEY_VALUE
{
	string m_strKey;
	string m_strValue;
};

class CLuaOper
{
public:
	CLuaOper();
	~CLuaOper();

public:
	bool load(const char* pszPath, const char* pszFile);
	
	//pszFunc: lua脚本中函数
	//pszParam: 格式如下<k1=v1><k2=v2>
	int call_to_h2(const char* pszFunc,const vector<KEY_VALUE>& vec,string& strBody);
	int call_to_ctrl(const char* pszFunc,const char* pszBody,CRequestFlowObj *pObj);
	int call_to_func(const char* pszFunc,const vector<KEY_VALUE>& vec,CCallFuncObj &CallFuncObj);
	bool CheckAuthen(const string& strID,const string& strIp,const string& strCmd,const string& strMsisdn);
private:
	lua_State* m_L;
};

#endif /* PRE_H_ */
