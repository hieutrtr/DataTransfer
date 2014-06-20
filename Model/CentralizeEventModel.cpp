#include "CentralizeEventModel.h"
#include "../Common/DBCommon.h"

CCentralizeEventModel::CCentralizeEventModel(void)
{
}

CCentralizeEventModel::~CCentralizeEventModel(void)
{
}

Query CCentralizeEventModel::GetMainDataQuery()
{
	Query queryCondition = QUERY("is_sync" << 0);
	return queryCondition;
}

BSONObj CCentralizeEventModel::GetCenRecord(BSONObj boRecord)
{
	BSONObj boCenRecord, boDefault;
	/*-- Create Default --*/
	boDefault = BSON(
		"is_sync" << 0
		);

	boCenRecord = CMongodbModel::MergeBSONObj(&boDefault, &boRecord);

	return boCenRecord;
}

BSONObj CCentralizeEventModel::GetCenCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"serverid" << boRecord["serverid"] <<
		"eventid" << boRecord["eventid"]
		);
	return boCondition;
}