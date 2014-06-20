#include "LogModel.h"

class CEventModel :public CLogModel
{
public:
	CEventModel();
	~CEventModel();
	BSONObj UniqueQuery(BSONObj boObj);
};