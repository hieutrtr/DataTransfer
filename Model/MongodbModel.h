#pragma once
#include "../Common/Common.h"
#include "mongo/client/dbclient.h"
#include "mongo/bson/bsonobjbuilder.h"
using namespace mongo;

typedef vector<BSONObj> BSONObjArray;
class CMongodbModel
{
public:
	CMongodbModel(void);
	CMongodbModel(const BSONObj& objBSON);
	~CMongodbModel(void);

	operator BSONObj() { return m_objBSON; }
	operator BSONObj*() { return &m_objBSON; }

	inline CMongodbModel operator=(const BSONObj& objBSON) { m_objBSON = objBSON; return *this;}
	inline BSONElement GetOID() { return m_objBSON["_id"]; }

	static BSONObj RemoveFields(BSONObj *pRecord, StringArray &arrFieldName);
	static BSONObj MergeBSONObj(BSONObj *pOldRecord, BSONObj *pNewRecord);
	static BSONObj MergeBSONObj(BSONObj *pOldRecord, BSONObj *pNewRecord, BSONObj &pboChangedFields);
	static BSONObj ConvertBSONObj(BSONObj boRecord, map<string, string> mapField);
	//template<class TYPE>
	void Append(string strFieldName, int tValue);
	void Append(string strFieldName, string tValue);
	void Append(string strFieldName, long long tValue);
	void Append(BSONObj boAdd);
	BSONObj LoadObj();

	virtual void Load(const BSONObj& boRecord) {}

	void UpdateBSONObj(const BSONObj& objBSON);
	Query GetObjectIdQuery();
protected:
	BSONObjBuilder *m_pBSONBuilder;
	BSONObj m_objBSON;
	BSONElement m_beOID;
};
