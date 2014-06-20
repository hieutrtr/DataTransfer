#include "LogParser.h"

class CTriggerController;

class CTriggerLogParser :public CLogParser
{
public:
	CTriggerLogParser(void);
	CTriggerLogParser(const string& strConfigFileName, const string& strLocationGroup);
	~CTriggerLogParser(void);
protected:
	map<string, long> CollectFile();
	vector<CLogModel*> ParseLog(const long &lLength, long &lPosition, char* cBuffer);
	void ProceedData(vector<CLogModel*> v_LogModelPtr);
	bool Connect();
	CTriggerController *m_pTriggerController;
};