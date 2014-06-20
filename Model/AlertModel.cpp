#include "AlertModel.h"
#include "../Common/DBCommon.h"

CAlertModel::CAlertModel(void)
{
}

CAlertModel::~CAlertModel(void)
{
}

void CAlertModel::Load(AlertInfo sAlertInf)
{
	BSONObj boAlertOID = BSON("_id" << OID(sAlertInf.strSourceId));
	m_beOID = boAlertOID["_id"];
	m_strComment = sAlertInf.strMSG;
	m_strStatus = sAlertInf.strStatus;
	m_strOutageEnd = sAlertInf.strOutageEnd;
	m_iStatus = sAlertInf.iStatus;
}

void CAlertModel::Load(BSONObj boAlert)
{
	m_strCurrStatus = boAlert.hasField("itsm_status") ? boAlert.getStringField("itsm_status") : "";
	m_strTicketId = boAlert.hasField("ticket_id") ? boAlert.getStringField("ticket_id") : "";
	m_strITSMId = boAlert.hasField("itsm_id") ? boAlert.getStringField("itsm_id") : "";
	m_iItsmSttNoti = boAlert.hasField("itsm_status_notified") ? boAlert.getIntField("itsm_status_notified") : 0;
}

BSONObj CAlertModel::GetRecordBson()
{
	BSONObj boRecord;
	string strCurrStatusTmp, strStatusTmp;
	strCurrStatusTmp = CUtilities::ToLowerString(m_strCurrStatus);
	strStatusTmp = CUtilities::ToLowerString(m_strStatus);
	if (m_strOutageEnd.empty())
	{
		if (strCurrStatusTmp.compare(strStatusTmp) == 0)
		{
			return BSONObj();
		}
		m_iItsmSttNoti = 1;
	}
	else if (1 == m_iItsmSttNoti)
	{
		m_iItsmSttNoti = 0;
		m_strStatus = "closed";
	}
	else
	{
		return BSONObj();
	}
	boRecord = BSON(
		"_id" << m_beOID
		<< "msg" << m_strComment
		<< "itsm_id" << m_strITSMId
		<< "ticket_id" << m_strTicketId
		<< "outage_end" << m_strOutageEnd
		<< "itsm_status_notified" << m_iItsmSttNoti
		<< "itsm_status" << m_strStatus
		<< "prev_itsm_status" << m_strCurrStatus
		);
	return boRecord;
}
BSONObj CAlertModel::GetAlertStatus()
{
	BSONObj boAlertStatus;
	boAlertStatus = BSON("$set" << BSON(
		"itsm_status" << m_strStatus
		<< "itsm_status_notified" << m_iItsmSttNoti
		<< "status" << m_iStatus
		));
	return boAlertStatus;
}