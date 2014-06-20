#pragma once
#include "MongodbController.h"

class CUpdateItemLogController :
	public CMongodbController
{
public:
	CUpdateItemLogController(void);
	virtual ~CUpdateItemLogController(void);
};
