#include "CentralizeZbxAlertProcessor.h"
#include "../Model/CentralizeZbxAlertModel.h"
#include "../Controller/ZbxAlertController.h"
#include "../Controller/MAAlertController.h"
#include "../Controller/UpdateItemLogController.h"
#include "../Common/DBCommon.h"

CCentralizeZbxAlertProcessor::CCentralizeZbxAlertProcessor(const string& strConfigFileName)
:CCentralizeProcessor(strConfigFileName)
{
	m_pSourceController = new CZbxAlertController();
	m_pDesController = new CMAAlertController();
	m_pCentralModel = new CCentralizeZbxAlertModel();
	m_pUpdateItemController = new CUpdateItemLogController();
}

CCentralizeZbxAlertProcessor::~CCentralizeZbxAlertProcessor(void)
{
	if (NULL != m_pUpdateItemController)
	{
		delete m_pUpdateItemController;
	}
}

bool CCentralizeZbxAlertProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterMongodbController(m_pSourceController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pDesController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pUpdateItemController, DB_GROUP_MONGODB_MA);

	return CProcessor::Connect();
}

BSONObj CCentralizeZbxAlertProcessor::GetAdditionInfo(BSONObj boRecord)
{
	auto_ptr<DBClientCursor> ptrItemDataCursor;
	auto_ptr<DBClientCursor> ptrMapDataCursor;
	BSONObj boAddtionInfo, boItemRecord, boMapRecord;

	/*-- Get Item Info By itemid --*/
	Query queryCondition = QUERY("itemid" << boRecord["itemid"]);
	ptrItemDataCursor = m_pUpdateItemController->Find(queryCondition);
	if ((ptrItemDataCursor.get() != NULL) && (ptrItemDataCursor->more()))
	{
		boItemRecord = ptrItemDataCursor->nextSafe();
	}

	/*-- Get Alert Type Mapping Info By alert_key --*/
	if (!boItemRecord.isEmpty())
	{
		Query queryMapCondition = QUERY("alert_key" << boItemRecord["key_"]);
		ptrMapDataCursor = m_pUpdateItemController->Find(TBL_MAP_ALERT_TYPE, queryMapCondition);
		if ((ptrMapDataCursor.get() != NULL) && (ptrMapDataCursor->more()))
		{
			boMapRecord = ptrMapDataCursor->nextSafe();
			/*-- Build alert_type info --*/
			if (boMapRecord.hasField("alert_type"))
			{
				boAddtionInfo = BSON(
					"alert_type" << boMapRecord["alert_type"]
					);
			}
		}
	}

	return boAddtionInfo.copy();
}

bool CCentralizeZbxAlertProcessor::ExecuteLateProcess(BSONObj boRecord)
{
	auto_ptr<DBClientCursor> ptrNewDataCursor;
	auto_ptr<DBClientCursor> ptrOldDataCursor;
	auto_ptr<DBClientCursor> ptrACKDataCursor;
	BSONObj boOldAlertCondition, boNewAlertCondition, boOldAlert, boNewAlert, boACK;
	CCentralizeZbxAlertModel *pCentralCentralizeZbxAlertModel = dynamic_cast<CCentralizeZbxAlertModel*>(m_pCentralModel);

	boOldAlertCondition = pCentralCentralizeZbxAlertModel->GetOldAlertCondition(boRecord);
	boNewAlertCondition = pCentralCentralizeZbxAlertModel->GetNewAlertCondition(boRecord);
	/*-- Get New Alert Info --*/
	ptrNewDataCursor = m_pDesController->Find(Query(boNewAlertCondition));
	if ((ptrNewDataCursor.get() != NULL) && (ptrNewDataCursor->more()))
	{
		boNewAlert = ptrNewDataCursor->nextSafe();
	}
	if (!boNewAlert.isEmpty())
	{
		/*-- Get Prev Alert Info --*/
		ptrOldDataCursor = m_pDesController->Find(Query(boOldAlertCondition));
		if ((ptrOldDataCursor.get() != NULL) && (ptrOldDataCursor->more()))
		{
			boOldAlert = ptrOldDataCursor->nextSafe();
		}
		if (!boOldAlert.isEmpty())
		{
			/*-- Clone ACK --*/
			ptrACKDataCursor = m_pDesController->Find(TBL_ALERT_ACK, QUERY("alert_id" << boOldAlert["_id"]));
			if ((ptrACKDataCursor.get() != NULL) && (ptrACKDataCursor->more()))
			{
				while (ptrACKDataCursor->more())
				{
					BSONObjBuilder bbRecordBuilder;
					boACK = ptrACKDataCursor->nextSafe();
					boACK = boACK.removeField("_id");
					boACK = boACK.removeField("source_id");
					boACK = boACK.removeField("alert_id");
					bbRecordBuilder.appendElements(boACK);
					bbRecordBuilder.append("alert_id", boNewAlert["_id"]);
					bbRecordBuilder.append("source_id", boNewAlert["_id"]);
					m_pDesController->Insert(TBL_ALERT_ACK, bbRecordBuilder.obj());
				}
			}
		}
	}
	m_pDesController->Update(BSON("$set" << BSON("is_show" << 2)), Query(boOldAlertCondition));
	m_pDesController->Update(BSON("$set"<<BSON("is_new" << 0)), Query(boNewAlertCondition));
	m_pSourceController->Update(BSON("$set" << BSON("is_sync" << 1)), QUERY("_id" << boRecord["_id"]));
	return true;
}