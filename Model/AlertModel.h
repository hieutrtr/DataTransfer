#pragma once
#include "MongodbModel.h"
struct AlertInfo
{
	string strSourceId;
	string strStatus;
	int iStatus;
	string strOutageEnd;
	string strMSG;
};
class CAlertModel : public CMongodbModel
{
public:
	CAlertModel(void);
	virtual ~CAlertModel(void);
	virtual void Load(AlertInfo sAlertInf);
	virtual void Load(BSONObj boAlert);
	virtual BSONObj GetRecordBson();
	virtual BSONObj GetAlertStatus();
protected:
	string m_strTicketId;
	string m_strITSMId;
	string m_strOutageEnd;
	string m_strStatus;
	string m_strCurrStatus;
	string m_strComment;
	int m_iStatus;
	int m_iItsmSttNoti;
};