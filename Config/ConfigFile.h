#pragma once
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ConfigReader.h"

class CConfigFile:public CConfigReader
{
	static CConfigFile* s_pInstance;

protected:
	string m_strLocationGroup;
	string m_strDBGroup;

	CConfigFile(const string& strCfgFile);
	~CConfigFile(void);

public:	
	static CConfigFile* GetInstance(const string& strCfgFile = "");

	string GetErrorLogFileName();
	string GetDBLogFileName();
	string GetInfoLogFileName();
	string GetDBType();
	string GetHost();
	string GetUser();
	string GetPassword();
	string GetSource();
	string GetPort();
	string GetReadReference();

	bool IsReplicateSetUsed();
	int GetDebugLevel();

	void SetActiveDBGroup(const string& strDBGroup);
	void SetActiveLocationGroup(const string& strLocationGroup);
	string GetMarkingLogPath();
	string GetLogPath();
	string GetPrefix();
	int GetPeriod();
	
};

