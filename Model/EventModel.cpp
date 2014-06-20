#include "EventModel.h"

CEventModel::CEventModel(void)
{
}

CEventModel::~CEventModel(void)
{
}

BSONObj CEventModel::UniqueQuery(BSONObj boObj)
{
	BSONObj bsonQueryResult = BSON("zabbix_server_id" << boObj["zabbix_server_id"] << "eventid" << boObj["eventid"]);
	return bsonQueryResult;
}