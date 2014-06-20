#pragma once
#include "MongodbModel.h"
#include "../Utilities/TextParser.h"

class CLogModel : public CMongodbModel, public CTextParser
{
public:
	CLogModel(void);
	virtual ~CLogModel(void);

	/* For common */
	virtual void Renew(){};
	virtual BSONObj GetBSONModel(){};
};
