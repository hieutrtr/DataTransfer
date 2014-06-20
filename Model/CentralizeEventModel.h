#pragma once
#include "CentralizeModel.h"

class CCentralizeEventModel : public CCentralizeModel
{
public:
	CCentralizeEventModel(void);
	virtual ~CCentralizeEventModel(void);

	Query GetMainDataQuery();
	BSONObj GetCenRecord(BSONObj boRecord);
	BSONObj GetCenCondition(BSONObj boRecord);
};
