#pragma once
#include "CentralizeModel.h"

class CCentralizeSO6AlertModel : public CCentralizeModel
{
public:
	CCentralizeSO6AlertModel(void);
	virtual ~CCentralizeSO6AlertModel(void);

	Query GetMainDataQuery();
	BSONObj GetCenRecord(BSONObj boRecord);
	BSONObj GetCenCondition(BSONObj boRecord);
};
