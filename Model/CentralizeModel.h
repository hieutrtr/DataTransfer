#pragma once
#include "MongodbModel.h"

class CCentralizeModel : public CMongodbModel
{
public:
	CCentralizeModel();
	virtual ~CCentralizeModel();
	
	virtual Query GetMainDataQuery() = 0;
	virtual BSONObj GetCenRecord(BSONObj boRecord) = 0;
	virtual BSONObj GetCenCondition(BSONObj boRecord) = 0;
};
