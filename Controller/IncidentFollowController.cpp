#include "IncidentFollowController.h"
#include "../Common/DBCommon.h"


CIncidentFollowController::CIncidentFollowController(void)
{
}

CIncidentFollowController::~CIncidentFollowController(void)
{
}

bool CIncidentFollowController::FindIncidentInDay()
{
	try{
		string strQuery = "SELECT * FROM `incident_follow` WHERE `itsm_last_update_time` > DATE_SUB(NOW(), INTERVAL 1 DAY)";
		SelectQuery(strQuery.c_str());
		if (m_pResult->row_count == 0)
		{
			return false;
		}
		return true;
	}
	catch (exception& ex)
	{
		string strLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "IncidentFollowController", "FindIncidentInDay", strErrorMess.str());
		CUtilities::WriteErrorLog(strLog);
	}
}

bool CIncidentFollowController::FindIncidentOpen()
{
	try{
		string strQuery = "SELECT *, UNIX_TIMESTAMP(outage_start) AS unix_outage_start,`outage_end` FROM `incident_follow` WHERE `status` = 'Open' AND `auto_update_impact_level` != 1 AND `outage_end` IS NULL";
		SelectQuery(strQuery.c_str());
		if (m_pResult->row_count == 0)
		{
			return false;
		}
		return true;
	}
	catch (exception& ex)
	{
		string strLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "IncidentFollowController", "FindIncidentInDay", strErrorMess.str());
		CUtilities::WriteErrorLog(strLog);
	}
}

bool CIncidentFollowController::FindIncidentHighLevelWithoutSEReport()
{
	try{
		string strQuery = "SELECT * , UNIX_TIMESTAMP(outage_start) AS unix_outage_start FROM `incident_follow` WHERE `status` = 'Open' AND `impact_level` IN (1, 2) AND `se_reported` IS NULL OR `se_reported` != '1'";
		SelectQuery(strQuery.c_str());
		if (m_pResult->row_count == 0)
		{
			return false;
		}
		return true;
	}
	catch (exception& ex)
	{
		string strLog;
		stringstream strErrorMess;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "IncidentFollowController", "FindIncidentInDay", strErrorMess.str());
		CUtilities::WriteErrorLog(strLog);
	}
}
