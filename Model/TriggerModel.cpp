#include "TriggerModel.h"

CTriggerModel::CTriggerModel(void)
{
}

CTriggerModel::~CTriggerModel(void)
{
}

BSONObj CTriggerModel::UniqueQuery(BSONObj boObj)
{
	BSONObj bsonQueryResult = BSON("zabbix_server_id" << boObj["zabbix_server_id"] << "triggerid" << boObj["triggerid"]);
	return bsonQueryResult;
}