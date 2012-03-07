/**
 *  @file lua_op.cpp
 *
 *  @date 2012-2-28
 *  @Author: Bonly
 */

#include "lua_op.h"


CLuaOper::CLuaOper()
{
	m_L = lua_open();
	
	assert(m_L);

	luaL_openlibs(m_L);
}

CLuaOper::~CLuaOper()
{
	lua_close(m_L);
}

bool CLuaOper::load(const char* pszPath, const char* pszFile)
{
	if(pszPath == NULL || pszFile == NULL)
	{
		return false;
	}

	char szTmp[1024];
	memset(szTmp, 0, sizeof(szTmp));
	snprintf(szTmp, sizeof(szTmp),"package.path=package.path..';%s%s?.lua'", pszPath, g_cPathSplit);

	if(luaL_dostring(m_L, szTmp) != 0)
	{
		return false;
	}

	memset(szTmp, 0, sizeof(szTmp));
	snprintf(szTmp, sizeof(szTmp), "%s%s%s",pszPath, g_cPathSplit, pszFile);

	return luaL_dofile(m_L, szTmp) == 0;
}

int CLuaOper::call_to_h2(const char* pszFunc,const vector<KEY_VALUE>& vec,string& strBody)
{
	lua_getglobal(m_L, pszFunc);

	lua_newtable(m_L);
	
	for(vector<KEY_VALUE>::const_iterator it = vec.begin();it != vec.end();++it)
	{
		lua_pushstring(m_L,it->m_strKey.c_str());//压入key
		lua_pushstring(m_L,it->m_strValue.c_str());//压入value
		lua_settable(m_L,-3);//弹出key,value，并设置到table里面去
	}
	
	if(lua_pcall(m_L,1,1,0) != 0)
	{
		return 1;
	}

	strBody.assign(lua_tostring(m_L, -1));

	lua_pop(m_L, 1);
	
	return 0;
}

/*
int CLuaOper::call_to_ctrl(const char* pszFunc,const char* pszBody,CRequestFlowObj* pObj)
{
	ACE_Guard<ACE_Thread_Mutex> Guard(m_Lock);

//	assert(pszFunc == NULL || pszBody == NULL || pObj == NULL);

	lua_getglobal(m_L, pszFunc);
	
	lua_pushstring(m_L,pszBody);

	if(lua_pcall(m_L,1,1, 0) != 0)
	{
		return 1;
	}

	if(lua_istable(m_L, -1) == 1)
	{
		int nKey = lua_gettop(m_L);
		lua_pushnil(m_L);
											  
		while( 0 != lua_next(m_L,nKey))
		{
			string strKey = lua_tostring(m_L,-2);
																		   
			if(strKey.compare("FLOW_ID") == 0)
			{
				pObj->m_strFlowId.assign(lua_tostring(m_L,-1));
			}
			else
			{
				pObj->m_Params.SetParam(strKey,lua_tostring(m_L,-1));
			}
			
			lua_pop(m_L,1);
		}
	}
	
	lua_pop(m_L, 1);

	return 0;
}
*/

int CLuaOper::call_to_ctrl(const char* pszFunc,const char* pszBody,CRequestFlowObj* pObj)
{
	ACE_Guard<ACE_Thread_Mutex> Guard(m_Lock);

//	assert(pszFunc == NULL || pszBody == NULL || pObj == NULL);

	lua_getglobal(m_L, pszFunc);

	lua_newtable(m_L);
 
	const char* p = pszBody;
 
	const char* q = NULL;
 
	int nKey = 0;
 
	while((q = strchr(p,'\t')) != NULL)
	{
		lua_pushnumber(m_L,nKey++);
 
		if(p != q)
		{
			lua_pushlstring(m_L,p,q - p);
		}
		else
		{
			lua_pushstring(m_L,"");
		}
 
		p = q + 1;
 
		lua_settable(m_L,-3);
	}

	lua_pushnumber(m_L,nKey);

	if(lua_pcall(m_L,2,2, 0) != 0)
	{
		return 1;
	}

	int nRet = (int)lua_tonumber(m_L, -1);

	lua_pop(m_L, 1);

	if(nRet == 0)
	{
		if(lua_istable(m_L, -1) == 1)
		{
			nKey = lua_gettop(m_L);
			lua_pushnil(m_L);

			while( 0 != lua_next(m_L,nKey)) 
			{
				string strKey = lua_tostring(m_L,-2);

				if(strKey.compare("FLOW_ID") == 0)
				{
					pObj->m_strFlowId.assign(lua_tostring(m_L,-1));
				}
				else
				{
					pObj->m_Params.SetParam(strKey,lua_tostring(m_L,-1));
				}

				lua_pop(m_L,1);
			}
		}

		lua_pop(m_L, 1);
	}
	else
	{
		lua_pop(m_L, 1);
	}

	return nRet;
}

int CLuaOper::call_to_func(const char* pszFunc,const vector<KEY_VALUE>& vec,CCallFuncObj &CallFuncObj)
{
	ACE_Guard<ACE_Thread_Mutex> Guard(m_Lock);

	lua_getglobal(m_L, pszFunc);

	lua_newtable(m_L);
	
	for(vector<KEY_VALUE>::const_iterator it = vec.begin();it != vec.end();++it)
	{
		lua_pushstring(m_L,it->m_strKey.c_str());//压入key
		lua_pushstring(m_L,it->m_strValue.c_str());//压入value
		lua_settable(m_L,-3);//弹出key,value，并设置到table里面去
	}
	
	if(lua_pcall(m_L,1,2,0) != 0)
	{
		return 1;
	}

	int nRet = (int)lua_tonumber(m_L, -1);
	 
	lua_pop(m_L, 1);
		  
	if(nRet == 0)
	{
		if(lua_istable(m_L, -1) == 1)
		{
			int nKey = lua_gettop(m_L);
			lua_pushnil(m_L);
														   
			while( 0 != lua_next(m_L,nKey))
			{
				CallFuncObj.m_Params.SetParam(lua_tostring(m_L,-2),lua_tostring(m_L,-1));

				lua_pop(m_L,1);
			}
		}

		lua_pop(m_L, 1);
	}
	else
	{
		lua_pop(m_L, 1);
	}
	
	return 0;
}

bool CLuaOper::CheckAuthen(const string& strID,const string& strIp,const string& strCmd,const string& strMsisdn)
{
	ACE_Guard<ACE_Thread_Mutex> Guard(m_Lock);

	lua_getglobal(m_L, "CheckAuthen");

	lua_pushstring(m_L,strID.c_str());
	lua_pushstring(m_L,strIp.c_str());
	lua_pushstring(m_L,strCmd.c_str());
	lua_pushstring(m_L,strMsisdn.c_str());

	if(lua_pcall(m_L,4,1,0) != 0)
	{
		return false;
	}

	bool bRet = false;

	if(lua_isboolean(m_L,-1))
	{
		bRet = (bool)lua_toboolean(m_L,-1);
	}

	lua_pop(m_L, 1);

	return bRet; 
}

