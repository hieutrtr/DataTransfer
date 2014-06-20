#pragma once
#include "ConfigFile.h"

class CConfigHistoryFile :
	public CConfigFile
{
	static CConfigHistoryFile *s_pInstance;

public:
	static CConfigHistoryFile* GetInstance(const string& strCfgFile = "");

	string GetLastDatetime();
	string GetNextDatetime(string strLastDatetime, int iPeriod);

	void SetLastDatetime(string strDatetime);
	void DeletePositionKey(string strKey);
	void UpdatePositionKey(string strKey, long lPosition);
	int GetPosition(string strKey);


	string GetFileName();

protected:
	CConfigHistoryFile(const string& strCfgFile);
	~CConfigHistoryFile(void);

};
