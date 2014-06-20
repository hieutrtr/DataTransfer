#include "UpdateItemLogParser.h"
#include "../Controller/UpdateItemLogController.h"
#include "../Model/UpdateItemLogModel.h"
#include "../Model/LogModel.h"
#include "../Config/ConfigUpdateFile.h"
#include "../Utilities/FileMapping.h"
#include "../Common/DBCommon.h"

CUpdateItemLogParser::CUpdateItemLogParser(const string& strConfigFileName, const string& strLocationGroup)
:CLogParser(strConfigFileName, strLocationGroup)
{
	m_pUpdateItemLogController = new CUpdateItemLogController();

	CConfigFile::GetInstance()->SetActiveLocationGroup(strLocationGroup);
	string strMarkingLog = CConfigFile::GetInstance()->GetMarkingLogPath();
	CConfigUpdateFile::GetInstance(strMarkingLog);
}

CUpdateItemLogParser::~CUpdateItemLogParser(void)
{
	if (m_pUpdateItemLogController != NULL)
	{
		delete m_pUpdateItemLogController;
		m_pUpdateItemLogController = NULL;
	}
}

bool CUpdateItemLogParser::Connect()
{
	// Register controllers before connecting to database
	RegisterMongodbController(m_pUpdateItemLogController, DB_GROUP_MONGODB_MA);
	return CProcessor::Connect();
}

void CUpdateItemLogParser::ParseLog()
{
	long lPosition;
	string strFileName;
	strFileName = CConfigFile::GetInstance()->GetLogPath();
	// If parse log success, update position in marking logs

	lPosition = CConfigUpdateFile::GetInstance()->GetPosition();
	cout << "[Current Position] " << lPosition << endl;
	if (CLogParser::ParseLog(strFileName, lPosition))
	{
		CConfigUpdateFile::GetInstance()->UpdatePositionKey(lPosition);
		cout << "[Last Position] " << lPosition << endl;
	}
}


vector<CLogModel*> CUpdateItemLogParser::ParseLog(long& lPosition, long lLength, char* pBuffer)
{
	vector<CLogModel*> vtUpdateItemLogModelPtr;
	string strTemp;
	int iZbxServerId, iStatus, iValueType;
	long long lClock, lHostId, lItemId, lServerId;
	string strDescription, strKey, strUnits, strType;

	while (lPosition < lLength)
	{
		// Init database fields
		iZbxServerId = iStatus = iValueType = 0;
		lClock = lItemId = lHostId = lItemId = lServerId = 0;
		strDescription = strKey = strUnits = strType = "";

		//Parse Clock
		strTemp = GetToken((const char*)pBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			try
			{
				lClock = atol(strTemp.c_str());
			}
			catch (exception &ex)
			{
				stringstream strErrorMess;
				strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " << CUtilities::GetCurrTime() << endl;
				CUtilities::WriteErrorLog(ERROR_MSG, strErrorMess.str());
			}
		}

		//Parse ZbxServerId
		strTemp = GetToken((const char*)pBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			try
			{
				iZbxServerId = atoi(strTemp.c_str());
			}
			catch (exception &ex)
			{
				stringstream strErrorMess;
				strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " << CUtilities::GetCurrTime() << endl;
				CUtilities::WriteErrorLog(strErrorMess.str());
			}
		}

		//Parse HostId
		strTemp = GetToken((const char*)pBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			try
			{
				lHostId = atol(strTemp.c_str());
			}
			catch (exception &ex)
			{
				stringstream strErrorMess;
				strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " << CUtilities::GetCurrTime() << endl;
				CUtilities::WriteErrorLog(strErrorMess.str());
			}
		}

		//ServerId
		lServerId = ((lHostId - 10000) * 256) + iZbxServerId;

		//Parse ItemId
		strTemp = GetToken((const char*)pBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			try
			{
				lItemId = atol(strTemp.c_str());
			}
			catch (exception &ex)
			{
				stringstream strErrorMess;
				strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " << CUtilities::GetCurrTime() << endl;
				CUtilities::WriteErrorLog(strErrorMess.str());
			}
		}

		//Parse Status
		strTemp = GetToken((const char*)pBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			try
			{
				iStatus = atoi(strTemp.c_str());
			}
			catch (exception &ex)
			{
				stringstream strErrorMess;
				strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " << CUtilities::GetCurrTime() << endl;
				CUtilities::WriteErrorLog(strErrorMess.str());
			}
		}

		//Parse Key
		strKey = GetItemKey((const char*)pBuffer, lPosition, lLength);;

		//Parse Type
		int iPos;
		iPos = strKey.find("[");
		if (iPos != std::string::npos){
			strType = strKey.substr(0, iPos);
		}
		else
		{
			strType = strKey;
		}

		//Parse Description
		strTemp = GetDescription((const char*)pBuffer, lPosition, lLength);;
		if (strTemp.compare("") != 0)
		{
			strDescription = strTemp;
		}

		//Parse ValueType
		strTemp = GetToken((const char*)pBuffer, lPosition, lLength);
		if (strTemp.compare("") != 0)
		{
			try
			{
				iValueType = atoi(strTemp.c_str());
			}
			catch (exception &ex)
			{
				stringstream strErrorMess;
				strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__ << " | at : " << CUtilities::GetCurrTime() << endl;
				CUtilities::WriteErrorLog(strErrorMess.str());
			}
		}

		//Parse Units
		//cout<< Buffer[nCurPosition] << endl;;
		if (pBuffer[lPosition] != '\n')
		{
			strUnits = GetToken((const char*)pBuffer, lPosition, lLength);
		}
		/*cout << lClock << " | " << iZbxServerId << " | " << lHostId << " | " << lItemId << " | " << iStatus << " | " << strKey 
		<< " | " << strDescription << " | " << iValueType << " | " <<endl;*/
		//CLogModel* pLogModel = new CUpdateItemLogModel();
		CUpdateItemLogModel *pUpdateItemLogModel = new CUpdateItemLogModel(); //dynamic_cast<CUpdateItemLogModel*>(pLogModel);
		pUpdateItemLogModel->SetClock(lClock);
		pUpdateItemLogModel->SetZbxServerId(iZbxServerId);
		pUpdateItemLogModel->SetHostId(lHostId);
		pUpdateItemLogModel->SetServerId(lServerId);
		pUpdateItemLogModel->SetItemId(lItemId);
		pUpdateItemLogModel->SetStatus(iStatus);
		pUpdateItemLogModel->SetKey(strKey);
		pUpdateItemLogModel->SetDescription(strDescription);
		pUpdateItemLogModel->SetValueType(iValueType);
		pUpdateItemLogModel->SetUnits(strUnits);
		pUpdateItemLogModel->SetAlertType(strType);
		vtUpdateItemLogModelPtr.push_back(pUpdateItemLogModel);
	}
	return vtUpdateItemLogModelPtr;
}

bool CUpdateItemLogParser::ProcessData(vector<CLogModel*> vtLogModelPtr)
{
	bool bResult = true;
	BSONObj boItemData;
	vector<BSONObj> vboItemData;
	vector<BSONObj>::iterator itObj;
	vector<CLogModel*>::iterator itModel;
	/*-- Collect data for bulk insert --*/
	itModel = vtLogModelPtr.begin();
	while (itModel != vtLogModelPtr.end())
	{
		boItemData = (*itModel)->GetBSONModel();
		cout << "boItemData: "<< boItemData << endl;
		m_pUpdateItemLogController->Insert(boItemData, BSON("serverid" << boItemData["serverid"] << "itemid" << boItemData["itemid"]));
		//vboItemData.push_back(boItemData);
		itModel++;
	}
	return bResult;
}