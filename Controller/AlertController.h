#pragma once
#include "MongodbController.h"

class CAlertController :public CMongodbController
{
public:
	CAlertController(void);
	virtual ~CAlertController(void);
	virtual bool UpdateINCStatus(BSONObj bsonRecord){};
};