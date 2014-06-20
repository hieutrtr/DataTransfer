#pragma once
#include "UpdateAlertSttProcessor.h"

class CCSUpdateAlertSttProcessor :
	public CUpdateAlertSttProcessor
{
public:
	CCSUpdateAlertSttProcessor(const string& strConfigFileName);
	~CCSUpdateAlertSttProcessor();

protected:
	bool Connect();
};
