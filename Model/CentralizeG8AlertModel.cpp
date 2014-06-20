#include "CentralizeG8AlertModel.h"
#include "../Common/DBCommon.h"

CCentralizeG8AlertModel::CCentralizeG8AlertModel(void)
{
}

CCentralizeG8AlertModel::~CCentralizeG8AlertModel(void)
{
}

Query CCentralizeG8AlertModel::GetMainDataQuery()
{
	Query queryCondition = QUERY("operation" << 4);
	return queryCondition;
}

BSONObj CCentralizeG8AlertModel::GetCenRecord(BSONObj boRecord)
{
	BSONObj boCenRecord, boDefault;
	map<string, string> mapCSAlertField;

	boDefault = BSON(
		"is_show" << 1 <<
		"source_from" << "G8" <<
		"source_id" << CUtilities::GetMongoObjId(boRecord["_id"].toString(false)) <<
		"department" << "G8" <<
		"is_new" << 1
		);

	mapCSAlertField["clock"] = "outage_start";
	mapCSAlertField["ticket_id"] = "ticket_id";
	mapCSAlertField["title"] = "title";
	mapCSAlertField["description"] = "description";
	mapCSAlertField["product"] = "product";
	mapCSAlertField["attachments"] = "attachments";
	mapCSAlertField["num_of_case"] = "num_of_case";
	mapCSAlertField["itsm_incident_id"] = "itsm_id";

	boCenRecord = CMongodbModel::ConvertBSONObj(boRecord, mapCSAlertField);
	boCenRecord = CMongodbModel::MergeBSONObj(&boDefault, &boCenRecord);

	return boCenRecord;
}

BSONObj CCentralizeG8AlertModel::GetCenCondition(BSONObj boRecord)
{
	BSONObj boCenRecord;
	return boCenRecord.copy();
}

BSONObj CCentralizeG8AlertModel::GetOldAlertCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"source_id" << CUtilities::GetMongoObjId(boRecord["_id"].toString(false)) <<
		"source_from" << "G8" <<
		"is_new" << 0 <<
		"is_show" << BSON("$in" << BSON_ARRAY(0 << 1))
		);
	return boCondition;
}

BSONObj CCentralizeG8AlertModel::GetNewAlertCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"source_id" << CUtilities::GetMongoObjId(boRecord["_id"].toString(false)) <<
		"source_from" << "G8" <<
		"is_new" << 1
		);
	return boCondition;
}