#include "TriggerLogParser.h"
#include "../Controller/TriggerController.h"
#include "../Model/TriggerModel.h"
#include "../Common/DBCommon.h"
#include "../Config/ConfigFile.h"
#include "../Config/ConfigMarkFile.h"

CTriggerLogParser::CTriggerLogParser(const string& strConfigFileName, const string& strLocationGroup)
:CLogParser(strConfigFileName, strLocationGroup)
{

	m_pTriggerController = new CTriggerController();
}
CTriggerLogParser::~CTriggerLogParser(void)
{
	if (NULL != m_pTriggerController)
	{
		delete m_pTriggerController;
	}
}

bool CTriggerLogParser::Connect()
{
	RegisterMongodbController(m_pTriggerController, DB_GROUP_MONGODB_MA);
	return CLogParser::Connect();
}

map<string, long> CTriggerLogParser::CollectFile()
{
	map<string, long> map_FileName2Position;
	string strFileName = CConfigFile::GetInstance()->GetLogPath();
	cout << "CollectFile:" << strFileName << endl;
	long lPostion = CConfigMarkFile::GetInstance()->GetPosition("Position");

	map_FileName2Position[strFileName] = lPostion;
	return map_FileName2Position;
}
vector<CLogModel*> CTriggerLogParser::ParseLog(const long &lLength, long &lPosition, char* cBuffer)
{
	int nMegaCount;
	string strTemp;
	int iZbxServerId, iStatus, iPriority, iValue;
	long long lClock, lTriggerId;
	string strExpression, strDescription;
	stringstream strErrorMess;
	BSONObj boTrigger, boQueryTrigger;
	vector<CLogModel*> v_pLogModel;
	nMegaCount = (lPosition / 1000000) + 1;
	cout << "nMegaCount:" << nMegaCount << endl;
	while (lPosition < lLength)
	{
		iPriority = iZbxServerId = iStatus = iValue = 0;
		lTriggerId = lClock = 0;
		strExpression = strDescription = "";
		/*---------------------------------------------*/
		//Parse ServerId
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			iZbxServerId = atoi(strTemp.c_str());
		}
		//Parse iTriggerId
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			lTriggerId = atol(strTemp.c_str());
		}

		//Parse strExpression
		strTemp = GetExpression(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			strExpression = strTemp;
		}

		//Parse Description
		strTemp = GetDescription(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			strDescription = strTemp;
			if (cBuffer[lPosition - 1] == '\n')
			{
				continue;
			}
		}
		else
		{
			GoToNewLine(cBuffer, lPosition, lLength);
			continue;
		}

		//Parse Status
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			iStatus = atoi(strTemp.c_str());
		}

		//Parse Value
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			iValue = atoi(strTemp.c_str());
		}

		//Parse Priority
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			iPriority = atoi(strTemp.c_str());
		}

		//Parse Clock
		strTemp = GetToken(cBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			lClock = atol(strTemp.c_str());
		}
		// cout << iZbxServerId << " | " << lTriggerId << " | " << strExpression << " | " << strDescription << " | " << iStatus 
		// << " | " << iValue << " | " << iPriority << " | " << lClock << endl;
		CTriggerModel *pTriggerModel = new CTriggerModel();
		pTriggerModel->Append("zabbix_server_id", iZbxServerId);
		pTriggerModel->Append("triggerid", lTriggerId);
		pTriggerModel->Append("expression", strExpression);
		pTriggerModel->Append("description", strDescription);
		pTriggerModel->Append("status", iStatus);
		pTriggerModel->Append("value", iValue);
		pTriggerModel->Append("priority", iPriority);
		pTriggerModel->Append("clock", lClock);
		boTrigger = pTriggerModel->LoadObj();
		boQueryTrigger = pTriggerModel->UniqueQuery(boTrigger);
		cout << "lPosition:" << lPosition << endl;
		cout << "lLength:" << lLength << endl;
		m_pTriggerController->Insert(boTrigger, boQueryTrigger);
		delete pTriggerModel;
		if (lPosition >= lLength || lPosition > 1000000 * nMegaCount)
		{
			string strLog;
			stringstream strMess;
			strMess << "Length:" << lLength;
			strMess << "|Position:" << lPosition;
			strLog = CUtilities::FormatLog(INFO_MSG, "triggerParser", "ParseLog", strMess.str());
			CUtilities::WriteInfoLog(INFO_MSG, strLog);
			CConfigMarkFile::GetInstance()->UpdatePositionKey("Position",lPosition);
			break;
		}
	}
	return v_pLogModel;
}

void CTriggerLogParser::ProceedData(vector<CLogModel*> v_LogModelPtr)
{

}