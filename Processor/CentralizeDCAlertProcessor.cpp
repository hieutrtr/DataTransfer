#include "CentralizeDCAlertProcessor.h"
#include "../Model/CentralizeDCAlertModel.h"
#include "../Controller/DCAlertController.h"
#include "../Controller/MAAlertController.h"
#include "../Controller/MapProductController.h"
#include "../Common/DBCommon.h"

CCentralizeDCAlertProcessor::CCentralizeDCAlertProcessor(const string& strConfigFileName)
:CCentralizeProcessor(strConfigFileName)
{
	m_pSourceController = new CDCAlertController();
	m_pDesController = new CMAAlertController();
	m_pCentralModel = new CCentralizeDCAlertModel();
}

CCentralizeDCAlertProcessor::~CCentralizeDCAlertProcessor(void)
{
}

bool CCentralizeDCAlertProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterMongodbController(m_pSourceController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pDesController, DB_GROUP_MONGODB_MA);

	return CProcessor::Connect();
}

bool CCentralizeDCAlertProcessor::ExecuteLateProcess(BSONObj boRecord)
{
	auto_ptr<DBClientCursor> ptrNewDataCursor;
	auto_ptr<DBClientCursor> ptrOldDataCursor;
	auto_ptr<DBClientCursor> ptrACKDataCursor;
	BSONObj boOldAlertCondition, boNewAlertCondition, boOldAlert, boNewAlert, boACK;
	CCentralizeDCAlertModel *pCentralCentralizeDCAlertModel = dynamic_cast<CCentralizeDCAlertModel*>(m_pCentralModel);

	boOldAlertCondition = pCentralCentralizeDCAlertModel->GetOldAlertCondition(boRecord);
	boNewAlertCondition = pCentralCentralizeDCAlertModel->GetNewAlertCondition(boRecord);
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
	m_pDesController->Update(BSON("$set" << BSON("is_new" << 0)), Query(boNewAlertCondition));
	m_pSourceController->Update(BSON("$set" << BSON("is_sync" << 0)), QUERY("_id" << boRecord["_id"]));
	return true;
}