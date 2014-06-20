#include "LogModel.h"

class CTriggerModel :public CLogModel
{
public:
	CTriggerModel();
	~CTriggerModel();
	BSONObj UniqueQuery(BSONObj boObj);
};