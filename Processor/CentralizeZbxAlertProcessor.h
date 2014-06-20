#pragma once
#include "CentralizeProcessor.h"

class CUpdateItemLogController;
class CCentralizeZbxAlertProcessor :
	public CCentralizeProcessor
{
public:
	CCentralizeZbxAlertProcessor(const string& strConfigFileName);
	~CCentralizeZbxAlertProcessor(void);

protected:
	bool Connect();
	BSONObj GetAdditionInfo(BSONObj boRecord);
	bool ExecuteLateProcess(BSONObj boRecord);

protected:
	CUpdateItemLogController *m_pUpdateItemController;
};
