#pragma once
#include "CentralizeModel.h"

class CCentralizeZbxAlertModel : public CCentralizeModel
{
public:
	CCentralizeZbxAlertModel(void);
	virtual ~CCentralizeZbxAlertModel(void);

	Query GetMainDataQuery();
	BSONObj GetCenRecord(BSONObj boRecord);
	BSONObj GetCenCondition(BSONObj boRecord);
	BSONObj GetOldAlertCondition(BSONObj boRecord);
	BSONObj GetNewAlertCondition(BSONObj boRecord);
};
