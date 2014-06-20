#pragma once
#include "LogParser.h"
#include "Processor.h"
#include "../Utilities/ZabbixParser.h"

class CUpdateItemLogController;
class CLogModel;

class CUpdateItemLogParser :
	public CLogParser, public CZabbixParser
{
public:
	CUpdateItemLogParser(const string& strConfigFileName);
	CUpdateItemLogParser(const string& strConfigFileName, const string& strLocationGroup);
	virtual ~CUpdateItemLogParser(void);

protected:

	bool Connect();
	void ParseLog();
	vector<CLogModel*> ParseLog(long& lPosition, long lLength, char* pBuffer);

	bool ProcessData(vector<CLogModel*>);
protected:
	CUpdateItemLogController* m_pUpdateItemLogController;
};