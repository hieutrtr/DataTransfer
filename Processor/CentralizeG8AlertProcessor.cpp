#include "CentralizeG8AlertProcessor.h"
#include "../Model/CentralizeG8AlertModel.h"
#include "../Controller/G8AlertController.h"
#include "../Controller/MAAlertController.h"
#include "../Controller/MapProductController.h"
#include "../Common/DBCommon.h"

CCentralizeG8AlertProcessor::CCentralizeG8AlertProcessor(const string& strConfigFileName)
:CCentralizeProcessor(strConfigFileName)
{
	m_pSourceController = new CG8AlertController();
	m_pDesController = new CMAAlertController();
	m_pCentralModel = new CCentralizeG8AlertModel();
	m_pMapProductController = new CMapProductController();
}

CCentralizeG8AlertProcessor::~CCentralizeG8AlertProcessor(void)
{
	if (NULL != m_pMapProductController)
	{
		delete m_pMapProductController;
	}
}

bool CCentralizeG8AlertProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterMongodbController(m_pSourceController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pDesController, DB_GROUP_MONGODB_MA);
	RegisterMongodbController(m_pMapProductController, DB_GROUP_MONGODB_MA);

	return CProcessor::Connect();
}

BSONObj CCentralizeG8AlertProcessor::GetAdditionInfo(BSONObj boRecord)
{
	auto_ptr<DBClientCursor> ptrMapProductCursor;
	auto_ptr<DBClientCursor> ptrMapDataCursor;
	BSONObj boAddtionInfo, boMapProductRecord;
	string strProduct, strItsmId, strTitle, strDescription, strAlertMsg, strTmp;

	/*-- Get Map Product Info --*/
	Query queryCondition = QUERY("source" << "G8" << "src_product" << boRecord["product"]);
	ptrMapProductCursor = m_pMapProductController->Find(queryCondition);
	if ((ptrMapProductCursor.get() != NULL) && (ptrMapProductCursor->more()))
	{
		boMapProductRecord = ptrMapProductCursor->nextSafe();
		if (boMapProductRecord.hasField("itsm_product"))
		{
			strProduct = boMapProductRecord.getStringField("itsm_product");
		}
	}
	if (!strProduct.empty() && strProduct.compare("EOO") != 0)
		strTmp = "[" + strProduct + "] ";
	else
		strTmp = "";
	/*-------------------------------------------------*/
	strTitle = boRecord.hasField("title") ? boRecord.getStringField("title") : "";
	strDescription = boRecord.hasField("description") ? boRecord.getStringField("description") : "";
	strItsmId = boRecord.hasField("itsm_id") ? boRecord.getStringField("itsm_id") : "";

	if (!strItsmId.empty() && strItsmId.compare("EOO") != 0)
		strItsmId = "Incident " + strItsmId + " - ";
	else
		strItsmId = "";

	strAlertMsg = strItsmId + strTmp + strTitle + " " + strDescription;
	boAddtionInfo = BSON("product" << strProduct << "alert_message" << strAlertMsg);

	return boAddtionInfo.copy();
}

bool CCentralizeG8AlertProcessor::ExecuteLateProcess(BSONObj boRecord)
{
	auto_ptr<DBClientCursor> ptrNewDataCursor;
	auto_ptr<DBClientCursor> ptrOldDataCursor;
	auto_ptr<DBClientCursor> ptrACKDataCursor;
	BSONObj boOldAlertCondition, boNewAlertCondition, boOldAlert, boNewAlert, boACK;
	CCentralizeG8AlertModel *pCentralCentralizeG8AlertModel = dynamic_cast<CCentralizeG8AlertModel*>(m_pCentralModel);

	boOldAlertCondition = pCentralCentralizeG8AlertModel->GetOldAlertCondition(boRecord);
	boNewAlertCondition = pCentralCentralizeG8AlertModel->GetNewAlertCondition(boRecord);
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
	m_pSourceController->Update(BSON("$set" << BSON("operation" << 0)), QUERY("_id" << boRecord["_id"]));
	return true;
}