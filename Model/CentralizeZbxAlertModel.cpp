#include "CentralizeZbxAlertModel.h"
#include "../Common/DBCommon.h"

CCentralizeZbxAlertModel::CCentralizeZbxAlertModel(void)
{
}

CCentralizeZbxAlertModel::~CCentralizeZbxAlertModel(void)
{
}

Query CCentralizeZbxAlertModel::GetMainDataQuery()
{
	Query queryCondition = QUERY("is_sync"<<0);
	return queryCondition;
}

BSONObj CCentralizeZbxAlertModel::GetCenRecord(BSONObj boRecord)
{
	BSONObj boCenRecord, boDefault;
	map<string, string> mapZbxAlertField;
	long long lCreateDate;
	lCreateDate = atol(CUtilities::GetCurrTimeStamp().c_str());
	/*-- Create Default --*/
	boDefault = BSON(
		"ack_msg" << "" <<
		"affected_deals" << "" <<
		"create_date" << lCreateDate <<
		"external_status" << "" <<
		"internal_status" << "" <<
		"is_acked" << 0 <<
		"itsm_incident_id" << "" <<
		"level" << 0 <<
		"num_of_case" << 0 <<
		"priority" << "" <<
		"source_from" << "Zabbix" <<
		"source_id" << CUtilities::GetMongoObjId(boRecord["_id"].toString(false)) <<
		"ticket_id" << "" <<
		"title" << "" <<
		"update_date" << "" <<
		"is_new" << 1
		);

	/*-- Create Maping Field --*/
	mapZbxAlertField["clock"] = "clock";
	mapZbxAlertField["department"] = "cmdb_department_alias";
	mapZbxAlertField["product"] = "cmdb_product_alias";
	mapZbxAlertField["alert_message"] = "description";
	mapZbxAlertField["description"] = "description";
	mapZbxAlertField["zabbix_trigger_description"] = "description";
	mapZbxAlertField["zabbix_eventid"] = "eventid";
	mapZbxAlertField["zbx_host"] = "host";
	mapZbxAlertField["zabbix_hostid"] = "hostid";
	mapZbxAlertField["zabbix_itemid"] = "itemid";
	mapZbxAlertField["zabbix_itemname"] = "key_";
	mapZbxAlertField["zbx_maintenance"] = "maintenance";
	mapZbxAlertField["zabbix_trigger_priority"] = "priority";
	mapZbxAlertField["zabbix_server_id"] = "serverid";
	mapZbxAlertField["is_show"] = "status";
	mapZbxAlertField["zabbix_triggerid"] = "triggerid";
	mapZbxAlertField["zbx_zabbix_server_id"] = "zabbix_server_id";

	boCenRecord = CMongodbModel::ConvertBSONObj(boRecord, mapZbxAlertField);
	boCenRecord = CMongodbModel::MergeBSONObj(&boDefault, &boCenRecord);

	return boCenRecord;
}

BSONObj CCentralizeZbxAlertModel::GetCenCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"zabbix_server_id" << boRecord["serverid"] <<
		"zabbix_eventid" << boRecord["eventid"]
		);
	return boCondition;
}

BSONObj CCentralizeZbxAlertModel::GetOldAlertCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"zabbix_server_id" << boRecord["serverid"] <<
		"zabbix_triggerid" << boRecord["triggerid"] <<
		"is_new" << 0 <<
		"is_show" << BSON("$in" << BSON_ARRAY(0 << 1))
		);
	return boCondition;
}

BSONObj CCentralizeZbxAlertModel::GetNewAlertCondition(BSONObj boRecord)
{
	BSONObj boCondition = BSON(
		"zabbix_server_id" << boRecord["serverid"] <<
		"zabbix_triggerid" << boRecord["triggerid"] <<
		"is_new" << 1
		);
	return boCondition;
}