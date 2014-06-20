#include "CSAlertController.h"
#include "../Common/DBCommon.h"

#define CODE_ERROR_SSL_INIT "1"
#define MSG_ERROR_SSL_INIT "Cannot init ssl to dc service"

#define CODE_ERROR_CRYPTO_THREAD_SETUP "2"
#define MSG_ERROR_CRYPTO_THREAD_SETUP "Cannot setup thread mutex for OpenSSL"

#define CODE_ERROR_INIT "3"
#define MSG_ERROR_INIT "Cannot access to CS service"

#define CODE_ERROR_SSL_CLIENT_CONTEXT "4"
#define MSG_ERROR_SSL_CLIENT_CONTEXT "SSL client authentication fail"

#define CODE_ERROR_UPDATE_STATUS_INC "5"
#define MSG_ERROR_UPDATE_STATUS_INC "Cannot call update status inc to CS"
#define RESPONSE_UNSUCCESS "UN Sucessfull"

CCSAlertController::CCSAlertController(void)
{
	m_strTableName = TBL_CS_ALERT;
}

CCSAlertController::~CCSAlertController(void)
{
}

bool CCSAlertController::UpdateINCStatus(BSONObj bsonRecord)
{
	int iResult;
	string strResponse, strItsmStatus, strLog, strRejectMess;
	char *cINCCode, *cITSMCode, *cITSMCloseDate, *cCreatedBy, *cComment;
	short iINCStatusID = 99;
	short *p_iINCStatusID;
	if (bsonRecord.isEmpty())
	{
		return false;
	}
	strItsmStatus = bsonRecord.hasField("itsm_status") ? bsonRecord.getStringField("itsm_status") : "";
	strRejectMess = bsonRecord.hasField("msg") ? bsonRecord.getStringField("msg") : "";
	cINCCode = new char[100];
	cITSMCode = new char[100];
	cITSMCloseDate = new char[100];
	cCreatedBy = new char[100];
	cComment = new char[strRejectMess.size() + 1];
	// ========= Get Inc Status ===========
	if (strItsmStatus.compare("open") == 0)
		iINCStatusID = 24;
	else if (strItsmStatus.compare("closed") == 0)
		iINCStatusID = 26;
	else if (strItsmStatus.compare("reopen") == 0)
		iINCStatusID = 28;
	else if (strItsmStatus.compare("rejected") == 0)
		iINCStatusID = 27;
	else if (strItsmStatus.compare("resolved") == 0)
		iINCStatusID = 25;
	strcpy(cINCCode, bsonRecord.getStringField("ticket_id"));
	strcpy(cITSMCode, bsonRecord.getStringField("itsm_id"));
	strcpy(cCreatedBy, "sdk");
	memcpy(cComment, strRejectMess.c_str(), strRejectMess.size() + 1);
	strcpy(cITSMCloseDate, bsonRecord.getStringField("outage_end"));
	p_iINCStatusID = &iINCStatusID;
	iResult = CAPIUtilities::CallUpdateINCStatusAPI(cINCCode, p_iINCStatusID, cITSMCode, cCreatedBy, cComment, cITSMCloseDate, strResponse);
	//============================Write Log==========================
	strLog = CUtilities::FormatLog(INFO_MSG, "UpdateAlertStt", "CSAlertController", "UpdateCSStatusINC:" + strResponse);
	CUtilities::WriteInfoLog(INFO_MSG, strLog);
	//============================Destroy==========================
	delete[] cINCCode;
	delete[] cITSMCode;
	delete[] cITSMCloseDate;
	delete[] cCreatedBy;
	delete[] cComment;
	if (API_ACTION_ERROR == iResult || CODE_ERROR_INIT == strResponse || CODE_ERROR_UPDATE_STATUS_INC == strResponse
		|| CODE_ERROR_SSL_CLIENT_CONTEXT == strResponse
		|| strResponse.find(RESPONSE_UNSUCCESS) != std::string::npos || strResponse.find("fail") != std::string::npos)
	{
		string strSourceId = bsonRecord.hasField("_id") ? CUtilities::GetMongoObjId(bsonRecord["_id"]) : "";
		string strStatus = bsonRecord.hasField("itsm_status") ? bsonRecord.getStringField("itsm_status") : "";
		string strCurrStatus = bsonRecord.hasField("prev_itsm_status") ? bsonRecord.getStringField("prev_itsm_status") : "";
		string strLog = CUtilities::FormatLog(INFO_MSG, "CCSAlertController", "UpdateINCStatus", "FAIL:" + strSourceId + ": " +
			strCurrStatus + " -> " + strStatus);
		CUtilities::WriteInfoLog(INFO_MSG, strLog);
		return false;
	}
	return true;
}
