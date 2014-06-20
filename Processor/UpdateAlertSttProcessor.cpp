#include "UpdateAlertSttProcessor.h"

#include "../Controller/AlertController.h"
#include "../Model/AlertModel.h"
#include "../Model/JsonModel.h"
#include "../Controller/IncidentFollowController.h"
#include "../Config/ConfigFile.h"
#include "../Common/DBCommon.h"

CUpdateAlertSttProcessor::CUpdateAlertSttProcessor(const string& strConfigFileName)
:CProcessor(strConfigFileName)
{
	m_pIncidentFollowController = new CIncidentFollowController();
}

CUpdateAlertSttProcessor::~CUpdateAlertSttProcessor(void)
{
	if (NULL != m_pAlertModel)
	{
		delete m_pAlertModel;
	}
	if (NULL != m_pAlertController)
	{
		delete m_pAlertController;
	}
	if (NULL != m_pIncidentFollowController)
	{
		delete m_pIncidentFollowController;
	}
}

void CUpdateAlertSttProcessor::Proceed()
{
	string strJsonSourceInfo, strLog; //
	CJsonModel objJsonModel;
	AlertInfo sAlertInf;
	int nSize;

	if (!Connect())
	{
		return;
	}
	m_pIncidentFollowController->SetNameUTF8();
	while (true)
	{
		if (!m_pIncidentFollowController->FindIncidentInDay()){
			sleep(10);
			continue;
		}
		while (m_pIncidentFollowController->NextRow())
		{
			//===============Json SourceInfo===============
			strJsonSourceInfo = m_pIncidentFollowController->FetchString("linked_alerts");
			if (strJsonSourceInfo.empty() || strJsonSourceInfo.compare("[]") == 0)
				continue;
			objJsonModel.AppendJson(strJsonSourceInfo);
			nSize = objJsonModel.GetSize();
			if (nSize == 0)
				continue;
			//=============================================
			sAlertInf.strOutageEnd = CUtilities::ToLowerString(m_pIncidentFollowController->FetchString("outage_end"));
			sAlertInf.strStatus = CUtilities::ToLowerString(m_pIncidentFollowController->FetchString("status"));
			sAlertInf.strMSG = m_pIncidentFollowController->FetchString("rejected_reason");
			// =========Get Inc Status ===========
			if (sAlertInf.strStatus.compare("open") == 0)
				sAlertInf.iStatus = RAW_ALERT_STATUS_INIT;
			else if (sAlertInf.strStatus.compare("closed") == 0)
				sAlertInf.iStatus = RAW_ALERT_STATUS_ITSM_CLOSED;
			else if (sAlertInf.strStatus.compare("reopen") == 0)
				sAlertInf.iStatus = RAW_ALERT_STATUS_ITSM_REOPEN;
			else if (sAlertInf.strStatus.compare("rejected") == 0)
				sAlertInf.iStatus = RAW_ALERT_STATUS_ITSM_REJECTED;
			else if (sAlertInf.strStatus.compare("resolved") == 0)
				sAlertInf.iStatus = RAW_ALERT_STATUS_ITSM_RESOLVED;
			//==========================Update Alert status from ITSM=======================
			for (int i = 0; i<nSize; i++)
			{
				sAlertInf.strSourceId = CUtilities::RemoveBraces(objJsonModel.toString(i, "src_id"));
				UpdateAlertStatus(sAlertInf);
			}
			objJsonModel.Destroy();
		}
		//===========Destroy============
		sleep(60);
	}
}

void CUpdateAlertSttProcessor::UpdateAlertStatus(AlertInfo sAlertInf)
{
	string strCurrStatus, strTicketId, strItsmId, strLog;
	int iItsmSttNoti;
	BSONObj boRecord;
	auto_ptr<DBClientCursor> ptrResultCursor = auto_ptr<DBClientCursor>();

	m_pAlertModel->Load(sAlertInf);
	if (m_pAlertController->Find(ptrResultCursor, m_pAlertModel->GetObjectIdQuery())){
		if (ptrResultCursor->more())
		{
			boRecord = ptrResultCursor->nextSafe();
			m_pAlertModel->Load(boRecord);
			// ============================Outage-End is empty==========================
			if (m_pAlertController->UpdateINCStatus(m_pAlertModel->GetRecordBson())) // API Update Status from Inc
			{
				m_pAlertController->Update(m_pAlertModel->GetAlertStatus(), m_pAlertModel->GetObjectIdQuery());
				strCurrStatus = boRecord.hasField("itsm_status") ? boRecord.getStringField("itsm_status") : "";
				strLog = CUtilities::FormatLog(INFO_MSG, "UpdateAlertStt", "ProcessCSUpdate_Call_API", sAlertInf.strSourceId + ": " +
					strCurrStatus + " -> " + sAlertInf.strStatus);
				CUtilities::WriteInfoLog(INFO_MSG, strLog);
			}
		}
	}
}