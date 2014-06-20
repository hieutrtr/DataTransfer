#pragma once
#include "Processor.h"
#include "../Utilities/ZabbixParser.h"

class CLogModel;
class CLogParser : public CProcessor, public CZabbixParser
{
public:
	CLogParser(const string& strConfigFileName, const string& strLocationGroup);
	virtual ~CLogParser(void);

	void Proceed();

protected:
	void ParseLog();
	bool Connect();
	virtual map<string, long> CollectFile() = 0;
	virtual vector<CLogModel*> ParseLog(const long &lLength, long &lPosition, char* cBuffer) = 0;
	virtual void ProceedData(vector<CLogModel*> v_LogModelPtr) = 0;

private:
	char* ReadBuffer(long &lLength, const string& strFileName);
};
