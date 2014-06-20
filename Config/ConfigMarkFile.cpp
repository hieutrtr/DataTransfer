#include "ConfigMarkFile.h"
#include "../Utilities/Utilities.h"

#define FILE_INFO "FILE_INFO"
#define INFO "INFO"
#define FILENAME "FileName"
#define DATETIME "Datetime"
#define HISTORY_FILE_PERIOD 5

CConfigMarkFile *CConfigMarkFile::s_pInstance = NULL;

CConfigMarkFile::CConfigMarkFile(const string& strCfgFile)
:CConfigFile(strCfgFile)
{
}

CConfigMarkFile::~CConfigMarkFile(void)
{
}


CConfigMarkFile* CConfigMarkFile::GetInstance(const string& strCfgFile)
{
	if (!s_pInstance && !strCfgFile.empty())
	{
		s_pInstance = new CConfigMarkFile(strCfgFile);
	}
	return s_pInstance;
}

void CConfigMarkFile::SetLastDatetime(string strDatetime)
{
	Update(FILE_INFO, DATETIME, strDatetime);
}

string CConfigMarkFile::GetFileName()
{
	return ReadStringValue(FILE_INFO, FILENAME);
}

string CConfigMarkFile::GetLastDatetime()
{
	string strDateTime;
	strDateTime = ReadStringValue(FILE_INFO, DATETIME);
	if (strDateTime == "")
	{
		strDateTime = CUtilities::GetDateSuffixHistory(HISTORY_FILE_PERIOD);
	}

	return strDateTime;
}

string CConfigMarkFile::GetNextDatetime(string strLastDatetime, int iPeriod)
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

void CConfigMarkFile::DeletePositionKey(string strKey)
{
	Delete(INFO, strKey);
}

void CConfigMarkFile::UpdatePositionKey(string strKey, long lPosition)
{
	Update(INFO, strKey, CUtilities::ConvertLongToString(lPosition));
}

void CConfigMarkFile::UpdateInfo(string strKey, long lInfo)
{
	Update(INFO, strKey, CUtilities::ConvertLongToString(lInfo));
}

void CConfigMarkFile::UpdateInfo(string strKey, string strInfo)
{
	Update(INFO, strKey, strInfo);
}

int CConfigMarkFile::GetPosition(string strKey)
{
	return ReadIntValue(INFO, strKey);
}

string CConfigMarkFile::GetInfo(string strKey)
{
	return ReadStringValue(INFO, strKey);
}