#pragma once
#include "ConfigFile.h"

class CConfigMarkFile :
	public CConfigFile
{
	static CConfigMarkFile *s_pInstance;

public:
	static CConfigMarkFile* GetInstance(const string& strCfgFile = "");

	string GetLastDatetime();
	string GetNextDatetime(string strLastDatetime, int iPeriod);

	void SetLastDatetime(string strDatetime);
	void DeletePositionKey(string strKey);
	void UpdatePositionKey(string strKey, long lPosition);
	int GetPosition(string strKey); 
	string GetInfo(string strKey);
	void UpdateInfo(string strKey, long strInfo);
	void UpdateInfo(string strKey, string strInfo);


	string GetFileName();

protected:
	CConfigMarkFile(const string& strCfgFile);
	~CConfigMarkFile(void);

};
