#pragma once
#include "CentralizeModel.h"

class CCentralizeDCAlertModel : public CCentralizeModel
{
public:
	CCentralizeDCAlertModel(void);
	virtual ~CCentralizeDCAlertModel(void);

	Query GetMainDataQuery();
	BSONObj GetCenRecord(BSONObj boRecord);
	BSONObj GetCenCondition(BSONObj boRecord);
	BSONObj GetOldAlertCondition(BSONObj boRecord);
	BSONObj GetNewAlertCondition(BSONObj boRecord);
};
