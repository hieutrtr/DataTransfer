#pragma once
#include "MySQLController.h"
#include "../Common/Common.h"

class CIncidentFollowController :public CMySQLController
{
public:
	CIncidentFollowController(void);
	~CIncidentFollowController(void);

	bool FindIncidentInDay();
	bool FindIncidentOpen();
	bool FindIncidentHighLevelWithoutSEReport();
	void ResetModel();
};

