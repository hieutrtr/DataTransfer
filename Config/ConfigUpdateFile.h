#pragma once
#include "ConfigFile.h"

class CConfigUpdateFile :
	public CConfigFile
{
	static CConfigUpdateFile *s_pInstance;

public:
	static CConfigUpdateFile* GetInstance(const string& strCfgFile = "");
	void UpdatePositionKey(long lPosition);
	int GetPosition();
protected:
	CConfigUpdateFile(const string& strCfgFile);
	~CConfigUpdateFile(void);

};
