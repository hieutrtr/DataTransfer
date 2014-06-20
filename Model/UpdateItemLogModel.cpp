#include "UpdateItemLogModel.h"
#include "../Common/DBCommon.h"

CUpdateItemLogModel::CUpdateItemLogModel(void)
{
}

CUpdateItemLogModel::~CUpdateItemLogModel(void)
{
}

BSONObj CUpdateItemLogModel::GetBSONModel()
{
	BSONObj boModel;

	boModel = BSON(
		"zabbix_server_id" << m_iZbxServerId <<
		"status" << m_iStatus <<
		"value_type" << m_iValueType <<
		"clock" << m_lClock <<
		"hostid" << m_lHostId <<
		"itemid" << m_lItemId <<
		"serverid" << m_lServerId <<
		"description" << m_strDescription <<
		"key_" << m_strKey <<
		"units" << m_strUnits <<
		"alert_type" << m_strAlertType
		);

	return boModel;
}