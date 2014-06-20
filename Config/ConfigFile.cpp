#include "ConfigFile.h"
#include "../Common/DBCommon.h"

#define DEBUG_GROUP "DEBUG"
#define DEBUG_LEVEL "Level"

#define ERROR_GROUP "ERROR"
#define LOG_GROUP "LOG"
#define ERROR_LOG "ErrorLog"
#define DB_LOG "DBLog"
#define INFO_LOG "InfoLog"

CConfigFile *CConfigFile::s_pInstance = NULL;

CConfigFile::CConfigFile(const string& strFileName)
:CConfigReader(strFileName)
{	
	m_strLocationGroup	= LOCATION_GROUP_DEFAULT;
	m_strDBGroup		= DB_GROUP_MONGODB_DEFAULT;
}

CConfigFile::~CConfigFile(void)
{	
}

CConfigFile* CConfigFile::GetInstance(const string& strCfgFile)
{
	if (!s_pInstance && !strCfgFile.empty())
	{
		s_pInstance = new CConfigFile(strCfgFile);
	}
	return s_pInstance;
}

string CConfigFile::GetInfoLogFileName()
{
	return ReadStringValue(LOG_GROUP, INFO_LOG);
}

string CConfigFile::GetDBLogFileName()
{
	return ReadStringValue(LOG_GROUP, DB_LOG);
}

string CConfigFile::GetErrorLogFileName()
{
	return ReadStringValue(LOG_GROUP, ERROR_LOG);
}

void CConfigFile::SetActiveDBGroup(const string& strDBGroup)
{
	m_strDBGroup = strDBGroup;
}

string CConfigFile::GetDBType()
{
	return ReadStringValue(m_strDBGroup, DB_TYPE);
}

string CConfigFile::GetHost()
{
	return ReadStringValue(m_strDBGroup, HOST);
}

string CConfigFile::GetUser()
{
	return ReadStringValue(m_strDBGroup, USER);
}

string CConfigFile::GetPassword()
{
	return ReadStringValue(m_strDBGroup, PASS);
}

string CConfigFile::GetSource()
{
	return ReadStringValue(m_strDBGroup, SRC);
}

string CConfigFile::GetPort()
{
	return ReadStringValue(m_strDBGroup, PORT);
}

bool CConfigFile::IsReplicateSetUsed()
{
	return ReadBoolValue(m_strDBGroup, REPLICA_SET);
}

string CConfigFile::GetReadReference()
{
	return ReadStringValue(m_strDBGroup, READ_REFERENCE);
}

int CConfigFile::GetDebugLevel()
{
	return ReadIntValue(DEBUG_GROUP, DEBUG_LEVEL);
}

void CConfigFile::SetActiveLocationGroup(const string& strLocationGroup)
{
	m_strLocationGroup = strLocationGroup;
}

string CConfigFile::GetMarkingLogPath()
{
	return ReadStringValue(m_strLocationGroup, MARKING_LOG_PATH);
}

string CConfigFile::GetLogPath()
{
	return ReadStringValue(m_strLocationGroup, LOG_PATH);
}

int CConfigFile::GetPeriod()
{
	return ReadIntValue(m_strLocationGroup, PERIOD);
}

string CConfigFile::GetPrefix()
{
	return ReadStringValue(m_strLocationGroup, PREFIX);
}