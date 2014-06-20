#include "LogParser.h"

class CEventController;

class CEventLogParser :public CLogParser
{
public:
	CEventLogParser(void);
	CEventLogParser(const string& strConfigFileName, const string& strLocationGroup);
	~CEventLogParser(void);
protected:
	map<string, long> CollectFile();
	vector<CLogModel*> ParseLog(const long &lLength, long &lPosition, char* cBuffer);
	void ProceedData(vector<CLogModel*> v_LogModelPtr);
	bool Connect();
	CEventController *m_pEventController;
};