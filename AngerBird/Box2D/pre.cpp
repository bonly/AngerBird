#include "pre.h"
#include "JFileInputStream.h"
char gpcDebug[LOGLEN];

bool OutputDebugData(const char* pcDbg)
{
#ifndef _DEBUG
		return true;
#endif
	IFileMgr* pFileMgrDbg = NULL;
	AEEApplet* pMe = (AEEApplet*) GETAPPINSTANCE();
	if (!pMe)
		return false;

	ISHELL_CreateInstance(pMe->m_pIShell, AEECLSID_FILEMGR, (void**)&pFileMgrDbg);
	
	if (!pFileMgrDbg)
		return false;

	int rc = 0;
	IFile* pIFileWrite = NULL;

	//打开配置文件 每次都重构
	if (SUCCESS != IFILEMGR_Test(pFileMgrDbg, "mylog.log"))
	{
		pIFileWrite = IFILEMGR_OpenFile(pFileMgrDbg, "mylog.log", _OFM_CREATE);
	}
	else
	{
		pIFileWrite = IFILEMGR_OpenFile(pFileMgrDbg, "mylog.log", _OFM_APPEND);
	}
	if (!pIFileWrite)
	{
		IFILEMGR_Release(pFileMgrDbg);
		return false;
	}

	rc = IFILE_Write(pIFileWrite, pcDbg, STRLEN(pcDbg));
	IFILE_Release(pIFileWrite);
	IFILEMGR_Release(pFileMgrDbg);
	return true;

}


