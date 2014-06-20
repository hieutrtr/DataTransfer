#include "MAAlertController.h"
#include "../Common/DBCommon.h"

CMAAlertController::CMAAlertController(void)
{
	m_strTableName = TBL_MA_ALERT;
}

CMAAlertController::~CMAAlertController(void)
{
}

bool CMAAlertController::HideAlertNotInSrcId(string strSrcFrom, vector<string> vStrAlertId)
{

	BSONArrayBuilder babAlertId;
	Query queryCond;
	BSONObj boRecord;

	for (int i = 0; i < vStrAlertId.size(); i++){
		babAlertId << vStrAlertId[i];
	}

	queryCond = QUERY("source_id" << BSON("$nin" << babAlertId.arr()) << "source_from" << strSrcFrom << "is_show" << 1);
	boRecord = BSON("$set" << BSON("is_show" << 0));
	cout << "queryCond:" << queryCond << endl;
	return Update(boRecord, queryCond);
}