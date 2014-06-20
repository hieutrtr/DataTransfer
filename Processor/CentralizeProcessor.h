#pragma once
#include "Processor.h"

class CMongodbController;
class CCentralizeModel;
class CCentrolizeMySQLController;

class CCentralizeProcessor: public CProcessor
{
public:
	CCentralizeProcessor(const string& strConfigFileName);
	virtual ~CCentralizeProcessor();

	void Proceed();
protected:
	virtual bool Connect() = 0;
	/*-- For getting data from another source. Implement in child class */
	virtual BSONObj GetAdditionInfo(BSONObj boRecord) { return BSONObj(); };
	/*-- Doing something before centralization. Be Called in ProcessData Function */
	virtual bool ExecuteEarlyProcess(BSONObj boRecord) { return true; };
	virtual bool ExecuteEarlyProcess() { return true; };
	/*-- Doing something after centralization. Be Called in ProcessData Function */
	virtual bool ExecuteLateProcess(BSONObj boRecord) { return true; };
	virtual bool ExecuteLateProcess() { return true; };

	bool ProcessData();
	bool LoadMainData(auto_ptr<DBClientCursor> &ptrMainDataCursor);
	bool Save(BSONObj boRecord);
	virtual bool Save() { return true; };

protected:
	CMongodbController *m_pSourceController;
	CMongodbController *m_pDesController;
	CCentralizeModel *m_pCentralModel;
	CCentrolizeMySQLController *m_pSourceMySQLController;
};