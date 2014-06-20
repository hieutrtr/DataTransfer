#pragma once
#include "../Common/Common.h"
#include "../Model/MongodbModel.h"
#include "mongo/client/dbclient.h"
using namespace mongo;

class CConfigFile;
class CMongodbController;
class CMySQLController;
class CMongodbModel;

union Controller {
	CMongodbController* pMongodbController;
	CMySQLController* pMySQLController;
};

typedef vector<Controller > ControllerArray;
typedef map<string, ControllerArray > mapDBGroup2ControllerArray;
typedef vector<CMongodbModel*> MongodbModelArray;

class CProcessor
{
public:
	CProcessor(const string& strConfigFileName);
	virtual ~CProcessor(void);
protected:
	void RegisterMongodbController(CMongodbController* pController, string strDBGroup = "");
	void RegisterMySQLController(CMySQLController* pController, string strDBGroup = "");

	virtual bool Connect();
protected:
	CConfigFile* m_pConfigFile;
	//MongodbControllerArray m_arrMongodbController;
	mapDBGroup2ControllerArray m_mapDBGroup2ControllerArray;

};
