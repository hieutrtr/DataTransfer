#include "Processor.h"
#include "../Config/ConfigFile.h"
#include "../Controller/MongodbController.h"
#include "../Controller/MySQLController.h"
#include "../Common/DBCommon.h"

CProcessor::CProcessor(const string& strConfigFileName)
{
	CConfigFile::GetInstance(strConfigFileName);
}

CProcessor::~CProcessor(void)
{
	mapDBGroup2ControllerArray::iterator mit;
	for (mit = m_mapDBGroup2ControllerArray.begin(); mit != m_mapDBGroup2ControllerArray.end(); mit++) {
		m_mapDBGroup2ControllerArray[mit->first].clear();
	}
	m_mapDBGroup2ControllerArray.clear();
}

void CProcessor::RegisterMongodbController(CMongodbController* pController, string strDBGroup)
{
	cout << "1 controller registers for group " << strDBGroup << endl;
	if (NULL != pController && "" != strDBGroup)
	{
		Controller uController;
		uController.pMongodbController = pController;
		m_mapDBGroup2ControllerArray[strDBGroup].push_back(uController);
	}
}

void CProcessor::RegisterMySQLController(CMySQLController* pController, string strDBGroup)
{
	cout << "1 controller registers for group " << strDBGroup << endl;
	if (NULL != pController && "" != strDBGroup)
	{
		Controller uController;
		uController.pMySQLController = pController;
		m_mapDBGroup2ControllerArray[strDBGroup].push_back(uController);
	}
}

bool CProcessor::Connect()
{
	bool bTemp = false;
	bool bResult = true;
	string strDBGroup;
	ControllerArray vController;
	//====================================Connection==================================
	if (NULL == CConfigFile::GetInstance())
	{
		return false;
	}

	mapDBGroup2ControllerArray::iterator mit;
	for (mit = m_mapDBGroup2ControllerArray.begin(); mit != m_mapDBGroup2ControllerArray.end(); mit++) {

		// Repeat if you also want to iterate through the second map.
		strDBGroup	= mit->first;
		vController = mit->second;

		CConfigFile::GetInstance()->SetActiveDBGroup(strDBGroup);
		ConnectInfo CInfo = CDBUtilities::GetConnectInfo();
		
		cout << "Trying connect controllers to group [" << strDBGroup << "] ..." << endl;
		ControllerArray::iterator it;
		cout << "[Num of registered controllers] " << vController.size() << endl;
		cout << "[DBHost] " << CInfo.strHost << endl;
		cout << "[DBType] " << CInfo.strDBType << endl;

		for (int i = 0; i<DB_RECONNECT_TIME; i++)
		{
			it = vController.begin();

			// Connect all controllers to database
			while (it != vController.end())
			{
				Controller uController = *it;
				//pController = *it;
				if (CInfo.strDBType == MONGODB)
				{
					bTemp = (uController.pMongodbController)->Connect(CInfo);
				}
				else if (CInfo.strDBType == MYSQL)
				{
					bTemp = (uController.pMySQLController)->Connect(CInfo);
				}

				if (!bTemp)
				{
					CUtilities::WriteErrorLog(ERROR_MSG, CUtilities::FormatLog(ERROR_MSG, "CProcessor", "Connect()", "Connection Fail"));
					sleep(DB_CONNECT_RETRY_INTERVAL);

					// Mark as false if one controller could not connect to database
					bResult = false;
					break;
				}
				else
				{
					bResult = true;
				}
				it++;
			}
			// All controllers were connnected to database
			if (bResult)
			{
				cout << "[" << strDBGroup << "] All controllers were connected successfully" << endl;
				break;
				
			}
			else
			{
				cout << "[" << strDBGroup << "] One of controllers could not connect to DB. Retrying ... " << endl;
				continue;
			}
		}
		
	}

	return bResult;
}