#pragma once
#include "MongodbController.h"

class CMAAlertController :
	public CMongodbController
{
public:
	CMAAlertController(void);
	virtual ~CMAAlertController(void);
	bool HideAlertNotInSrcId(string strSrcFrom, vector<string> vStrAlertId);
};
