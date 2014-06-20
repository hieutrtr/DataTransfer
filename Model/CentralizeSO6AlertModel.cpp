#include "CentralizeSO6AlertModel.h"
#include "../Common/DBCommon.h"

CCentralizeSO6AlertModel::CCentralizeSO6AlertModel(void)
{
}

CCentralizeSO6AlertModel::~CCentralizeSO6AlertModel(void)
{
}

Query CCentralizeSO6AlertModel::GetMainDataQuery()
{
}

BSONObj CCentralizeSO6AlertModel::GetCenRecord(BSONObj boRecord)
{
	BSONObj boCenRecord;
	string strDescription, strSourceId, strTitle, strProduct,
		strServerName, strContent, strMsgAlert, strPriority, strTmp, strLastObjId;
	long long lClock, lLastClock; // ThaoDT add field lLastClock
	bool bFindSameAlert; //++ThaoDT 2014-03-24

	strPriority = boRecord.getStringField("priority");
	strTmp = CUtilities::ToLowerString(strPriority);
	if (strTmp.compare("notmonitor") == 0 || strTmp.compare("low") == 0)
	{
		return boCenRecord;
	}
	strSourceId = boRecord.getStringField("id");
	lClock = CUtilities::UnixTimeFromString(boRecord.getStringField("updatetime"));
	strServerName = boRecord.getStringField("servername");

	
	/*------------------ Build Record ------------------*/
	boCenRecord = BSON(
		"is_show" << 1 <<
		"source_from" << "SO6" <<
		"source_id" << strSourceId <<
		"clock" << lClock <<
		"priority" << strPriority <<
		"department" << "SO6" <<
		"zbx_host" << strServerName
		);
	/*-----------------------------------------------------------*/

	return boCenRecord;
}

BSONObj CCentralizeSO6AlertModel::GetCenCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"source_id" << boRecord["id"] <<
		"source_from" << "SO6"
		);
	return boCondition;
}