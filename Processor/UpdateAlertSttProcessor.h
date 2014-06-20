#pragma once
#include "Processor.h"

class CAlertController;
class CAlertModel;
class CIncidentFollowController;
class CSyncProcessData;
class CConfigFile;
struct ConnectInfo;
struct AlertInfo;

class CUpdateAlertSttProcessor: public CProcessor
{
public:
	CUpdateAlertSttProcessor(const string& strConfigFileName);
	virtual ~CUpdateAlertSttProcessor();
	void Proceed();

protected:
	/////////////Function//////////////
	void UpdateAlertStatus(AlertInfo sAlertInf);
	//////////////////////////////////////////////

	CAlertModel *m_pAlertModel;
	CAlertController *m_pAlertController;
	CIncidentFollowController *m_pIncidentFollowController;
};