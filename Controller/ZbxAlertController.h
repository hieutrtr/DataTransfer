#pragma once
#include "MongodbController.h"

class CZbxAlertController :
	public CMongodbController
{
public:
	CZbxAlertController(void);
	virtual ~CZbxAlertController(void);
};
