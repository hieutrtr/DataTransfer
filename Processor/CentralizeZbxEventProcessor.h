#pragma once
#include "CentralizeProcessor.h"

class CTriggerController;
class CServerController;
class CCentralizeZbxEventProcessor :
	public CCentralizeProcessor
{
public:
	CCentralizeZbxEventProcessor(const string& strConfigFileName);
	~CCentralizeZbxEventProcessor(void);

protected:
	bool Connect();
	BSONObj GetAdditionInfo(BSONObj boRecord);
	bool ExecuteLateProcess(BSONObj boRecord);
	bool ExecuteEarlyProcess(BSONObj boRecord);
protected:
	CTriggerController *m_pTriggerLogController;
	CServerController *m_pServerController;
};
