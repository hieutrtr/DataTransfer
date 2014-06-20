#include "CentralizeProcessor.h"
#include "../Controller/MongodbController.h"
#include "../Controller/CentrolizeMySQLController.h"
#include "../Model/CentralizeModel.h"

CCentralizeProcessor::CCentralizeProcessor(const string& strConfigFileName)
:CProcessor(strConfigFileName)
{
}

CCentralizeProcessor::~CCentralizeProcessor()
{
	if (NULL != m_pSourceMySQLController)
	{
		delete m_pSourceMySQLController;
	}
	if (NULL != m_pSourceController)
	{
		delete m_pSourceController;
	}
	if (NULL != m_pDesController)
	{
		delete m_pDesController;
	}
	if (NULL != m_pCentralModel)
	{
		delete m_pCentralModel;
	}
}

void CCentralizeProcessor::Proceed()
{
	if (Connect())
	{
		while (true)
		{
			if (!ProcessData())
			{
				sleep(CENTRALIZE_INTERVAL);
			}
		}
	}
}

bool CCentralizeProcessor::ProcessData()
{
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrMainDataCursor;
	if (LoadMainData(ptrMainDataCursor))
	{
		/*-- Mongodb Source --*/
		if (NULL != m_pSourceController) 
		{
			while (ptrMainDataCursor->more())
			{
				boRecord = ptrMainDataCursor->nextSafe();
				if (ExecuteEarlyProcess(boRecord))
				{
					if (Save(boRecord))
					{
						ExecuteLateProcess(boRecord);
					}
				}
			}
		}
		/*-- MySQL Source --*/
		else if (NULL != m_pSourceMySQLController)
		{
			while (m_pSourceMySQLController->NextRow())
			{
				if (ExecuteEarlyProcess())
				{
					Save();
				}
			}
			ExecuteLateProcess();
		}
	}
}

bool CCentralizeProcessor::LoadMainData(auto_ptr<DBClientCursor> &ptrMainDataCursor)
{
	Query boMainDataQuery;
	/*-- Mongodb Source --*/
	if (NULL != m_pSourceController)
	{
		boMainDataQuery = m_pCentralModel->GetMainDataQuery();
		ptrMainDataCursor = m_pSourceController->Find(boMainDataQuery);
		if ((ptrMainDataCursor.get() != NULL) && (ptrMainDataCursor->more()))
		{
			return true;
		}
	}
	/*-- MySQL Source --*/
	else if (NULL != m_pSourceMySQLController)
	{
		if (m_pSourceMySQLController->Find())
		{
			return true;
		}
	}
	return false;
}

bool CCentralizeProcessor::Save(BSONObj boRecord)
{
	string strLog;
	BSONObj boCenRecord, boCenCondition, boAdditionInfo;

	/*-- Build Central Record By Model Function --*/
	boCenRecord = m_pCentralModel->GetCenRecord(boRecord);
	boCenCondition = m_pCentralModel->GetCenCondition(boRecord);

	if (boCenRecord.isEmpty())
	{
		strLog = CUtilities::FormatLog(ERROR_MSG, "CCentralizeProcessor", "Save", "SourceRecordFail:" + boRecord.toString());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
		return false;
	}

	/*-- Get Addition Info --*/
	boAdditionInfo = GetAdditionInfo(boRecord);
	if (!boAdditionInfo.isEmpty())
	{
		boCenRecord = CMongodbModel::MergeBSONObj(&boCenRecord, &boAdditionInfo);
	}


	/*-- Insert Centralize --*/
	if (m_pDesController->Insert(boCenRecord, boCenCondition))
	{
		return true;
	}
	strLog = CUtilities::FormatLog(ERROR_MSG, "CCentralizeProcessor", "Save", "InsertFail:" + boRecord.toString());
	CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	return false;
}

