#pragma once
#include "CentralizeProcessor.h"

class CMapProductController;
class CCentralizeSO6AlertProcessor :
	public CCentralizeProcessor
{
public:
	CCentralizeSO6AlertProcessor(const string& strConfigFileName);
	~CCentralizeSO6AlertProcessor(void);

protected:
	bool Connect();
	bool Save();
	BSONObj CreateBSON();
	string GetSO6Product(string strServerName);
	bool ExecuteLateProcess();
	BSONObj GetAdditionInfo(BSONObj boRecord);
protected:
	vector<string> m_vStrAlertId;
	CMapProductController *m_pMapProductController;
};
