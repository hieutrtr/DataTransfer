#include "CentralizeDCAlertModel.h"
#include "../Common/DBCommon.h"

CCentralizeDCAlertModel::CCentralizeDCAlertModel(void)
{
}

CCentralizeDCAlertModel::~CCentralizeDCAlertModel(void)
{
}

Query CCentralizeDCAlertModel::GetMainDataQuery()
{
	Query queryCondition = QUERY("is_sync" << 1);
	return queryCondition;
}

BSONObj CCentralizeDCAlertModel::GetCenRecord(BSONObj boRecord)
{
	BSONObj boCenRecord, boDefault;
	map<string, string> mapCSAlertField;
	int iIsShow;
	string strStatus, strDescription, strHostService;

	strStatus = boRecord.hasField("status") ? boRecord.getStringField("status") : "";
	strStatus = CUtilities::ToUpperString(strStatus);
	iIsShow = 1;
	if (strStatus.compare("OK") == 0)
	{
		iIsShow = 0;
	}
	strHostService = boRecord.hasField("host_service") ? boRecord.getStringField("host_service") : "";
	strDescription = boRecord.hasField("description") ? boRecord.getStringField("description") : "";
	strDescription = strDescription + "_" + strHostService + "_" + strStatus;
	boDefault = BSON(
		"is_show" << iIsShow <<
		"source_from" << "DC" <<
		"source_id" << CUtilities::GetMongoObjId(boRecord["_id"].toString(false)) <<
		"department" << "DC" <<
		"description" << strDescription <<
		"is_new" << 1 <<
		"alert_message" << strDescription <<
		"clock" << atoll(CUtilities::GetCurrTimeStamp().c_str())
		);
	mapCSAlertField["title"] = "description";
	mapCSAlertField["zbx_host"] = "host_service";

	boCenRecord = CMongodbModel::ConvertBSONObj(boRecord, mapCSAlertField);
	boCenRecord = CMongodbModel::MergeBSONObj(&boDefault, &boCenRecord);

	return boCenRecord;
}

BSONObj CCentralizeDCAlertModel::GetCenCondition(BSONObj boRecord)
{
	BSONObj boCenRecord;
	return boCenRecord.copy();
}

BSONObj CCentralizeDCAlertModel::GetOldAlertCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"source_id" << CUtilities::GetMongoObjId(boRecord["_id"].toString(false)) <<
		"source_from" << "DC" <<
		"is_new" << 0 <<
		"is_show" << BSON("$in" << BSON_ARRAY(0 << 1))
		);
	return boCondition;
}

BSONObj CCentralizeDCAlertModel::GetNewAlertCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"source_id" << CUtilities::GetMongoObjId(boRecord["_id"].toString(false)) <<
		"source_from" << "DC" <<
		"is_new" << 1
		);
	return boCondition;
}