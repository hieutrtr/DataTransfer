#pragma once
#include "CentralizeModel.h"

class CCentralizeG8AlertModel : public CCentralizeModel
{
public:
	CCentralizeG8AlertModel(void);
	virtual ~CCentralizeG8AlertModel(void);

	Query GetMainDataQuery();
	BSONObj GetCenRecord(BSONObj boRecord);
	BSONObj GetCenCondition(BSONObj boRecord);
	BSONObj GetOldAlertCondition(BSONObj boRecord);
	BSONObj GetNewAlertCondition(BSONObj boRecord);
};
