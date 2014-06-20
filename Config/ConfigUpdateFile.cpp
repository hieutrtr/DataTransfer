#include "ConfigUpdateFile.h"
#include "../Utilities/Utilities.h"
#include "../Common/DBCommon.h"

#define FILE_INFO "FILE_INFO"
#define INFO "INFO"
#define KEY_POSITION "Position"

CConfigUpdateFile *CConfigUpdateFile::s_pInstance = NULL;

CConfigUpdateFile::CConfigUpdateFile(const string& strCfgFile)
:CConfigFile(strCfgFile)
{
}

CConfigUpdateFile::~CConfigUpdateFile(void)
{
}

CConfigUpdateFile* CConfigUpdateFile::GetInstance(const string& strCfgFile)
{
	if (!s_pInstance && !strCfgFile.empty())
	{
		s_pInstance = new CConfigUpdateFile(strCfgFile);
	}
	return s_pInstance;
}


void CConfigUpdateFile::UpdatePositionKey(long lPosition)
{
	Update(INFO, KEY_POSITION, CUtilities::ConvertLongToString(lPosition));
}

int CConfigUpdateFile::GetPosition()
{
	return ReadIntValue(INFO, KEY_POSITION);
}