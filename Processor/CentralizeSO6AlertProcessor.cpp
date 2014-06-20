#include "CentralizeSO6AlertProcessor.h"
#include "../Model/CentralizeSO6AlertModel.h"
#include "../Controller/SO6AlertController.h"
#include "../Controller/MAAlertController.h"
#include "../Controller/MapProductController.h"
#include "../Common/DBCommon.h"

CCentralizeSO6AlertProcessor::CCentralizeSO6AlertProcessor(const string& strConfigFileName)
:CCentralizeProcessor(strConfigFileName)
{
	m_pSourceController = NULL;
	m_pSourceMySQLController = new CSO6AlertController();
	m_pDesController = new CMAAlertController();
	m_pCentralModel = new CCentralizeSO6AlertModel();
	m_pMapProductController = new CMapProductController();
}

CCentralizeSO6AlertProcessor::~CCentralizeSO6AlertProcessor(void)
{
	if (NULL != m_pMapProductController)
	{
		delete m_pMapProductController;
	}
}

bool CCentralizeSO6AlertProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterMySQLController(m_pSourceMySQLController, DB_GROUP_MYSQL_SO6);
	RegisterMongodbController(m_pDesController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pMapProductController, DB_GROUP_MONGODB_MA);

	return CProcessor::Connect();
}

bool CCentralizeSO6AlertProcessor::Save()
{
	BSONObj boCenRecord;
	m_vStrAlertId.push_back(m_pSourceMySQLController->FetchString("id"));
	boCenRecord = CreateBSON();
	CCentralizeProcessor::Save(boCenRecord);
	return true;
}

BSONObj CCentralizeSO6AlertProcessor::CreateBSON()
{
	BSONObj boRecord;
	boRecord = BSON(
		"id" << m_pSourceMySQLController->FetchString("id") <<
		"serverid" << m_pSourceMySQLController->FetchString("serverid") <<
		"servername" << m_pSourceMySQLController->FetchString("servername") <<
		"content" << m_pSourceMySQLController->FetchString("content") <<
		"updatetime" << m_pSourceMySQLController->FetchString("updatetime") <<
		"sendalert" << m_pSourceMySQLController->FetchString("sendalert") <<
		"reason" << m_pSourceMySQLController->FetchString("reason") <<
		"priority" << m_pSourceMySQLController->FetchString("priority") <<
		"type_alert" << m_pSourceMySQLController->FetchString("type_alert")
		);
	return boRecord.copy();
}

BSONObj CCentralizeSO6AlertProcessor::GetAdditionInfo(BSONObj boRecord)
{
	auto_ptr<DBClientCursor> ptrMapProductCursor;
	BSONObj boAddtionInfo, boMapProductRecord;
	string strProduct, strContent, strDescription, strTmp, strMsgAlert;
	vector<string> vInformation;

	/*-- Get Map Product Info --*/
	strProduct = GetSO6Product(boRecord.getStringField("servername"));
	Query queryCondition = QUERY("source" << "SO6" << "src_product" << strProduct);
	ptrMapProductCursor = m_pMapProductController->Find(queryCondition);
	if ((ptrMapProductCursor.get() != NULL) && (ptrMapProductCursor->more()))
	{
		boMapProductRecord = ptrMapProductCursor->nextSafe();
		if (boMapProductRecord.hasField("itsm_product"))
		{
			strProduct = boMapProductRecord.getStringField("itsm_product");
			//====================================
			strContent = boRecord.getStringField("content");
			strContent = CUtilities::StripTags(strContent);
			strContent = CUtilities::ReplaceString(strContent, "\r\n", "\n");
			strContent = CUtilities::ReplaceString(strContent, "\n\r", "\n");
			strDescription = strContent;
			vInformation = CUtilities::SplitString(strContent, "\n");
			if (vInformation.size() > 1)
			{
				strTmp = vInformation[1];
				std::remove(strTmp.begin(), strTmp.end(), ' ');
				if (!strTmp.empty())
					strMsgAlert = CUtilities::ReplaceString(vInformation[1], ",", "\n");
				else
					strMsgAlert = CUtilities::ReplaceString(vInformation[0], ",", "\n");
			}
			else
				strMsgAlert = CUtilities::ReplaceString(vInformation[0], ",", "\n");
			strMsgAlert = "[" + strProduct + "] " + strMsgAlert;
		}
	}
	boAddtionInfo = BSON(
		"product" << strProduct <<
		"description" << strDescription <<
		"alert_message" << strMsgAlert
		);

	return boAddtionInfo.copy();
}

string CCentralizeSO6AlertProcessor::GetSO6Product(string strServerName)
{
	int iFindStart, iFindEnd, iSpec;
	string strRes;
	strRes = "";
	if (strServerName.compare("SO6_G6Mobile_XH-Report21") == 0)
	{
		strRes = "XH";
		return strRes;
	}
	if (strServerName.compare("SO6_G6Membase_Mem45-UNIN") == 0)
	{
		strRes = "UNIN";
		return strRes;
	}
	// iSpec = strServerName.find("SO6_");
	// if(iSpec != std::string::npos)
	// {
	// iFindEnd = strServerName.find("_",4);
	// strRes = strServerName.substr(iSpec,iFindEnd);
	// return strRes;
	// }
	iSpec = strServerName.find("_DEV");
	if (iSpec == std::string::npos)
	{
		iSpec = strServerName.find("_Dev");
	}
	if (iSpec != std::string::npos)
	{
		iSpec += 4;
		strRes = strServerName.substr(0, iSpec);
		return strRes;
	}

	iFindStart = strServerName.find("_");
	if (iFindStart == std::string::npos)
	{
		iFindStart = strServerName.find("-");
	}
	if (iFindStart != std::string::npos)
	{
		iFindEnd = strServerName.find("_", iFindStart + 1);
		if (iFindEnd != std::string::npos)
		{
			strRes = strServerName.substr(iFindStart + 1, iFindEnd - iFindStart - 1);
		}
		else
		{
			iFindEnd = strServerName.find("-", iFindStart + 1);
			if (iFindEnd != std::string::npos)
				strRes = strServerName.substr(iFindStart + 1, iFindEnd - iFindStart - 1);
		}
	}
	return strRes;
}

bool CCentralizeSO6AlertProcessor::ExecuteLateProcess()
{
	bool bResult;
	CMAAlertController *pMAAlertController = dynamic_cast<CMAAlertController*>(m_pDesController);
	bResult = pMAAlertController->HideAlertNotInSrcId("SO6", m_vStrAlertId);
	m_vStrAlertId.clear();
	return bResult;
}
