#pragma once
#include "AlertController.h"

class CCSAlertController : public CAlertController
{
public:
	CCSAlertController(void);
	~CCSAlertController(void);

	bool UpdateAlertStatus(Query queryCondition, BSONObj bsonRecord);
	bool UpdateCSImpact(Query queryCondition, BSONObj bsonRecord);
	bool UpdateCSReject(Query queryCondition);
	bool UpdateINCStatus(BSONObj bsonRecord);
};