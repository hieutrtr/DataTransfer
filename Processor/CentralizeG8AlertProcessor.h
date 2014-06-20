#pragma once
#include "CentralizeProcessor.h"

class CMapProductController;
class CCentralizeG8AlertProcessor :
	public CCentralizeProcessor
{
public:
	CCentralizeG8AlertProcessor(const string& strConfigFileName);
	~CCentralizeG8AlertProcessor(void);

protected:
	bool Connect();
	BSONObj GetAdditionInfo(BSONObj boRecord);
	bool ExecuteLateProcess(BSONObj boRecord);

protected:
	CMapProductController *m_pMapProductController;
};
