#include "CSUpdateAlertSttProcessor.h"
#include "../Model/CSAlertModel.h"
#include "../Controller/CSAlertController.h"
#include "../Controller/IncidentFollowController.h"
#include "../Common/DBCommon.h"

CCSUpdateAlertSttProcessor::CCSUpdateAlertSttProcessor(const string& strConfigFileName)
:CUpdateAlertSttProcessor(strConfigFileName)
{
	m_pAlertModel = new CCSAlertModel();
	m_pAlertController = new CCSAlertController();
}

CCSUpdateAlertSttProcessor::~CCSUpdateAlertSttProcessor(void)
{
	if (NULL != m_pAlertModel)
	{
		delete m_pAlertModel;
	}
	if (NULL != m_pAlertController)
	{
		delete m_pAlertController;
	}
}

bool CCSUpdateAlertSttProcessor::Connect()
{
	// Register controllers before connecting to database
	RegisterMongodbController(m_pAlertController, DB_GROUP_MONGODB_MA);
	RegisterMySQLController(m_pIncidentFollowController, DB_GROUP_MYSQL_MA);

	return CProcessor::Connect();
}