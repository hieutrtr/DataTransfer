#include "ConfigHistoryFile.h"
#include "../Utilities/Utilities.h"

#define FILE_INFO "FILE_INFO"
#define INFO "INFO"
#define FILENAME "FileName"
#define DATETIME "Datetime"
#define HISTORY_FILE_PERIOD 5

CConfigHistoryFile *CConfigHistoryFile::s_pInstance = NULL;

CConfigHistoryFile::CConfigHistoryFile(const string& strCfgFile)
:CConfigFile(strCfgFile)
{
}

CConfigHistoryFile::~CConfigHistoryFile(void)
{
}


CConfigHistoryFile* CConfigHistoryFile::GetInstance(const string& strCfgFile)
{
	if (!s_pInstance && !strCfgFile.empty())
	{
		s_pInstance = new CConfigHistoryFile(strCfgFile);
	}
	return s_pInstance;
}

void CConfigHistoryFile::SetLastDatetime(string strDatetime)
{
	Update(FILE_INFO, DATETIME, strDatetime);
}

string CConfigHistoryFile::GetFileName()
{
	return ReadStringValue(FILE_INFO, FILENAME);
}

string CConfigHistoryFile::GetLastDatetime()
{
	string strDateTime;
	strDateTime = ReadStringValue(FILE_INFO, DATETIME);
	if (strDateTime == "")
	{
		strDateTime = CUtilities::GetDateSuffixHistory(HISTORY_FILE_PERIOD);
	}

	return strDateTime;
}

string CConfigHistoryFile::GetNextDatetime(string strLastDatetime, int iPeriod)
{
	struct tm tm;
	string strNextDatetime;
	try{
		memset(&tm, 0, sizeof(struct tm));

		strptime(strLastDatetime.c_str(), "%Y%m%d_%H%M", &tm);
		tm.tm_min += iPeriod;
		mktime(&tm);
	}
	catch (exception& ex)
	{
		string strFormatLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__;
		strFormatLog = CUtilities::FormatLog(ERROR_MSG, "CHistoryConfig", "GetNextDatetime", strErrorMess.str());
		CUtilities::WriteErrorLog(strFormatLog);
	}

	strNextDatetime = CUtilities::FormatDateSuffixHistory(tm);
	return strNextDatetime;
}

void CConfigHistoryFile::DeletePositionKey(string strKey)
{
	Delete(INFO, strKey);
}

void CConfigHistoryFile::UpdatePositionKey(string strKey, long lPosition)
{
	Update(INFO, strKey, CUtilities::ConvertLongToString(lPosition));
}

int CConfigHistoryFile::GetPosition(string strKey)
{
	return ReadIntValue(INFO, strKey);
}