#include "CentralizeZbxEventProcessor.h"
#include "../Model/CentralizeEventModel.h"
#include "../Controller/EventController.h"
#include "../Controller/TriggerController.h"
#include "../Controller/ServerController.h"
#include "../Controller/ZbxAlertController.h"
#include "../Common/DBCommon.h"

CCentralizeZbxEventProcessor::CCentralizeZbxEventProcessor(const string& strConfigFileName)
:CCentralizeProcessor(strConfigFileName)
{
	m_pSourceController = new CEventController();
	m_pDesController = new CZbxAlertController();
	m_pCentralModel = new CCentralizeEventModel();
	m_pTriggerLogController = new CTriggerController();
	m_pServerController = new CServerController();
}

CCentralizeZbxEventProcessor::~CCentralizeZbxEventProcessor(void)
{
	if (NULL != m_pTriggerLogController)
	{
		delete m_pTriggerLogController;
	}
	if (NULL != m_pServerController)
	{
		delete m_pServerController;
	}
}

bool CCentralizeZbxEventProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterMongodbController(m_pSourceController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pDesController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pTriggerLogController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pServerController, DB_GROUP_MONGODB_CMDB);

	return CProcessor::Connect();
}

BSONObj CCentralizeZbxEventProcessor::GetAdditionInfo(BSONObj boRecord)
{
	auto_ptr<DBClientCursor> ptrTriggerDataCursor;
	auto_ptr<DBClientCursor> ptrMapZbxServerCursor;
	auto_ptr<DBClientCursor> ptrServerCursor;
	BSONObj boAddtionInfo, boTriggerRecord, boMapZbxServerRecord, boServerRecord;
	int iPriority;
	string strDescription, strHost, strDeptAlias, strProdAlias, strSerialNumber;
	strDescription = strHost = strDeptAlias = strProdAlias = strSerialNumber = "";
	iPriority = 0;
	/*-- Get Trigger Info By triggerid --*/
	Query queryCondition = QUERY("triggerid" << boRecord["triggerid"] << "zabbix_server_id" << boRecord["zabbix_server_id"]);
	m_pTriggerLogController->Find(ptrTriggerDataCursor,queryCondition);
	if (ptrTriggerDataCursor->more())
	{
		boTriggerRecord = ptrTriggerDataCursor->nextSafe();
	}

	/*-- Get Server Info --*/
	if (!boTriggerRecord.isEmpty())
	{
		iPriority		= boTriggerRecord.hasField("priority") ? boTriggerRecord.getIntField("priority") : 0;
		strDescription	= boTriggerRecord.hasField("description") ? boTriggerRecord.getStringField("description") : "";

		m_pServerController->Find(TBL_MAP_ZBX_SERVER, ptrMapZbxServerCursor, QUERY("zbx_server_id" << boRecord["serverid"]));
		if (ptrMapZbxServerCursor->more())
		{
			boMapZbxServerRecord = ptrMapZbxServerCursor->nextSafe();
			strSerialNumber = boMapZbxServerRecord.hasField("serial_number") ? boMapZbxServerRecord.getStringField("serial_number") : "";
			if (!strSerialNumber.empty())
			{
				m_pServerController->Find(ptrServerCursor, QUERY("code" << strSerialNumber));
				if (ptrServerCursor->more())
				{
					boServerRecord = ptrServerCursor->nextSafe();
					strHost			= boServerRecord.hasField("server_name") ? boServerRecord.getStringField("server_name") : "";
					strDeptAlias	= boServerRecord.hasField("department_alias") ? boServerRecord.getStringField("department_alias") : "";
					strProdAlias	= boServerRecord.hasField("product_alias") ? boServerRecord.getStringField("product_alias") : "";
				}
			}
		}
		if (!strDescription.empty())
		{
			if (!strHost.empty())
			{
				int iDesPos = strDescription.find("{HOSTNAME}");
				if (iDesPos != string::npos)
					strDescription = strDescription.replace(iDesPos, iDesPos + 9, strHost);
				else{
					iDesPos = strDescription.find("{HOST.NAME}");
					if (iDesPos != string::npos)
						strDescription = strDescription.replace(iDesPos, iDesPos + 10, strHost);
				}
			}
		}
		boAddtionInfo = BSON(
			"priority" << iPriority <<
			"description" << strDescription <<
			"host" << strHost <<
			"cmdb_department_alias" << strDeptAlias <<
			"cmdb_product_alias" << strProdAlias
			);
	}

	return boAddtionInfo.copy();
}

bool CCentralizeZbxEventProcessor::ExecuteLateProcess(BSONObj boRecord)
{
	m_pSourceController->Update(BSON("$set" << BSON("is_sync" << 1)), QUERY("_id" << boRecord["_id"]));
	return true;
}

bool CCentralizeZbxEventProcessor::ExecuteEarlyProcess(BSONObj boRecord)
{
	auto_ptr<DBClientCursor> ptrTriggerDataCursor;
	BSONObj boTriggerRecord;
	int iPriority;
	iPriority = 0;
	Query queryCondition = QUERY("triggerid" << boRecord["triggerid"] << "zabbix_server_id" << boRecord["zabbix_server_id"]);
	m_pTriggerLogController->Find(ptrTriggerDataCursor, queryCondition);
	if (ptrTriggerDataCursor->more())
	{
		boTriggerRecord = ptrTriggerDataCursor->nextSafe();
	}

	/*-- Check Trigger Info --*/
	if (boTriggerRecord.isEmpty())
	{
		return false;
	}
	iPriority = boTriggerRecord.hasField("priority") ? boTriggerRecord.getIntField("priority") : 0;
	if (5 != iPriority)
	{
		return false;
	}
	return true;
}