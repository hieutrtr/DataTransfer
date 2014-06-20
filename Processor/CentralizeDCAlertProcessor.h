#pragma once
#include "CentralizeProcessor.h"

class CCentralizeDCAlertProcessor :
	public CCentralizeProcessor
{
public:
	CCentralizeDCAlertProcessor(const string& strConfigFileName);
	~CCentralizeDCAlertProcessor(void);

protected:
	bool Connect();
	bool ExecuteLateProcess(BSONObj boRecord);
};
