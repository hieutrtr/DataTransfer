#include "EventLogParser.h"
#include "../Controller/EventController.h"
#include "../Model/EventModel.h"
#include "../Common/DBCommon.h"
#include "../Config/ConfigFile.h"
#include "../Config/ConfigMarkFile.h"

CEventLogParser::CEventLogParser(const string& strConfigFileName, const string& strLocationGroup)
:CLogParser(strConfigFileName, strLocationGroup)
{
	m_pEventController = new CEventController();
}
CEventLogParser::~CEventLogParser(void)
{
	if (NULL != m_pEventController)
	{
		delete m_pEventController;
	}
}

bool CEventLogParser::Connect()
{
	RegisterMongodbController(m_pEventController, DB_GROUP_MONGODB_MA);
	return CLogParser::Connect();
}

map<string, long> CEventLogParser::CollectFile()
{
	struct tm tm;
	map<string, long> map_FileName2Position;
	string strFileName, strSuffix;
	long lPostion;
	int iIsEnd;

	strFileName = CConfigFile::GetInstance()->GetLogPath();
	lPostion = CConfigMarkFile::GetInstance()->GetPosition("Position");
	strSuffix = CConfigMarkFile::GetInstance()->GetInfo("Suffix");
	if (strSuffix.empty())
	{
		strSuffix = CUtilities::GetDateSuffixLogByDay();
		CConfigMarkFile::GetInstance()->UpdateInfo("Suffix", strSuffix);
		CConfigMarkFile::GetInstance()->UpdateInfo("Position", 0);
		CConfigMarkFile::GetInstance()->UpdateInfo("IsEnd", 0);
	}
	else
	{
		iIsEnd = atoi(CConfigMarkFile::GetInstance()->GetInfo("IsEnd").c_str());
		if (iIsEnd)
		{
			memset(&tm, 0, sizeof(struct tm));
			strptime(strSuffix.c_str(), "%Y%m%d", &tm);
			tm.tm_mday++;
			mktime(&tm);
			strSuffix = CUtilities::FormatDateSuffixLogByDay(tm);
			CConfigMarkFile::GetInstance()->UpdateInfo("Suffix", strSuffix);
			CConfigMarkFile::GetInstance()->UpdateInfo("Position", 0);
			CConfigMarkFile::GetInstance()->UpdateInfo("IsEnd", 0);
		}
	}
	strFileName += strSuffix;
	map_FileName2Position[strFileName] = lPostion;
	return map_FileName2Position;
}

vector<CLogModel*> CEventLogParser::ParseLog(const long &lLength, long &lPosition, char* cBuffer)
{
	string strTemp;
	int iZbxServerId, iStatus, iValueChanged;
	long long lClock, lEventId, lTriggerId, lHostId, lItemId, lServerId;
	BSONObj boEvent, boQueryEvent;
	vector<CLogModel*> v_pLogModel;
	while (lPosition < lLength)
	{
		iZbxServerId = iStatus = iValueChanged = 0;
		lClock = lEventId = lTriggerId = lHostId = lItemId = 0;
		/*---------------------------------------------*/
		//Parse Clock
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			lClock = atol(strTemp.c_str());
		}
		//Parse ZbxServerId
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			iZbxServerId = atoi(strTemp.c_str());
		}

		//Parse EventId
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			lEventId = atol(strTemp.c_str());
		}

		//Parse Status
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			iStatus = atoi(strTemp.c_str());
		}

		//Parse TriggerId
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			lTriggerId = atol(strTemp.c_str());
		}

		//Parse HostId
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			lHostId = atol(strTemp.c_str());
		}

		//ServerId
		lServerId = ((lHostId - 10000) * 256) + iZbxServerId;

		//Parse ItemId
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			lItemId = atol(strTemp.c_str());
		}

		//Parse ValueChanged
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			iValueChanged = atoi(strTemp.c_str());
		}


		// cout << iZbxServerId << " | " << lEventId << " | " << strExpression << " | " << strDescription << " | " << iStatus 
		// << " | " << iValue << " | " << iPriority << " | " << lClock << endl;
		CEventModel *pEventModel = new CEventModel();
		pEventModel->Append("clock", lClock);
		pEventModel->Append("zabbix_server_id", iZbxServerId);
		pEventModel->Append("eventid", lEventId);
		pEventModel->Append("status", iStatus);
		pEventModel->Append("triggerid", lTriggerId);
		pEventModel->Append("hostid", lHostId);
		pEventModel->Append("serverid", lServerId);
		pEventModel->Append("itemid", lItemId);
		pEventModel->Append("value_changed", iValueChanged);
		pEventModel->Append("is_sync", 0);
		boEvent = pEventModel->LoadObj();
		boQueryEvent = pEventModel->UniqueQuery(boEvent);
		cout << "lPosition:" << lPosition << endl;
		cout << "lLength:" << lLength << endl;
		cout << "boEvent:" << boEvent << endl;
		cout << "boQueryEvent:" << boQueryEvent << endl;
		m_pEventController->Insert(boEvent, boQueryEvent);
		delete pEventModel;
	}

	if (!lLength)
	{
		CConfigMarkFile::GetInstance()->UpdateInfo("Suffix", "");
	}
	else
	{
		CConfigMarkFile::GetInstance()->UpdateInfo("IsEnd", 1);
	}
	return v_pLogModel;
}

void CEventLogParser::ProceedData(vector<CLogModel*> v_LogModelPtr)
{

}